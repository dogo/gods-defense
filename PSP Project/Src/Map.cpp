//**************************************************************************
//		PSP Project: 'Gods Defense' - Map.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Map.h"

EnemyWave::EnemyWave(string mapDirName, int waveLevel)
{
	mMapDirName = mapDirName;
	mWaveLevel = waveLevel;
}

Wave::Wave(TiXmlElement *waveNode)
{
	//Default Initializers
	mWaveDescription = NULL;
	mIntervalSpawnTime = 1;
	mIsBoss = false;
	mPointOfInterest = false;
	mCurrentEnemySpawn = 0;
	mEnemySpawnTimer = 0;
	mEnemiesLeftAlive = 0;
}

void Wave::EnemySpawn()
{
	mCurrentEnemySpawn = 0;
	mEnemySpawnTimer = mTempSpawnTimer;
}

Wave::~Wave()
{
}

Path::Path()
{
}

Path::Path(TiXmlElement *pathNode)
{
}

void Map::LoadMap(const string &mapName)
{
}