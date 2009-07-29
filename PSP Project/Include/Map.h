//**************************************************************************
//		PSP Project: 'Gods Defense' - Map.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

//Class Declarations
class Wave;
class Path;
class Map;

#include "../Include/GameScreen.h"
#include "../Include/Tower.h"
#include "../Include/GodLibrary.h"
#include "tinyxml/tinyxml.h"

using namespace std;

class EnemyWave
{
public:
	EnemyWave(string MapDirName, int waveLevel);
	string mMapDirName;
	int mWaveLevel;
};

class Wave
{
public:
	Wave(TiXmlElement *waveNode);
	void EnemySpawn();
	~Wave();
private:
	unsigned int mCurrentEnemySpawn; // Array watcher
	int mEnemySpawnTimer; // Controls the time of the last enemy spawned
	int mTempSpawnTimer;
	char *mWaveDescription; //wave Description
	bool mIsBoss; // boss wave? 
	bool mPointOfInterest; //The enemy reached the point of interest, the player loses points for life
	int mEnemiesLeftAlive; //how many enemies left in the current wave
};

class Path
{
public:
	Path();
	Path(TiXmlElement *pathNode);
};

class Map
{
public:
	void LoadMap(const string &mapName);
};

#endif