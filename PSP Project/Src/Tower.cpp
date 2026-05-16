//**************************************************************************
//		PSP Project: 'Gods Defense' - Tower.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include <fstream>
#include <math.h>

#include "../Include/Tower.h"
#include "../Include/GameGUI.h"
#include "../Include/util/Sprites.h"

TowerInfo::TowerInfo(TiXmlElement* infoNode)
{
	mCost = 0;
	mSellAmount = 0;
	mDamage = 0;
	mRateOfFire = 0;
	mRange = 0;
	mSplashRange  = 0;
	mSpeed = 0;
	mSlowAmount = 0;
	mSlowLength = 0;
	mCriticalPlus = 0;

	infoNode->QueryIntAttribute("Cost", &mCost);
	infoNode->QueryIntAttribute("SellAmount", &mSellAmount);
	infoNode->QueryIntAttribute("Damage", &mDamage);
	infoNode->QueryIntAttribute("ROF", &mRateOfFire);
	infoNode->QueryIntAttribute("Range", &mRange);
	infoNode->QueryIntAttribute("Splash", &mSplashRange);
	infoNode->QueryIntAttribute("Speed", &mSpeed);
	infoNode->QueryFloatAttribute("SlowAmount", &mSlowAmount);
	infoNode->QueryIntAttribute("SlowLength", &mSlowLength);
	infoNode->QueryIntAttribute("CriticalPlus", &mCriticalPlus);
}

