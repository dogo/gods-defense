//**************************************************************************
//		PSP Project: 'Gods Defense' - Enemy.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Enemy.h"

EnemyInfo::EnemyInfo()
{
	//Default Initializers
	mHealth = 0;
	mGoldValue = 0;
	mPointValue = 0;
	mSpeed = 0;
	mHasImunity = true;
	mCanFly = true;
}


EnemyInfo::EnemyInfo(TiXmlElement* infoNode)
{
	//Default Initializers
	mHealth = 0;
	mGoldValue = 0;
	mPointValue = 0;
	mSpeed = 0;
	mHasImunity = true;
	mCanFly = true;

	int temp;

	infoNode->QueryIntAttribute("Health", &temp);
	mHealth = temp;

	infoNode->QueryIntAttribute("GoldValue", &temp);
	mGoldValue = temp;

	infoNode->QueryIntAttribute("PointValue", &temp);
	mPointValue = temp;

	infoNode->QueryIntAttribute("Speed", &temp);
	mSpeed = temp;

	const char* HasImunity = infoNode->Attribute("HasImunity");
	if (HasImunity != NULL && !strcmp(HasImunity,"False")) //strcmp() return 0 if both string be the same.
	{
		mHasImunity = false;
	}
	const char* CanFly = infoNode->Attribute("CanFly");
	if (CanFly != NULL && !strcmp(CanFly,"False")) //strcmp() return 0 if both string be the same.
	{
		mCanFly = false;
	}
}

Enemy::Enemy(const string &enemyName)
{
	//Default Initializers
	mEnemyDirName = enemyName;
	lowerCase(mEnemyDirName);

	mEnemyName = "";
	mSize = 0;
	mCanFly = false;
	mEnemyImg = NULL;
	mAliveFrames = 0;
	mEnemyImgDeath = NULL;
	mDeathFrames = 0;
	mDeathSound = NULL;

	char temp[256];
	sprintf(temp, "ms0:/PSP/GAME/GodsDefense/Res/enemies/%s/enemy.xml", mEnemyDirName.c_str());

	TiXmlDocument EnemyXMLInput;
	EnemyXMLInput.LoadFile(temp);

	if (EnemyXMLInput.Error())
	{
		oslFatalError("Cannot open: %s", EnemyXMLInput.ErrorDesc());
		return;
	}

	TiXmlElement *node = NULL;
	node = EnemyXMLInput.FirstChildElement(); //head

	if (!node)
	{
		oslFatalError("No head not in: %s", temp);
		return;
	}

	node = node->FirstChildElement();

	while (node != NULL) //Read all XML file
	{
		string mCurrentLine = node->ValueStr();
		if (mCurrentLine == "Name")
		{
			mEnemyName = string(node->GetText());
		}
		else if (mCurrentLine == "Description")
		{
			mEnemyDescription = string(node->GetText());
		}		
		else if (mCurrentLine == "Size")
		{
			mSize = atoi(node->GetText());
		}
		else if (mCurrentLine == "Stats")
		{
			TiXmlElement *EnemylevelNode = node->FirstChildElement();
			while (EnemylevelNode != NULL) //read all enemy Stats
			{
				if (EnemylevelNode->ValueStr() != "Stat")
				{
					oslFatalError("EnemylevelNode Error: %s",EnemylevelNode->Value());
					return;
				}
				mEnemyVector.push_back(EnemyInfo(EnemylevelNode));

				EnemylevelNode = EnemylevelNode->NextSiblingElement();
			}
		}
		else if (mCurrentLine == "EnemyImg")
		{
			node->QueryIntAttribute("Frames", &mAliveFrames);

			sprintf(temp, "/Res/enemies/%s/%s", mEnemyDirName.c_str(), node->Attribute("File"));
			mEnemyImg = GodLibrary::LoadSpriteFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888, 32, 32); //32 Width && 32 Height

			mEnemyImg->centerX = (mEnemyImg->sizeX/2); //hotspot
			mEnemyImg->centerY = (mEnemyImg->sizeY/2); //hotspot

			node->QueryIntAttribute("Width", &mEnemyWidth);
			node->QueryIntAttribute("Height", &mEnemyHeight);
		}
		else if (mCurrentLine == "EnemyDeath")
		{
			node->QueryIntAttribute("Frames", &mDeathFrames);

			sprintf(temp, "/Res/enemies/%s/%s", mEnemyDirName.c_str(), node->Attribute("File"));
			mEnemyImgDeath = GodLibrary::LoadSpriteFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888, 32, 32); //32 Width && 32 Height

			mEnemyImgDeath->centerX = (mEnemyImgDeath->sizeX/2);
			mEnemyImgDeath->centerY = (mEnemyImgDeath->sizeY/2);

			node->QueryIntAttribute("Width", &mEnemyDeathWidth);
			node->QueryIntAttribute("Height", &mEnemyDeathHeight);
		}
		else if (mCurrentLine == "DeathSound")
		{
			sprintf(temp, "/Res/enemies/%s/%s", mEnemyDirName.c_str(), node->Attribute("File"));
			mDeathSound = oslLoadSoundFileWAV (temp, OSL_FMT_NONE);
		}
		else
		{
			oslFatalError("Bad node, not donout for you: %s",mCurrentLine);
			return;
		}
		node = node->NextSiblingElement();
	}
}

