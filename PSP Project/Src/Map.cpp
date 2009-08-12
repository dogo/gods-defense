//**************************************************************************
//		PSP Project: 'Gods Defense' - Map.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Map.h"

EnemyWave::EnemyWave(string folderName, int waveLevel)
{
	mMapDirName = folderName;
	mWaveLevel = waveLevel;
}

Wave::Wave(TiXmlElement *waveNode)
{
	//Default Initializers
	mWaveDescription = NULL;
	mIntervalSpawnTime = 1;
	mIsBoss = false;
	mPointOfInterest = false;
	mCurrentEnemySpawn = 0;
	mEnemySpawnTimer = 0;
	mEnemiesLeftAlive = 0;

	const char *description = waveNode->Attribute("Description");

	if (description != NULL)
		mWaveDescription = strdup(description);
	else
		mWaveDescription = strdup("No Description");

	mCurrentPath = string(waveNode->Attribute("Path"));

	waveNode->QueryIntAttribute("IntervalSpawnTime", &mIntervalSpawnTime);

	const char *tempPointOfInterest = waveNode->Attribute("PointOfInterest");
	if (tempPointOfInterest != NULL && !strcmp(tempPointOfInterest, "True")) //strcmp() return 0 if both string be the same.
		mPointOfInterest = true;

	const char *tempBoss = waveNode->Attribute("Boss");
	if (tempBoss != NULL && !strcmp(tempBoss, "True")) //strcmp() return 0 if both string be the same.
		mIsBoss = true;

	TiXmlElement *WaveEnemyNode = waveNode->FirstChildElement();
	while (WaveEnemyNode != NULL) //read all Enemies
	{
		if (WaveEnemyNode->ValueStr() != "Enemy")
		{
			oslFatalError("Bad node, not donout for you: %i",WaveEnemyNode->ValueStr());
			return;
		}

		const char *EnemyFolder = WaveEnemyNode->Attribute("Folder");
		int waveLevel = 0;

		int EnemyCounter = 1; //minimum
		WaveEnemyNode->QueryIntAttribute("NumberOfEnemies", &EnemyCounter);
		WaveEnemyNode->QueryIntAttribute("Map", &waveLevel);
		for (int i = 0; i < EnemyCounter; i++)
		{
			mEnemySpawns.push_back(EnemyWave(string(EnemyFolder), waveLevel));
		}
		WaveEnemyNode = WaveEnemyNode->NextSiblingElement();
	}
	
	mEnemiesLeftAlive = mEnemySpawns.size();
}

void Wave::StartEnemySpawn()
{
	mCurrentEnemySpawn = 0;
	mEnemySpawnTimer = mTempSpawnTimer;
}

void Wave::GetCurrenteWaveEnemy(string &enemyName, int &WaveLevel)
{
	enemyName = mEnemySpawns[mCurrentEnemySpawn].mMapDirName;
	WaveLevel = mEnemySpawns[mCurrentEnemySpawn].mWaveLevel;
	mCurrentEnemySpawn++;
}

bool Wave::EndOfWave()
{
	return (mEnemiesLeftAlive == 0);
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
	TiXmlElement *node = pathNode->FirstChildElement();
	while (node != NULL) //process all the checkpoints
	{
		if (node->ValueStr() == "Checkpoint")
		{
			mCheckpoint.push_back(PathCoords(node));

			//TODO : Calculate path length
		}
		else
		{
			oslFatalError("Bad node, not donout for you: %i",node->Value());
			return;
		}
		node = node->NextSiblingElement();
	}
}

Map::Map()
{
	mCurrentMapName = NULL;
	mMapName = NULL;
	mCurrentMapName = NULL;
	mImgMapName = NULL;
	mColisionMap = NULL;
}

void Map::LoadMap(const string &MapDirName)
{
	char temp[256];
	sprintf(temp, "Res/maps/%s/map.xml", MapDirName.c_str());

	TiXmlDocument MapXMLInput;
	MapXMLInput.LoadFile(temp);

	if (MapXMLInput.Error())
	{
		oslFatalError("Cannot open: %i", MapXMLInput.ErrorDesc());
		return;
	}

	mMapName = strdup(MapDirName.c_str());

	TiXmlElement *node = NULL;
	node = MapXMLInput.FirstChildElement(); //head

	if (!node)
	{
		oslFatalError("No head node in: %i", temp);
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
				A fun��o strtok busca dentro da string declarada um token definido, ou em tempo de compila��o ou em tempo 
				de execu��o. Se a fun��o encontra o token determinado � devolvido NULL.
			*/
			char *tempDes = strtok(checkText, "\n"); // "\r\n ou \n\r" ???
			while (tempDes != NULL)
			{
				mDescription.push_back(strdup(tempDes));
				tempDes = strtok(NULL, "\n");
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
				if (mCurrentLine == "BuildTowerMenu")
				{
					int x=0, y=0;

					towerMenuNode->QueryIntAttribute("X", &x);
					towerMenuNode->QueryIntAttribute("Y", &y);

					mTowersMenu[x][y] = string(towerMenuNode->Attribute("Folder"));
				}
				else
				{
					oslFatalError("Error at BuildTowerMenu: %i", towerMenuNode->Value());
					return;
				}
				towerMenuNode = towerMenuNode->NextSiblingElement();
			}
		}
		else if (mCurrentLine == "ColisionMap")
		{
			if (mColisionMap == NULL)
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
				case '\n':
					if (x > 0)
					{
						maxX = x;
						x = 0;
						y++;
					}
					break;
				case '#':
					mColisionMap[x][y] = true;
					x++;
					break;
				case '_':
					mColisionMap[x][y] = false;
					x++;
					break;
				default:
					oslFatalError("Bad character %i in Map::LoadMap.",*lText);
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
		else if (mCurrentLine == "MapImg")
		{
			mImgMapName = strdup(node->Attribute("File"));

			node->QueryIntAttribute("Width", &mGridTilesWidth);
			node->QueryIntAttribute("Height", &mGridTilesHeight);

			mColisionMap = new bool*[mGridTilesWidth];
			for (int i = 0; i < mGridTilesWidth; i++)
				mColisionMap[i] = new bool[mGridTilesHeight];
		}
		else if (mCurrentLine == "Path")
		{
			string pathName = string(node->Attribute("Name"));
			mPaths[pathName] = Path(node);
		}
		else if (mCurrentLine == "Waves")
		{
			TiXmlElement* waveNode = node->FirstChildElement();
			while (waveNode != NULL)
			{
				if (waveNode->ValueStr() != "Wave")
				{
					oslFatalError("Error at load waves in Map::LoadMap %i",waveNode->Value());
					return;
				}

				mWaves.push_back(new Wave(waveNode));

				waveNode = waveNode->NextSiblingElement();
			}
		}
		node = node->NextSiblingElement();
	}
}

void Map::draw()
{

}

Map *Map::sHighLander = 0; //init this really necessary?

Map *Map::InitMap()
{
	if (sHighLander == NULL)
		sHighLander = new Map();
	return sHighLander;
}