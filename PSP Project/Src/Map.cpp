//**************************************************************************
//		PSP Project: 'Gods Defense' - Map.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Map.h"

EnemyWave::EnemyWave(string folderName, int enemyLevel)
{
	mEnemyDirName = folderName;
	mEnemyLevel = enemyLevel;
}

Wave::Wave(TiXmlElement *waveNode)
{
	//Default Initializers
	mWaveDescription = NULL;
	mIntervalSpawnTime = 1;
	mIsBoss = false;
	mCurrentEnemySpawn = 0;
	mEnemySpawnTimer = 0;
	mEnemiesLeftAlive = 0;
	mWaveEndOnce = false;

	const char *description = waveNode->Attribute("Description");

	if (description != NULL)
		mWaveDescription = strdup(description);
	else
		mWaveDescription = strdup("No Description");

	mCurrentPath = string(waveNode->Attribute("Path"));

	waveNode->QueryIntAttribute("IntervalSpawnTime", &mIntervalSpawnTime);

	const char *tempBoss = waveNode->Attribute("Boss");
	if (tempBoss != NULL && !strcmp(tempBoss, "True")) //strcmp() return 0 if both string be the same.
		mIsBoss = true;

	TiXmlElement *WaveEnemyNode = waveNode->FirstChildElement();
	while (WaveEnemyNode != NULL) //read all Enemies
	{
		if (WaveEnemyNode->ValueStr() != "Enemy")
		{
			oslFatalError("Bad node, not donout for you: %s",WaveEnemyNode->ValueStr());
			return;
		}

		const char *EnemyFolder = WaveEnemyNode->Attribute("Folder");
		int EnemieLevel = 1;
		int EnemyCounter = 1; //minimum

		WaveEnemyNode->QueryIntAttribute("NumberOfEnemies", &EnemyCounter);
		WaveEnemyNode->QueryIntAttribute("EnemieLevel", &EnemieLevel);
		for (int i = 0; i < EnemyCounter; i++)
		{
			mEnemySpawns.push_back(EnemyWave(string(EnemyFolder), EnemieLevel-1));
		}
		WaveEnemyNode = WaveEnemyNode->NextSiblingElement();
	}
	
	mEnemiesLeftAlive = mEnemySpawns.size();
}

void Wave::StartEnemySpawn()
{
	mCurrentEnemySpawn = 0;
	mEnemySpawnTimer = mIntervalSpawnTime;
}

bool Wave::SpawnUpdate(u64 timePassed)
{
	mEnemySpawnTimer += timePassed;

	if (mCurrentEnemySpawn < mEnemySpawns.size() && mEnemySpawnTimer >= mIntervalSpawnTime)
	{
		mEnemySpawnTimer -= mIntervalSpawnTime;
		return true;
	}
	else
		return false;
}

void Wave::GetCurrentWaveEnemy(string &enemyName, int &EnemyLevel)
{
	enemyName = mEnemySpawns[mCurrentEnemySpawn].mEnemyDirName;
	EnemyLevel = mEnemySpawns[mCurrentEnemySpawn].mEnemyLevel;
	printf("EnemyLevel %d\n",EnemyLevel);
	mCurrentEnemySpawn++;
	printf("mCurrentEnemySpawn %d\n",mCurrentEnemySpawn);
}

bool Wave::EndOfWave()
{
	return (mEnemiesLeftAlive == 0);
}

bool Wave::EndOfOneWave()
{
	if (mEnemiesLeftAlive == 0 && !mWaveEndOnce)
	{
		mWaveEndOnce = true;
		return true;
	}
	return false;
}

void Wave::EnemyKilled()
{
	mEnemiesLeftAlive--;
}

Wave::~Wave()
{
	if (mWaveDescription != NULL)  //We have to be free :)
		free(mWaveDescription);
}

PathCoords::PathCoords(TiXmlElement *checkPointNode)
{
	int x=0, y=0;
	checkPointNode->QueryIntAttribute("X", &x);
	checkPointNode->QueryIntAttribute("Y", &y);

	mCoords.X = x;
	mCoords.Y = y;

	mRadius = 0;
	checkPointNode->QueryIntAttribute("Radius", &mRadius);
}

Path::Path()
{
}

