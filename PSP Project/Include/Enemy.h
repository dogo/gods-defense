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
#include "../Include/Map.h"
#include <vector>
#include <string>
#include <list> // list class-template definition

using namespace std;

enum EnemyState
{
	NOTHING_HAPPENING, //Nothing is happening with the enemy
	ENEMY_DIED, //Just died, give player gold
	ENEMY_HIT_THE_END, //Enemy hit the end of the path
	ENEMY_FULLY_DEAD //Enemy died
};

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
public:
	Enemy(const string &enemyName);
	~Enemy();

	string mEnemyDirName;
	string mEnemyName;
	string mEnemyDescription;
	int mSize;
	bool mCanFly;
	OSL_IMAGE *mEnemyImg;
	OSL_SOUND *mDeathSound;
	int mEnemyWidth;
	int mEnemyHeight;
	int mAliveFrames;

	vector<EnemyInfo> mEnemyVector;
};

class EnemyInstance  : public ReferenceCounted
{
public:
	EnemyInstance(Wave *wave, Enemy *enemy, const string &path, const unsigned int &level);
	Coordinates2D mEnemyPosition;
	Coordinates2D mNextCheckpoint; //Waypoint we are travelling to
	Wave *mWave; //Wave :)
	Enemy *mEnemy;
	int mHealth; //Enemy health, <= 0 dead
	unsigned int mStat;
	Path *mPath; //Path to travel
	const static int MAPSIZE = 480;
	float mSlowAmount;
	int mSlowLength;
	EnemyState mEnemyState;
	float mAngle;
	int mAnimationController;

	EnemyState GetEnemyState();
	void RenderLife();
	const int GetGold();
	void RenderEnemy();
	void Update(u64 timePassed);
	bool const EnemyIsDead(); // check if the enemy is dead.
	bool const EnemyCanFly(); // check if the enemy can fly.
	bool const EnemyStillOnMap(); //check if the enemy still on the map.
	void EnemyReciveDamage(const int &damage, const float &slowAmount, const int &slowLength); // the enemy recive damage
	float GetPointsWorth() const;
	int mCurrentFrames;

private:
	unsigned int mCurrentCheckpoint;
	float mDistanceFromStart;
};


#endif