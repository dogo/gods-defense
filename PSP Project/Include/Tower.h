#ifndef INCLUDED_TOWER_H
#define INCLUDED_TOWER_H

//Class Declarations
class Tower;
class TowerInstance;

#include "tinyxml/tinyxml.h"
#include "../Include/GodLibrary.h"

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
#endif