Enemy::~Enemy()
{
	if (mEnemyImg != NULL)
		oslDeleteImage(mEnemyImg);
	if (mEnemyImgDeath != NULL)
		oslDeleteImage(mEnemyImgDeath);
	if (mDeathSound != NULL)
		oslDeleteSound(mDeathSound);
}

EnemyInstance::EnemyInstance(Wave *wave, Enemy *enemy, const string &path, const unsigned int &level)
{
	mWave = wave;
	mEnemy = enemy;
	mStat = level;
	mPath = &(Map::InitMap()->mPaths["default"]); //TODO :  Fix this path is empty why ?!
	mEnemyPosition = mPath->mCheckpoint[0].mCoords; // mIndex == 0, to start
	mNextCheckpoint = mPath->mCheckpoint[1].mCoords; // mIndex == 1, nextCheckpoint
	mAngle = mEnemyPosition.AimTo(mNextCheckpoint);
	mHealth = mEnemy->mEnemyVector[mStat].mHealth;
	mSlowAmount = 0.0;
	mSlowLength = 0;
	mEnemyState = NOTHING_HAPPENING;
	mCurrentCheckpoint = 1;
}

void EnemyInstance::Update(u64 timePassed)
{
	//Enemy is dead so we return
	if (EnemyIsDead())
		return;

	float angle = mEnemyPosition.AimTo(mNextCheckpoint);
	float changeX = mEnemy->mEnemyVector[mStat].mSpeed * cos(angle);
	float changeY = mEnemy->mEnemyVector[mStat].mSpeed * sin(angle);
	float movement = mEnemy->mEnemyVector[mStat].mSpeed * timePassed / 1000.0f; //distance I'll move this tick

	//Update mAngle (render angle) to flow smoothly with the angle of travel
	if (mAngle != angle)
	{
		//Fix the render angle to be within M_PI so the enemy rotates in the right direction
		while (mAngle - angle >= M_PI)
			mAngle -= 2*M_PI;
		while (mAngle - angle <= -M_PI)
			mAngle += 2*M_PI;

		//Now slowly move the angle over
		float angleForTime = 2 * M_PI * timePassed / 1000.0f;
		if (fabs(mAngle - angle) <= angleForTime)
		{
			mAngle = angle;
		}
		else
		{
			if (mAngle > angle)
				mAngle -= angleForTime;
			else //mAngle < angle
				mAngle += angleForTime;
		}
	}

	//Decrement the slow counter
	mSlowLength -= timePassed;

	//If we are going slow then travel at reduced speed
	if (mSlowLength > 0)
	{
		movement *= mSlowAmount;
	}
	
	float xdif = fabs(mEnemyPosition.X - mNextCheckpoint.X);
	float ydif = fabs(mEnemyPosition.Y - mNextCheckpoint.Y);

	float distance = sqrtf((xdif * xdif) + (ydif * ydif));

	if (distance <= movement)
	{
		mEnemyPosition = mNextCheckpoint;

		mCurrentCheckpoint++;
		if (mCurrentCheckpoint >= mPath->GetCheckpointCount())
		{
			mEnemyState = ENEMY_HIT_THE_END;
			mWave->EnemyKilled();
			return;
		}

		mNextCheckpoint = mPath->mCheckpoint[mCurrentCheckpoint].mCoords;

		return;
	}
		//Calculate new position
	if (mSlowLength > 0)
	{
		mEnemyPosition.X += (changeX * timePassed * mSlowAmount)/1000;
		mEnemyPosition.Y += (changeY * timePassed * mSlowAmount)/1000;
	}
	else
	{
		mEnemyPosition.X += (changeX * timePassed)/1000;
		mEnemyPosition.Y += (changeY * timePassed)/1000;
	}
}

