//**************************************************************************
//		PSP Project: 'Gods Defense' - Map.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

//Class Declarations
class EnemyWave;
class Wave;
class Path;
class Map;

#include "../Include/GameScreen.h"
#include "../Include/Tower.h"
#include "../Include/GodLibrary.h"
#include "tinyxml/tinyxml.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class EnemyWave
{
public:
	EnemyWave(string folderName, int waveLevel);
	string mMapDirName;
	int mWaveLevel;
};

class Wave
{
public:
	Wave(TiXmlElement *waveNode);
	void StartEnemySpawn();
	bool EndOfWave(); //Check if is the end of wave
	void EnemyKilled(); // Every time when an dies or reaches the end of the path.
	void GetCurrenteWaveEnemy(string &enemyName, int &WaveLevel);
	~Wave();
private:
	unsigned int mCurrentEnemySpawn; // Array watcher
	int mEnemySpawnTimer; // Controls the time of the last enemy spawned
	int mTempSpawnTimer;
	char *mWaveDescription; //wave Description
	bool mIsBoss; // boss wave? 
	bool mPointOfInterest; //The enemy reached the point of interest, the player loses points for life
	int mEnemiesLeftAlive; //how many enemies left in the current wave
	int mIntervalSpawnTime; //Interval spawn time between enemies in the wave
	string mCurrentPath;
	vector<EnemyWave> mEnemySpawns;
};

class PathCoords
{
public:
	PathCoords(TiXmlElement *checkPointNode);

	Coordinates2D mCoords;
	int mRadius;
};

class Path
{
public:
	Path();
	Path(TiXmlElement *pathNode);

private:
	vector<PathCoords> mCheckpoint;
};

class Map
{
public:
	Map();
	~Map();
	void draw();
	void LoadMap(const string &mapName);
	void LoadMapImage();
	static Map *InitMap();

	char *mMapName;
	char *mCurrentMapName;
	char *mImgMapName;
	int mInitialGold;
	int mInitialLives;
	vector<char*> mDescription;
	vector<Wave*> mWaves;
	map<string, Path> mPaths;
	int mGridTilesWidth;
	int mGridTilesHeight;
	bool **mColisionMap;
	string **mTowersMenu;
private:
	static Map *sHighLander;
	OSL_IMAGE *mMapImage;
};

#endif