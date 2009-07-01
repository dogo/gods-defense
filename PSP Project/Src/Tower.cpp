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
	//Default Initialisers
	mTowerDirName = towerName;
	mIsBuildable = true;
	mTowerName = NULL;
	mTowerDescription = NULL;
	mShotType = PT_Arrow;
	mHitsLand = false;
	mHitsFlyer = false;
	mTowerLength = 0;
	mMenuIcon = NULL;
	mTowerImg = NULL;
	mShotImg = NULL;

	mTowerImg->centerX = (mTowerImg->sizeX/2); //hotspot
}

Tower::~Tower()
{
	if (mMenuIcon != NULL)
		oslDeleteImage(mMenuIcon);
	if (mTowerImg != NULL)
		oslDeleteImage(mTowerImg);
	if (mShotImg != NULL)
		oslDeleteImage(mShotImg);
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
	mRange = 0;
	mTower = tower;
	mPosition = position;
	mTowerTarget = NULL;
}

void TowerInstance::Update(unsigned timePassed, const list<EnemyInstance*> &enemies)
{
	if (!mTowerTarget)
	{
		//TODO :  Seek for an enemy.
	}
	else if (mTowerTarget)
	{
		//mTowerAngle = TODO : get the enemy angle
		ProjectileInstance::CreateProjectile(this, mTowerTarget);
	}
}

void TowerInstance::RenderTower()
{
	oslDrawImageXY(mTower->mTowerImg, mPosition.X, mPosition.Y);
}

void TowerInstance::RenderRangeCircle(const Point2D &position, const int &TowerInfo, const OSL_COLOR color)
{
	GodLibrary::drawCircle(position.X, position.Y, mRange, color);
}