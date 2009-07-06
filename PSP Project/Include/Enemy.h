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
	public:
		EnemyInfo();
		EnemyInfo(TiXmlElement* levelNode);
		unsigned int mHealth;
		unsigned int mGoldValue;
		unsigned int mPointValue;
		unsigned int mSpeed;
		bool mCanSlow;
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