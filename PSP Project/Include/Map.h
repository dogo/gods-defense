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
	EnemyWave(string folderName, int enemyLevel);
	string mEnemyDirName;
	int mEnemyLevel;
};

class Wave
{
public:
	Wave(TiXmlElement *waveNode);
	void StartEnemySpawn();
	bool EndOfWave(); //Check if is the end of wave
	void EnemyKilled(); // Every time when an dies or reaches the end of the path.
	void GetCurrentWaveEnemy(string &enemyName, int &EnemyLevel);
	bool SpawnUpdate(u64 timePassed);
	~Wave();

	string mPath;

private:
	unsigned int mCurrentEnemySpawn; // Array watcher
	int mEnemySpawnTimer; // Controls the time of the last enemy spawned
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
	unsigned int GetCheckpointCount() const;

	float mCheckpointLength; //Total length of path
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
	void ResetMap();
	void ScrollMap(); // Dogo : =(
	static Map *InitMap();
	void DeployTowerAt(const Coordinates2D &position, Tower *tower);
	//Returns true if all blocks under the tower are available
	bool TestBuildCollision(const Coordinates2D &position, Tower *tower);
	static void setScrollAmount(float scrollValue);

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
	bool **mCollisionMap;
	string *mTowersMenu;
	static float mScrollAmount;
private:
	static Map *sMapReference;
	OSL_IMAGE *mMapImage;
};

#endif