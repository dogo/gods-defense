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

Enemy::Enemy(const string &mapName, const string &enemyName)
{
	//Default Initializers
	mEnemyDirName = enemyName;
	mEnemyName = "";
	mSize = 0;
	mCanFly = false;
	mEnemyImg = NULL;
	mEnemyImgDeath = NULL;
	mDeathSound = NULL;

	mEnemyImg->centerX = (mEnemyImg->sizeX/2); //hotspot
	mEnemyImgDeath->centerX = (mEnemyImgDeath->sizeX/2);

	char temp[256];
	sprintf(temp, "Res/enemies/%s/enemy.xml", mEnemyDirName.c_str());

	TiXmlDocument EnemyXMLInput;
	EnemyXMLInput.LoadFile(temp);

	if (EnemyXMLInput.Error())
	{
		oslFatalError("Cannot open: %i", EnemyXMLInput.ErrorDesc());
		return;
	}

	TiXmlElement *node = NULL;
	node = EnemyXMLInput.FirstChildElement(); //head

	if (!node)
	{
		oslFatalError("No head not in: %i", temp);
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
					oslFatalError("TowersLevel Error: %i",EnemylevelNode->Value());
					return;
				}
				mEnemyVector.push_back(EnemyInfo(EnemylevelNode));

				EnemylevelNode = EnemylevelNode->NextSiblingElement();
			}
		}
		else if (mCurrentLine == "EnemyImg")
		{
			sprintf(temp, "Res/enemies/%s/%s", mEnemyDirName.c_str(), node->Attribute("File"));
			mEnemyImg = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

			node->QueryIntAttribute("Width", &mEnemyWidth);
			node->QueryIntAttribute("Height", &mEnemyHeight);
		}
		else if (mCurrentLine == "EnemyDeath")
		{
			sprintf(temp, "Res/enemies/%s/%s", mEnemyDirName.c_str(), node->Attribute("File"));
			mEnemyImgDeath = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

			node->QueryIntAttribute("Width", &mEnemyDeathWidth);
			node->QueryIntAttribute("Height", &mEnemyDeathHeight);
		}
		else if (mCurrentLine == "DeathSound")
		{
			sprintf(temp, "Res/enemies/%s/%s", mEnemyDirName.c_str(), node->Attribute("File"));
			mDeathSound = oslLoadSoundFileWAV (temp, OSL_FMT_NONE);
		}
		else
		{
			oslFatalError("Bad node, not donout for you: %i",mCurrentLine);
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
	mHealth = mEnemy->mEnemyVector[mStat].mHealth;
}

const int EnemyInstance::GetGold() 
{
	return mEnemy->mEnemyVector[mStat].mGoldValue;
}

void EnemyInstance::RenderEnemy()
{
	if (EnemyIsDead()) 
	{
		oslDrawImageXY(mEnemy->mEnemyImgDeath, mEnemyPosition.X, mEnemyPosition.Y);
		return;
	}
	oslDrawImageXY(mEnemy->mEnemyImg, mEnemyPosition.X, mEnemyPosition.Y);
}

bool const EnemyInstance::EnemyIsDead()
{
	return (mHealth <= 0);
}

bool const EnemyInstance::EnemyCanFly()
{
	return mEnemy->mCanFly;
}