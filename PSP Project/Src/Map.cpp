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

	const char *description = waveNode->Attribute("Description");

	if (description != NULL)
		mWaveDescription = strdup(description);
	else
		mWaveDescription = strdup("No Description");

	mCurrentPath = string(waveNode->Attribute("Path"));

	waveNode->QueryIntAttribute("IntervalSpawnTime", &mIntervalSpawnTime);

	const char *tempPointOfInterest = waveNode->Attribute("PointOfInterest");
	if (tempPointOfInterest != NULL && !strcmp(tempPointOfInterest, "True")) //strcmp() return 0 if both string be the same.
		mPointOfInterest = true;

	const char *tempBoss = waveNode->Attribute("Boss");
	if (tempBoss != NULL && !strcmp(tempBoss, "True")) //strcmp() return 0 if both string be the same.
		mIsBoss = true;

	TiXmlElement *WaveEnemyNode = waveNode->FirstChildElement();
	while (WaveEnemyNode != NULL) //read all Enemies
	{
		if (WaveEnemyNode->ValueStr() != "Enemy")
		{
			oslFatalError("TowersLevel Error: %i",WaveEnemyNode->ValueStr());
			return;
		}

		const char *EnemyFolder = WaveEnemyNode->Attribute("Folder");
		int waveLevel = 0;

		int EnemyCounter = 1; //minimum
		WaveEnemyNode->QueryIntAttribute("NumberOfEnemies", &EnemyCounter);
		WaveEnemyNode->QueryIntAttribute("Map", &waveLevel);
		for (int i = 0; i < EnemyCounter; i++)
		{
			mEnemySpawns.push_back(EnemyWave(string(EnemyFolder), waveLevel));
		}
		WaveEnemyNode = WaveEnemyNode->NextSiblingElement();
	}
	
	mEnemiesLeftAlive = mEnemySpawns.size();
}

void Wave::StartEnemySpawn()
{
	mCurrentEnemySpawn = 0;
	mEnemySpawnTimer = mTempSpawnTimer;
}

bool Wave::EndOfWave()
{
	return (mEnemiesLeftAlive == 0);
}

void Wave::EnemyKilled()
{
	mEnemiesLeftAlive--;
}

Wave::~Wave()
{
	if (mWaveDescription != NULL)  //We have to be free :)
		free(mWaveDescription);
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