Tower::Tower(const string &towerName)
{
	//Default Initializers
	mTowerDirName = towerName;
	PspIO::lowerCase(mTowerDirName);

	mIsBuildable = true;
	mTowerName = NULL;
	mTowerDescription = NULL;
	mProjectileType = PT_Arrow;
	mHitsLand = false;
	mHitsFlyer = false;
	mTowerLength = 0;
	mMenuIcon = NULL;
	mTowerImg = NULL;
	mProjectileImg = NULL;
	mFireSound = NULL;
	mHitSound = NULL;
	mTowerFrameWidth = 0;
	mTowerFrameHeight = 0;
	mTowerFrameCount = 1;
	mTowerFrameTime = 140;
	mProjectileFrameWidth = 0;
	mProjectileFrameHeight = 0;
	mProjectileFrameCount = 1;
	mProjectileFrameTime = 80;

	char temp[256];
	sprintf(temp, "%s/Res/towers/%s/tower.xml", PspIO::getCurrentDirectory().c_str(), mTowerDirName.c_str());

	TiXmlDocument TowerXMLInput;
	TowerXMLInput.LoadFile(temp);

	if (TowerXMLInput.Error())
	{
		oslFatalError("Cannot open: %s", TowerXMLInput.ErrorDesc());
		return;
	}

	TiXmlElement *node = NULL;
	node = TowerXMLInput.FirstChildElement(); //head

	if (!node)
	{
		oslFatalError("No head node in: %s", temp);
		return;
	}

	node = node->FirstChildElement();

	while (node != NULL) //Read all XML file
	{
		string mCurrentLine = node->ValueStr();
		/*
		The strdup() function is used in situations where we need to allocate space in memory to copy a specific string.
		Without using it, we would have to allocate space first with malloc(), and then use strncpy(), for example, to copy the string.
		The function returns a pointer with the string already allocated (which can be freed with free() after use) on success,
		or ENOMEM as an error if memory was not allocated due to insufficiency.
		*/
		if (mCurrentLine == "Name")
		{
			mTowerName = strdup(node->GetText());
		}
		else if (mCurrentLine == "Description")
		{
			mTowerDescription = strdup(node->GetText());
		}
		/*
		The atoi() function is used to convert strings to integers.
		*/
		else if (mCurrentLine == "TowerLength")
		{
			mTowerLength = atoi(node->GetText());
		}
		else if (mCurrentLine == "Capability")
		{
			const char* mAttributeText;

			mAttributeText = node->Attribute("HitsLand");
			if (mAttributeText != NULL && !strcmp(mAttributeText,"True")) //strcmp() return 0 if both string be the same.
			{
				mHitsLand = true;
			}

			mAttributeText = node->Attribute("HitsFlyers");
			if (mAttributeText != NULL && !strcmp(mAttributeText,"True")) //strcmp() return 0 if both string be the same.
			{
				mHitsFlyer = true;
			}
		}
		else if (mCurrentLine == "Projectile")
		{
			const char* ProjectileType = node->Attribute("Type");
			if (ProjectileType == NULL)
			{
				oslFatalError("No ProjectileType.");
				return;
			}
			//More Projectile Types goes here.
			if (!strcmp(ProjectileType, "Arrow"))
			{
				mProjectileType = PT_Arrow;
			}
			else if (!strcmp(ProjectileType, "Ice"))
			{
				mProjectileType = PT_Ice;
			}
			else if (!strcmp(ProjectileType, "Fire"))
			{
				mProjectileType = PT_Fire;
			}
			else if (!strcmp(ProjectileType, "Lightning"))
			{
				mProjectileType = PT_Lightning;
			}

			node->QueryIntAttribute("FrameWidth", &mProjectileFrameWidth);
			node->QueryIntAttribute("FrameHeight", &mProjectileFrameHeight);
			node->QueryIntAttribute("Frames", &mProjectileFrameCount);
			node->QueryIntAttribute("FrameTime", &mProjectileFrameTime);
			sprintf(temp, "/Res/towers/%s/%s", mTowerDirName.c_str(), node->Attribute("Sprite"));
			mProjectileImg = ProjectileInstance::LoadProjectileImage(mProjectileType, temp);
			if (mProjectileImg && mProjectileFrameWidth > 0 && mProjectileFrameHeight > 0)
				oslSetImageFrameSize(mProjectileImg, mProjectileFrameWidth, mProjectileFrameHeight);
		}
		else if (mCurrentLine == "TowersLevels")
		{
			TiXmlElement *TowerLevelNode = node->FirstChildElement();
			while (TowerLevelNode != NULL) //read all Towers Levels
			{
				if (TowerLevelNode->ValueStr() != "TowersLevel")
				{
					oslFatalError("TowersLevel Error: %s",TowerLevelNode->Value());
					return;
				}
				mTowerVector.push_back(TowerInfo(TowerLevelNode)); //Insert a element in the end

				TowerLevelNode = TowerLevelNode->NextSiblingElement();
			}
		}
		else if (mCurrentLine == "TowerImg")
		{
			node->QueryIntAttribute("FrameWidth", &mTowerFrameWidth);
			node->QueryIntAttribute("FrameHeight", &mTowerFrameHeight);
			node->QueryIntAttribute("Frames", &mTowerFrameCount);
			node->QueryIntAttribute("FrameTime", &mTowerFrameTime);

			sprintf(temp, "/Res/towers/%s/%s", mTowerDirName.c_str(), node->Attribute("File"));
			if (mTowerFrameWidth > 0 && mTowerFrameHeight > 0)
				mTowerImg = Sprites::LoadSpriteFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888, mTowerFrameWidth, mTowerFrameHeight);
			else
				mTowerImg = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

			if (mTowerFrameCount > 1)
			{
				mTowerImg->centerX = (mTowerFrameWidth/2); //hotspot
				mTowerImg->centerY = (mTowerFrameHeight/2); //hotspot
			}
			else
			{
				mTowerImg->centerX = (mTowerImg->sizeX/2); //hotspot
				mTowerImg->centerY = (mTowerImg->sizeY/2); //hotspot
			}

			node->QueryIntAttribute("Width", &mTowerWidth);
			node->QueryIntAttribute("Height", &mTowerHeight);
		}
		else if (mCurrentLine == "MenuIcon")
		{
			sprintf(temp, "/Res/towers/%s/%s", mTowerDirName.c_str(), node->Attribute("File"));
			mMenuIcon = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
		}
		else if (mCurrentLine == "FireSound")
		{
			sprintf(temp, "/Res/towers/%s/%s", mTowerDirName.c_str(), node->Attribute("File"));
			mFireSound = oslLoadSoundFileWAV (temp, OSL_FMT_NONE);
		}
		else if (mCurrentLine == "HitSound")
		{
			sprintf(temp, "/Res/towers/%s/%s", mTowerDirName.c_str(), node->Attribute("File"));
			mHitSound = oslLoadSoundFileWAV (temp, OSL_FMT_NONE);
		}
		else
		{
			oslFatalError("Bad node, not donout for you: %s",mCurrentLine.c_str());
			return;
		}
		node = node->NextSiblingElement();
	}
}

