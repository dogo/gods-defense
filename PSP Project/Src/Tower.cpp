//**************************************************************************
//		PSP Project: 'Gods Defense' - Tower.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include <fstream>
#include <math.h>

#include "../Include/Tower.h"


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

Tower::Tower(const string &mapName, const string &towerName)
{
	//Default Initializers
	mTowerDirName = towerName;
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

	mTowerImg->centerX = (mTowerImg->sizeX/2); //hotspot

	char temp[256];
	sprintf(temp, "Res/maps/%s/towers/%s/tower.xml", mapName.c_str(), mTowerDirName.c_str());

	TiXmlDocument TowerXMLInput;
	TowerXMLInput.LoadFile(temp);

	if (TowerXMLInput.Error())
	{
		oslFatalError("Cannot open: %i", TowerXMLInput.ErrorDesc());
		return;
	}

	TiXmlElement *node = NULL;
	node = TowerXMLInput.FirstChildElement(); //head

	if (!node)
	{
		oslFatalError("No head not in: %i", temp);
		return;
	}

	node = node->FirstChildElement();

	while (node != NULL) //Read all XML file
	{
		string mCurrentLine = node->ValueStr();
		/*
		A função strdup() é usada em situações onde temos que alocar um espaço na memória para copiar determinada string.
		Sem utiliza-lá, teríamos que alocar o espaço antes com malloc(), para em seguida usar strncpy(), por exemplo, para copiar a string.
		A função retorna um ponteiro com a string já alocada (podendo ser liberado com free() depois de seu uso) em caso de sucesso,
		ou ENOMEM como erro caso a memória não tenha sida alocada por insuficiência.		
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
		A função atoi() é usada para converter strings em números inteiros.
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

			if (!strcmp(ProjectileType, "Arrow"))
			{
				mProjectileType = PT_Arrow;
			}
			else if (!strcmp(ProjectileType, "Ice"))
			{
				mProjectileType = PT_Ice;
			}
			
			//More Projectile Types goes here.

			sprintf(temp, "Res/maps/%s/towers/%s/%s", mapName.c_str(), mTowerDirName.c_str(), node->Attribute("Sprite"));
			mProjectileImg = ProjectileInstance::LoadProjectileImage(mProjectileType, temp);
		}
		else if (mCurrentLine == "TowersLevels")
		{
			TiXmlElement *TowerLevelNode = node->FirstChildElement();
			while (TowerLevelNode != NULL) //read all Towers Levels
			{
				if (TowerLevelNode->ValueStr() != "TowersLevel")
				{
					oslFatalError("TowersLevel Error: %i",TowerLevelNode->Value());
					return;
				}
				mLevels.push_back(TowerInfo(TowerLevelNode)); //Insert a element in the end

				TowerLevelNode = TowerLevelNode->NextSiblingElement();
			}
		}
		else if (mCurrentLine == "TowerImg")
		{
			sprintf(temp, "Res/maps/%s/towers/%s/%s", mapName.c_str(), mTowerDirName.c_str(), node->Attribute("File"));
			mTowerImg = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

			node->QueryIntAttribute("Width", &mTowerWidth);
			node->QueryIntAttribute("Height", &mTowerHeight);
		}
		else if (mCurrentLine == "MenuIcon")
		{
			sprintf(temp, "Res/maps/%s/towers/%s/%s", mapName.c_str(), mTowerDirName.c_str(), node->Attribute("File"));
			mMenuIcon = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
		}
		else if (mCurrentLine == "FireSound")
		{
			sprintf(temp, "Res/maps/%s/towers/%s/%s", mapName.c_str(), mTowerDirName.c_str(), node->Attribute("File"));
			mFireSound = oslLoadSoundFileWAV (temp, OSL_FMT_NONE);
		}
		else if (mCurrentLine == "HitSound")
		{
			sprintf(temp, "Res/maps/%s/towers/%s/%s", mapName.c_str(), mTowerDirName.c_str(), node->Attribute("File"));
			mHitSound = oslLoadSoundFileWAV (temp, OSL_FMT_NONE);
		}
		else
		{
			oslFatalError("Bad node, not donout for you: %i",mCurrentLine);
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

void Tower::RenderTower(const Point2D &position)
{
	oslDrawImageXY(mTowerImg, position.X, position.Y);
}

void Tower::RenderRangeCircle(const Point2D &position, const int &TowerInfo, const OSL_COLOR color)
{
	GodLibrary::drawCircle(position.X, position.Y, mLevels[TowerInfo].mRange, color);
}

TowerInstance::TowerInstance(Tower *tower, const Point2D &position)
{
	mCurrentMap = 0;
	mTower = tower;
	mTowerPosition = position;
	mTowerTarget = NULL;
	mProjectileInterval = 0;
}

void TowerInstance::Update(unsigned timePassed, const list<EnemyInstance*> &enemies)
{
	mProjectileInterval -= timePassed;
	float mTowerSquareRange = mTower->mLevels[mCurrentMap].mRange * mTower->mLevels[mCurrentMap].mRange; //Range²

	if(mTowerPosition.SquareDistance(mTowerTarget->mEnemyPosition) > mTowerSquareRange)
	{
		//The target its out of range
		mTowerTarget = NULL;
	}

	if (!mTowerTarget) //we don't have a target, seek for an enemy.
	{
		//TODO :  Seek for an enemy.
	}
	else if (mTowerTarget)
	{
		mTowerAngle = mTowerPosition.AimTo(mTowerTarget->mEnemyPosition);

		/*
		* Tower can shoot when the Projectile Interval is < 0. (is a gun shot delay, like shooters games)
		*/
		if (mProjectileInterval <= 0)
		{
			mProjectileInterval = mTower->mLevels[mCurrentMap].mRateOfFire;		
			ProjectileInstance::CreateProjectile(this, mTowerTarget);
		}
	}
}

void TowerInstance::RenderTower()
{
	oslDrawImageXY(mTower->mTowerImg, mTowerPosition.X, mTowerPosition.Y);
}

void TowerInstance::RenderRangeCircle(const Point2D &position, const int &TowerInfo, const OSL_COLOR color)
{
	GodLibrary::drawCircle(position.X, position.Y, mCurrentMap, color);
}