EnemyState EnemyInstance::GetEnemyState()
{
	if (mEnemyState == ENEMY_DIED)
	{
		if (mEnemy->mDeathSound != NULL)
			oslPlaySound(mEnemy->mDeathSound, 1); //Plays the die sound on channel 1
		return ENEMY_DIED;
	}
	else if (mEnemyState == ENEMY_HIT_THE_END)
	{
		return ENEMY_HIT_THE_END;
	}
	else if (mEnemyState == ENEMY_FULLY_DEAD)
	{
		mEnemyState = ENEMY_FULLY_DEAD;
	}
	return mEnemyState;
}

const int EnemyInstance::GetGold() 
{
	return mEnemy->mEnemyVector[mStat].mGoldValue;
}

void EnemyInstance::RenderEnemy()
{
	if (EnemyIsDead()) 
	{
		DrawImageFrameXY(mEnemy->mEnemyImgDeath, mEnemyPosition.X, mEnemyPosition.Y, mEnemy->mDeathFrames);
		return;
	}
	mEnemy->mEnemyImg->centerX = 16; //Enemie / 2
	mEnemy->mEnemyImg->angle = (mAngle * 180/M_PI);
	DrawImageFrameXY(mEnemy->mEnemyImg, mEnemyPosition.X, GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount+mEnemyPosition.Y, mEnemy->mAliveFrames);
	oslPrintf_xy(0,30, "Enemy X-> %f    Enemy Y %f  mAngle %d", mEnemyPosition.X, mEnemyPosition.Y, mEnemy->mEnemyImg->angle);
}

bool const EnemyInstance::EnemyIsDead()
{
	return (mHealth <= 0);
}

bool const EnemyInstance::EnemyCanFly()
{
	return mEnemy->mCanFly;
}

bool const EnemyInstance::EnemyStillOnMap()
{	
	/*
mEnemyPosition.X < 0 |---------------------------| mEnemyPosition.X >= 480
					 |							 |
					 |		  PSP Screen		 |
					 |						     |
mEnemyPosition.Y < 0 |---------------------------| mEnemyPosition.Y >= 480
	*/
	return !(mEnemyPosition.X < 0 || mEnemyPosition.X >= MAPSIZE || mEnemyPosition.Y < 0 || mEnemyPosition.Y >= MAPSIZE);
}

void EnemyInstance::EnemyReciveDamage(const int &damage, const float &slowAmount, const int &slowLength)
{
	float currentSlow = (mSlowLength / mSlowAmount);
	float tempSlow = (slowLength / slowAmount);

	if (tempSlow > currentSlow)
	{
		mSlowAmount = slowAmount;
		mSlowLength = slowLength;
	}

	bool enemyIsAlive = (!EnemyIsDead());
	mHealth -= damage;
	if (enemyIsAlive && EnemyIsDead())
	{
		mEnemyState = ENEMY_DIED;
	}
}