Path::Path(TiXmlElement *pathNode)
{
	mCheckpointLength = 0.0f;
	TiXmlElement *node = pathNode->FirstChildElement();
	while (node != NULL) //process all the checkpoints
	{
		if (node->ValueStr() == "Checkpoint")
		{
			mCheckpoint.push_back(PathCoords(node));
			if(mCheckpoint.size() >= 2)
			{	//path length
				mCheckpointLength +=sqrtf(mCheckpoint[mCheckpoint.size()-2].mCoords.SquareDistance(mCheckpoint[mCheckpoint.size()-1].mCoords));
			}
		}
		else
		{
			oslFatalError("Bad node, not donout for you: %s",node->Value());
			return;
		}
		node = node->NextSiblingElement();
	}
}

unsigned int Path::GetCheckpointCount() const
{
	return mCheckpoint.size();
}

Map::Map()
{
	mMapImage = NULL;
	mCurrentMapName = NULL;
	mMapName = NULL;
	mImgMapName = NULL;
	mCollisionMap = NULL;
	mScrollAmount = 0;

	mTowersMenu = new string[4];
}

void Map::LoadMap(const string &MapDirName)
{

	ResetMap();

	char temp[256];
	sprintf(temp, "ms0:/PSP/GAME/GodsDefense/Res/maps/%s/map.xml", MapDirName.c_str()); //we have to pass all path to XML

	TiXmlDocument MapXMLInput;
	MapXMLInput.LoadFile(temp);

	if (MapXMLInput.Error())
	{
		oslFatalError("Cannot open: %s", MapXMLInput.ErrorDesc());
		return;
	}

	mMapName = strdup(MapDirName.c_str());

	TiXmlElement *node = NULL;
	node = MapXMLInput.FirstChildElement(); //head

	if (!node)
	{
		oslFatalError("No head node in: %s", temp);
		return;
	}

	node = node->FirstChildElement();

	while (node != NULL) //Read all XML file
	{
		string mCurrentLine = node->ValueStr();
		if (mCurrentLine == "Name")
		{
			mCurrentMapName = strdup(node->GetText());
		}
		else if (mCurrentLine == "Description")
		{
			char *checkText = strdup(node->GetText());
			/*
				A função strtok busca dentro da string declarada um token definido, ou em tempo de compilação ou em tempo 
				de execução. Se a função encontra o token determinado é devolvido NULL.
			*/
			char *tempDes = strtok(checkText, "\r\n"); // windows uses \r\n -> "\r" carrige return, "\n" break line
			while (tempDes != NULL)
			{
				mDescription.push_back(strdup(tempDes));
				tempDes = strtok(NULL, "\r\n");
			}
			free(checkText);
		}
		else if (mCurrentLine == "Initializers")
		{
			node->QueryIntAttribute("Gold", &mInitialGold);
			node->QueryIntAttribute("Lives", &mInitialLives);
		}
		else if (mCurrentLine == "Menu")
		{
			TiXmlElement *towerMenuNode = node->FirstChildElement();
			while (towerMenuNode != NULL)
			{
				if (towerMenuNode->ValueStr() == "BuildTowerMenu")
				{
					int y=0;

					towerMenuNode->QueryIntAttribute("Y", &y);

					mTowersMenu[y] = string(towerMenuNode->Attribute("Folder"));
				}
				else
				{
					oslFatalError("Error at BuildTowerMenu: %s", towerMenuNode->Value());
					return;
				}
				towerMenuNode = towerMenuNode->NextSiblingElement();
			}
		}
		else if (mCurrentLine == "MapImg")
		{
			mImgMapName = strdup(node->Attribute("File"));

			node->QueryIntAttribute("Width", &mGridTilesWidth);
			node->QueryIntAttribute("Height", &mGridTilesHeight);

			mCollisionMap = new bool*[mGridTilesWidth];
			for (int i = 0; i < mGridTilesWidth; i++)
				mCollisionMap[i] = new bool[mGridTilesHeight];
		}
		else if (mCurrentLine == "CollisionMap")
		{
			if (mCollisionMap == NULL)
			{
				oslFatalError("Map::LoadMap Colision Error");
				return;
			}

			const char* lText = node->GetText();
			int x = 0;
			int y = 0;
			int maxX = 0;

			while (*lText != '\0')
			{
				switch (*lText)
				{
					case '\r':
						//Do nothing, like 06
						break;
					case '\n':
						if (x > 0)
						{
							maxX = x;
							x = 0;
							y++;
						}
						break;
					case '#':
						mCollisionMap[x][y] = true;
						x++;
						break;
					case '_':
						mCollisionMap[x][y] = false;
						x++;
						break;
					default:
						oslFatalError("Bad character %s in Map::LoadMap.",*lText);
						return;
				}
				lText++;
			}
			if ( y != mGridTilesHeight )
			{
				oslFatalError("Map Height size error");
				return;
			}
			if ( maxX != mGridTilesWidth )
			{
				oslFatalError("Map Width size error");
				return;
			}

		}
		else if (mCurrentLine == "Path")
		{
			string pathName = string(node->Attribute("Name"));
			mPaths[pathName] = Path(node);
		}
		else if (mCurrentLine == "Waves")
		{
			TiXmlElement *waveNode = node->FirstChildElement();

			while (waveNode != NULL)
			{
				if (waveNode->ValueStr() != "Wave")
				{
					oslFatalError("Error at load waves in Map::LoadMap %s",waveNode->Value());
					return;
				}

				mWaves.push_back(new Wave(waveNode));
				waveNode = waveNode->NextSiblingElement();
			}
		}
		node = node->NextSiblingElement();
	}
}

