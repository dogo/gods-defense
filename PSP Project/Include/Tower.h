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
#include "../Include/GodLibrary.h"
#include <string>
#include <vector>

using namespace std;

#define ARROW 1;

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
};

class Tower
{
public:
	Tower(const string &mapName, const string &towerName);
	~Tower();

	void RenderTower(const Point2D &position);
	void RenderRangeCircle(const Point2D &position, const int &TowerInfo, const OSL_COLOR color);
/*
*	mIsBuildable - Player can Build ?.
*	mTowerDirName - Tower Directory name.
*	mTowerName - Tower Name.
*	mTowerDescription - Tower Description.
*	mShotType - Shot Type.
*	mHitsLand - Can Hits land ?
*	mHitsFlyer - Can Hits Flyer ?
*	mTowerLength - The potential distance of the Tower.
*	mMenuIcon - Tower Menu Icon
*	mTowerImg - Tower Image
*	mShotImg - Shot Image
*/
	bool mIsBuildable;
	string mTowerDirName;
	char *mTowerName;
	char *mTowerDescription;
	int mShotType; //TODO: Create Shot Class
	bool mHitsLand;
	bool mHitsFlyer;
	int mTowerLength;
	OSL_IMAGE *mMenuIcon;
	OSL_IMAGE *mTowerImg;
	OSL_IMAGE *mShotImg;

	vector<TowerInfo> mLevels;
};

class TowerInstance
{
public:
	TowerInstance(Tower *tower, const Point2D &position);
	
	//void Update(/*ARGS*/);	
	void RenderTower();
	void RenderRangeCircle(const Point2D &position, const int &TowerInfo, const OSL_COLOR color);
private:
	unsigned int mRange;
	Tower *mTower;
	Point2D mPosition; //Tower Center
};
#endif