Tower::~Tower()
{
	if (mTowerName != NULL) //We have to be free :)
		free(mTowerName);
	if (mTowerDescription != NULL) //We have to be free :)
		free(mTowerDescription);
	if (mMenuIcon != NULL)
		oslDeleteImage(mMenuIcon);
	if (mTowerImg != NULL)
		oslDeleteImage(mTowerImg);
	if (mProjectileImg != NULL)
		oslDeleteImage(mProjectileImg);
	if (mFireSound != NULL)
		oslDeleteSound(mFireSound);
	if (mHitSound != NULL)
		oslDeleteSound(mHitSound);
}

TowerInstance::TowerInstance(Tower *tower, const Coordinates2D &position)
{
	int x = ((int)position.X / 32);
	int y = ((int)position.Y / 32);
	mTowerLevel = 0;
	mTower = tower;
	mTowerPosition = Coordinates2D(x*32, y*32);
	mTowerTarget = NULL;
	mProjectileInterval = 0;
	mAnimationTime = 0;
	mCurrentFrame = 0;
}

void TowerInstance::Update(unsigned timePassed, const list<EnemyInstance*> &enemies)
{
	mProjectileInterval -= timePassed;
	if (mTower->mTowerFrameCount > 1 && mTower->mTowerFrameTime > 0)
	{
		mAnimationTime += timePassed;
		while (mAnimationTime >= mTower->mTowerFrameTime)
		{
			mAnimationTime -= mTower->mTowerFrameTime;
			mCurrentFrame++;
			mCurrentFrame %= mTower->mTowerFrameCount;
		}
	}
	float mTowerSquareRange = mTower->mTowerVector[mTowerLevel].mRange * mTower->mTowerVector[mTowerLevel].mRange; //Range�

	if (mTowerTarget && (mTowerTarget->EnemyIsDead() || mTowerPosition.SquareDistance(mTowerTarget->mEnemyPosition) > mTowerSquareRange || !mTowerTarget->EnemyStillOnMap()))
	{
		//The target is out of range or dead
		mTowerTarget = NULL;
	}
	if (!mTowerTarget) //We don't have a target, seek for an enemy.
	{
		//Seek for an enemy.
		//We use an iterator to walk through the enemy list.
		list<EnemyInstance*>::const_iterator enemyIteratorList;
		for (enemyIteratorList = enemies.begin(); enemyIteratorList != enemies.end(); enemyIteratorList++)
		{  //Dogo says : evil IF no donut for you !!
			if (!(*enemyIteratorList)->EnemyIsDead() && (*enemyIteratorList)->EnemyStillOnMap() &&
				mTowerPosition.SquareDistance((*enemyIteratorList)->mEnemyPosition) <= mTowerSquareRange &&
				((mTower->mHitsFlyer && (*enemyIteratorList)->EnemyCanFly()) || (mTower->mHitsLand && !(*enemyIteratorList)->EnemyCanFly()))
			)
			{
				mTowerTarget = (*enemyIteratorList);
				break;
			}
		}
	}
	if (mTowerTarget)
	{
		/*
		* Tower can shoot when the Projectile Interval is < 0. (is a gun shot delay, like shooters games)
		*/
		if (mProjectileInterval <= 0)
		{
			mProjectileInterval = mTower->mTowerVector[mTowerLevel].mRateOfFire;
			ProjectileInstance::CreateProjectile(this, mTowerTarget);
		}
	}
}
