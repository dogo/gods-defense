//**************************************************************************
//		PSP Project: 'Gods Defense' - Enemy.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Enemy.h"

/*
EnemyInfo::EnemyInfo(EnXmlElement* infoNode)
{
	mHP = 0;
	mSpeed = 0;
	mGold  = 0;
	mPoisonDmg = 0;
	mSlowLength = 0;
	mSlowAmount = 0;
	mColor = 0;

	// que que é isso???
	infoNode->QueryIntAttribute("HP", &mHP);
	infoNode->QueryIntAttribute("Speed", &mSpeed);
	infoNode->QueryIntAttribute("HP", &mHP);	
	infoNode->QueryIntAttribute("Gold", &mGold);
	infoNode->QueryIntAttribute("Gold", &mGold);
	infoNode->QueryIntAttribute("Speed", &mSpeed);
	infoNode->QueryFloatAttribute("SlowAmount", &mSlowAmount);
	infoNode->QueryIntAttribute("Color", &mColor);
}

Enemy::Enemy(const string &mapName, const string &towerName)
{
	//Default Initialisers
	mEnemyDirName = enemyName;
	mIsAlive = true;
	mEnemyName = NULL;
	mEnemyDescription = NULL;
	mShotType = PT_Arrow;
	//What the hell is this teach me plz DOGO
	mHitsLand = false;
	mHitsFlyer = false;
	mTowerLength = 0;
	mMenuIcon = NULL;
	mTowerImg = NULL;
	mShotImg = NULL;

	mTowerImg->centerX = (mTowerImg->sizeX/2); //hotspot
}

Enemy::~Enemy()
{
	if (mMenuIcon != NULL)
		oslDeleteImage(mMenuIcon);
	if (mEnemyImg != NULL)
		oslDeleteImage(mTowerImg);
	if (mShotImg != NULL)
		oslDeleteImage(mShotImg);
}*/