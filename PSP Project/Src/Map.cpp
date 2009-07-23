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

Wave::Wave()
{
}

Wave::Wave(TiXmlElement *waveNode)
{
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