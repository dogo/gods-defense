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

	infoNode->QueryIntAttribute("Cost", &mCost);
	infoNode->QueryIntAttribute("SellAmount", &mSellAmount);
	infoNode->QueryIntAttribute("Damage", &mDamage);
	infoNode->QueryIntAttribute("ROF", &mRateOfFire);
	infoNode->QueryIntAttribute("Range", &mRange);
	infoNode->QueryIntAttribute("Splash", &mSplashRange);
	infoNode->QueryIntAttribute("Speed", &mSpeed);
	infoNode->QueryFloatAttribute("SlowAmount", &mSlowAmount);
	infoNode->QueryIntAttribute("SlowLength", &mSlowLength);
}

Tower::Tower(const string &mapName, const string &towerName)
{
	//Default Initialisers
	mTowerDirName = towerName;
	mIsBuildable = true;
	mTowerName = NULL;
	mTowerDescription = NULL;
	mShotType = ARROW;
	mHitsLand = false;
	mHitsFlyer = false;
	mTowerLength = 0;
	mMenuIcon = NULL;
	mTowerImg = NULL;
	mShotImg = NULL;

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

void Tower::RenderRangeCircle(const Point2D &position, const int &TowerInfo, const OSL_COLOR color)
{
/*
	dogo : TODO : Fix this 
	(Error	1	error: cannot call member function 'void GodLibrary::drawCircle(int, int, int, OSL_COLOR)' 
	without object	Src/Tower.cpp:64)
	
	GodLibrary::drawCircle(position.X, position.Y, mLevels[TowerInfo].mRange, color);
*/
}