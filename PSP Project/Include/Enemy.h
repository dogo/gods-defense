//**************************************************************************
//		PSP Project: 'Gods Defense' - Enemy.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_ENEMY_H
#define INCLUDED_ENEMY_H

//Class Declarations
class Enemy;
class EnemyInstance;

#include "tinyxml/tinyxml.h"
#include "../Include/GodLibrary.h"
#include "../Include/GameScreen.h"
#include <vector>
#include <string>

using namespace std;

class EnemyInfo
{
/*
*	Health - How much health de enemy has.
*	GoldValue - Specifies the amount of gold is added into the player's Cash when this unit dies.
*	PointValue - How much points is added into the player's Score when this unit dies.
*	Speed - Specifies normal speed of the unit, when try to reach (without modificators).
*	HasImunity - Specifies if the enemy is has imunity Against bad attributes (Poison,IceSlow).
*	CanFly - Specifies if the enemy walks or fly.
*/

	public:
		EnemyInfo();
		EnemyInfo(TiXmlElement* levelNode);
		unsigned int mHealth;
		unsigned int mGoldValue;
		unsigned int mPointValue;
		unsigned int mSpeed;
		bool mHasImunity;
		bool mCanFly;
};


class Enemy
{
	private:
	public:
};

class EnemyInstance
{
	private:
	public:
		Point2D mEnemyPosition;
};


#endif