void Map::LoadMapImage()
{
	char temp[256];
	sprintf(temp, "/Res/maps/%s/%s", mMapName, mImgMapName);
	mMapImage = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	if(!mMapImage)
		oslFatalError("Error at load %s",mImgMapName);
}

void Map::ResetMap()
{
	if (mMapImage != NULL)
		oslDeleteImage(mMapImage);
	if (mMapName != NULL) //We have to be free :)
		free(mMapName);
	if (mCurrentMapName != NULL)
		free(mCurrentMapName);
	if (mImgMapName != NULL)
		free(mImgMapName);
	if (mCollisionMap != NULL)
	{
		for (int i = 0; i < mGridTilesWidth; i++)
			delete[] mCollisionMap[i];
		delete[] mCollisionMap;
		mCollisionMap = NULL;
	}

	for(unsigned int j = 0; j < mDescription.size(); j++)
	{
		free(mDescription[j]);
	}
	mDescription.clear();

	if (mTowersMenu != NULL)
	{
		for (unsigned int y = 0; y < 4; y++)
			mTowersMenu[y] = "";
	}

	mWaves.clear();
	mPaths.clear();

	mInitialGold = 0;
	mInitialLives = 0;
	mGridTilesWidth = 0;
	mGridTilesHeight = 0;
	mScrollAmount = 0;
}

void Map::draw()
{
	ScrollMap();
	oslDrawImage(mMapImage);
}

Map::~Map()
{
	if(mMapImage != NULL)
		oslDeleteImage(mMapImage);

	delete[] mTowersMenu;
	
	sMapReference = NULL;
}

//Statics
Map *Map::sMapReference = NULL; //init this really necessary?
float Map::mScrollAmount = 0.0; //init this really necessary?

Map *Map::InitMap()
{
	if (sMapReference == NULL)
		sMapReference = new Map();
	return sMapReference;
}

void Map::ScrollMap()
{
	if(osl_keys->pressed.R) //UP
	{
		oslFlushKey();
		
		mMapImage->y -= 34.0;
		
		if (mMapImage->y <= -208) //New Hot Point
			mMapImage->y = -208;			
	}
	
	if(osl_keys->pressed.L) //Down
	{
		oslFlushKey();		
		
		mMapImage->y += 34.0;
		
		if (mMapImage->y >= 0) //Old Hot Point
			mMapImage->y = 0;
	}
	setScrollAmount(mMapImage->y);
}

void Map::DeployTowerAt(const Coordinates2D &position, Tower *tower)
{
	int x = ((int)position.X / 32);
	int y = ((int)position.Y / 32);

	mCollisionMap[x][y] = false;
}

bool Map::TestBuildCollision(const Coordinates2D &position, Tower *tower)
{
	int x = ((int)position.X / 32);
	int y = ((int)position.Y / 32);

	return mCollisionMap[x][y];
}

void Map::setScrollAmount(float scrollValue)
{
	mScrollAmount = scrollValue;
}