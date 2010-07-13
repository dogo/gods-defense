//**************************************************************************
//		PSP Project: 'Gods Defense' - Tower.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_TOWER_H
#define INCLUDED_TOWER_H

//Class Declarations
class Tower;
class TowerInstance;

#include "tinyxml/tinyxml.h"
#include "../Include/util/Drawing.h"
#include "../Include/util/PspIO.h"
#include "../Include/Projectile.h"
#include "../Include/Enemy.h"
#include "../Include/GameScreen.h"
#include <string>
#include <vector>
#include <list> // list class-template definition

using namespace std;

/*
* C++ provides the friend keyword to do just this. Inside a class, you can indicate that other classes (or simply functions)
* will have direct access to protected and private members of the class.
* When granting access to a class, you must specify that the access is granted for a class using the class keyword.
* http://www.cprogramming.com/tutorial/friends.html
*/

class TowerInfo
{
public:
	TowerInfo(TiXmlElement* infoNode);

/*
*	Cost - How much the tower cost.
*	SellAmount - Specifies the amount this tower can be sold from.
*	Damage - Tower Damage.
*	ROF - Is the frequency at which a specific tower can fire.
*	Range - The potential distance of the Tower.
*	Splash - Splash Range.  =)
*	Speed - Shot speed.
*	SlowAmount - Speed multiplier for enemy speed (smaller = slower) 
*	SlowLength - Length of time the slow effect
*/
	int mCost;
	int mSellAmount;
	int mDamage;
	int mRateOfFire;
	int mRange;
	int mSplashRange;
	int mSpeed;
	float mSlowAmount;
	int mSlowLength;
	int mCriticalPlus;
};

class Tower
{
public:
	Tower(const string &towerName);
	~Tower();

	void RenderTower(const Coordinates2D &position);
	void RenderRangeCircle(const Coordinates2D &position, const int &TowerInfo, const OSL_COLOR color);
/*
*	mIsBuildable - Player can Build ?.
*	mTowerDirName - Tower Directory name.
*	mTowerName - Tower Name.
*	mTowerDescription - Tower Description.
*	mProjectileType - Projectile Type.
*	mHitsLand - Can Hits land ?
*	mHitsFlyer - Can Hits Flyer ?
*	mTowerLength - The potential distance of the Tower.
*	mMenuIcon - Tower Menu Icon
*	mTowerImg - Tower Image
*	mProjectileImg - Projectile Image
*/
	bool mIsBuildable;
	string mTowerDirName;
	char *mTowerName;
	char *mTowerDescription;
	int mProjectileType;
	bool mHitsLand;
	bool mHitsFlyer;
	int mTowerLength;
	OSL_IMAGE *mMenuIcon;
	OSL_IMAGE *mTowerImg;
	OSL_IMAGE *mProjectileImg;
	OSL_SOUND *mFireSound;
	OSL_SOUND *mHitSound;
	int mTowerWidth;
	int mTowerHeight;

	vector<TowerInfo> mTowerVector;
};

class TowerInstance
{
public:
	Tower *mTower;
	Coordinates2D mTowerPosition; //Tower Center
	unsigned int mTowerLevel; //Tower Level

	TowerInstance(Tower *tower, const Coordinates2D &position);	
	void Update(unsigned timePassed, const list<EnemyInstance*> &enemies);

	void RenderTower();
	void RenderRangeCircle(const OSL_COLOR color);

private:
	int mProjectileInterval;

	EnemyInstance *mTowerTarget;

	friend class ProjectileInstance;
};
#endif