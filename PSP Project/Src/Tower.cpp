//**************************************************************************
//		PSP Project: 'Gods Defense' - Tower.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include <fstream>
#include <math.h>

#include "../Include/Tower.h"
#include "../Include/GameGUI.h"

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
	lowerCase(mTowerDirName);

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

	char temp[256];
	sprintf(temp, "ms0:/PSP/GAME/GodsDefense/Res/towers/%s/tower.xml", mTowerDirName.c_str());

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

			sprintf(temp, "/Res/towers/%s/%s", mTowerDirName.c_str(), node->Attribute("Sprite"));
			mProjectileImg = ProjectileInstance::LoadProjectileImage(mProjectileType, temp);
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
			sprintf(temp, "/Res/towers/%s/%s", mTowerDirName.c_str(), node->Attribute("File"));
			mTowerImg = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

			mTowerImg->centerX = (mTowerImg->sizeX/2); //hotspot
			mTowerImg->centerY = (mTowerImg->sizeY/2); //hotspot

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
			oslFatalError("Bad node, not donout for you: %s",mCurrentLine);
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

void Tower::RenderTower(const Coordinates2D &position)
{
	oslDrawImageXY(mTowerImg, position.X, GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount+position.Y);
}

void Tower::RenderRangeCircle(const Coordinates2D &position, const int &TowerInfo, const OSL_COLOR color)
{
	GodLibrary::drawCircle(position.X, GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount+position.Y, mTowerVector[TowerInfo].mRange, color);
}

TowerInstance::TowerInstance(Tower *tower, const Coordinates2D &position)
{
	int x = ((int)position.X / 32);
	int y = ((int)position.Y / 32);
	mCurrentMap = 0;
	mTower = tower;
	mTowerPosition = Coordinates2D::Coordinates2D(x*32, y*32);
	mTowerTarget = NULL;
	mProjectileInterval = 0;
}

void TowerInstance::Update(unsigned timePassed, const list<EnemyInstance*> &enemies)
{
	mProjectileInterval -= timePassed;
	float mTowerSquareRange = mTower->mTowerVector[mCurrentMap].mRange * mTower->mTowerVector[mCurrentMap].mRange; //Range²

	if(mTowerPosition.SquareDistance(mTowerTarget->mEnemyPosition) > mTowerSquareRange || mTowerTarget->EnemyIsDead() || mTowerTarget->EnemyStillOnMap())
	{
		//The target its out of range or dead
		mTowerTarget = NULL;
	}

	if (!mTowerTarget) //we don't have a target, seek for an enemy.
	{
		//Seek for an enemy.
		//we use an iterator to walk on the enemy list.
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
	else if (mTowerTarget)
	{
		mTowerAngle = mTowerPosition.AimTo(mTowerTarget->mEnemyPosition);

		/*
		* Tower can shoot when the Projectile Interval is < 0. (is a gun shot delay, like shooters games)
		*/
		if (mProjectileInterval <= 0)
		{
			mProjectileInterval = mTower->mTowerVector[mCurrentMap].mRateOfFire;		
			ProjectileInstance::CreateProjectile(this, mTowerTarget);
		}
	}
}

void TowerInstance::RenderTower()
{
	oslDrawImageXY(mTower->mTowerImg, mTowerPosition.X + (mTower->mTowerImg->sizeX/2), (mTower->mTowerImg->sizeY/2) + mTowerPosition.Y + GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount);
}

void TowerInstance::RenderRangeCircle(const Coordinates2D &position, const int &TowerInfo, const OSL_COLOR color)
{
	GodLibrary::drawCircle(position.X, position.Y, mCurrentMap, color);
}