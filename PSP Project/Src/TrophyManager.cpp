//**************************************************************************
//		PSP Project: 'Gods Defense' - TrophyManager.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/TrophyManager.h"
#include <stdio.h>
#include <string.h>

struct TrophySaveData
{
	int version;
	int unlockedMask;
	int enemiesKilled;
	int towersBuilt;
	int towersUpgraded;
	int towersSold;
	int gamesWon;
	int bestScore;
};

static const int TROPHY_SAVE_VERSION = 1;
static const char TROPHY_SAVE_FILE[] = "trophies.dat";

static TrophySaveData gTrophySaveData;
static bool gTrophyManagerInitialized = false;

static const TrophyInfo gTrophyInfos[TROPHY_COUNT] = {
	{TROPHY_FIRST_TOWER, "First Defense", "Build your first tower."},
	{TROPHY_FIRST_BLOOD, "First Blood", "Defeat your first enemy."},
	{TROPHY_FIRST_UPGRADE, "Sharper Tools", "Upgrade any tower."},
	{TROPHY_FIRST_SALE, "Trade Route", "Sell any tower."},
	{TROPHY_BUILDER, "Builder", "Build 10 towers."},
	{TROPHY_HUNTER, "Hunter", "Defeat 50 enemies."},
	{TROPHY_HIGH_SCORE, "Hero Score", "Reach 1000 score."},
	{TROPHY_DEFENDER, "Gods Defender", "Win any map."}
};

static void ResetTrophySaveData()
{
	memset(&gTrophySaveData, 0, sizeof(gTrophySaveData));
	gTrophySaveData.version = TROPHY_SAVE_VERSION;
}

void TrophyManager::Init()
{
	if (gTrophyManagerInitialized)
		return;

	ResetTrophySaveData();
	Load();
	gTrophyManagerInitialized = true;
}

void TrophyManager::Load()
{
	FILE *file = fopen(TROPHY_SAVE_FILE, "rb");
	if (file == NULL)
		return;

	TrophySaveData loadedData;
	memset(&loadedData, 0, sizeof(loadedData));

	if (fread(&loadedData, sizeof(loadedData), 1, file) == 1 && loadedData.version == TROPHY_SAVE_VERSION)
	{
		gTrophySaveData = loadedData;
	}

	fclose(file);
}

void TrophyManager::Save()
{
	FILE *file = fopen(TROPHY_SAVE_FILE, "wb");
	if (file == NULL)
		return;

	fwrite(&gTrophySaveData, sizeof(gTrophySaveData), 1, file);
	fclose(file);
}

bool TrophyManager::Unlock(const TrophyId &id)
{
	Init();

	int trophyBit = 1 << id;
	if ((gTrophySaveData.unlockedMask & trophyBit) != 0)
		return false;

	gTrophySaveData.unlockedMask |= trophyBit;
	Save();

	char message[128];
	sprintf(message, "%s\n%s", Resource::STR_EARNED_TROPHIE, gTrophyInfos[id].name);
	oslMessageBox(message, Resource::STR_TROPHIES_CAPTION, oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
	return true;
}

void TrophyManager::CheckProgressUnlocks(const int &score)
{
	if (gTrophySaveData.towersBuilt >= 10)
		Unlock(TROPHY_BUILDER);

	if (gTrophySaveData.enemiesKilled >= 50)
		Unlock(TROPHY_HUNTER);

	if (score >= 1000 || gTrophySaveData.bestScore >= 1000)
		Unlock(TROPHY_HIGH_SCORE);
}

void TrophyManager::NotifyTowerBuilt()
{
	Init();
	gTrophySaveData.towersBuilt++;
	Save();
	Unlock(TROPHY_FIRST_TOWER);
	CheckProgressUnlocks(gTrophySaveData.bestScore);
}

void TrophyManager::NotifyTowerUpgraded()
{
	Init();
	gTrophySaveData.towersUpgraded++;
	Save();
	Unlock(TROPHY_FIRST_UPGRADE);
}

void TrophyManager::NotifyTowerSold()
{
	Init();
	gTrophySaveData.towersSold++;
	Save();
	Unlock(TROPHY_FIRST_SALE);
}

void TrophyManager::NotifyEnemyKilled(const int &score)
{
	Init();
	gTrophySaveData.enemiesKilled++;

	if (score > gTrophySaveData.bestScore)
		gTrophySaveData.bestScore = score;

	Save();
	Unlock(TROPHY_FIRST_BLOOD);
	CheckProgressUnlocks(score);
}

void TrophyManager::NotifyGameFinished(const bool &won, const int &score)
{
	Init();

	if (score > gTrophySaveData.bestScore)
		gTrophySaveData.bestScore = score;

	if (won)
		gTrophySaveData.gamesWon++;

	Save();
	CheckProgressUnlocks(score);

	if (won)
		Unlock(TROPHY_DEFENDER);
}

bool TrophyManager::IsUnlocked(const TrophyId &id)
{
	Init();
	return (gTrophySaveData.unlockedMask & (1 << id)) != 0;
}

const TrophyInfo *TrophyManager::GetTrophyInfo(const int &index)
{
	if (index < 0 || index >= TROPHY_COUNT)
		return NULL;

	return &gTrophyInfos[index];
}

int TrophyManager::GetTrophyCount()
{
	return TROPHY_COUNT;
}

int TrophyManager::GetUnlockedCount()
{
	Init();

	int count = 0;
	for (int i = 0; i < TROPHY_COUNT; i++)
	{
		if ((gTrophySaveData.unlockedMask & (1 << i)) != 0)
			count++;
	}
	return count;
}

int TrophyManager::GetProgressValue(const TrophyId &id)
{
	Init();

	switch (id)
	{
	case TROPHY_FIRST_TOWER:
	case TROPHY_BUILDER:
		return gTrophySaveData.towersBuilt;
	case TROPHY_FIRST_BLOOD:
	case TROPHY_HUNTER:
		return gTrophySaveData.enemiesKilled;
	case TROPHY_FIRST_UPGRADE:
		return gTrophySaveData.towersUpgraded;
	case TROPHY_FIRST_SALE:
		return gTrophySaveData.towersSold;
	case TROPHY_HIGH_SCORE:
		return gTrophySaveData.bestScore;
	case TROPHY_DEFENDER:
		return gTrophySaveData.gamesWon;
	default:
		return 0;
	}
}

int TrophyManager::GetProgressTarget(const TrophyId &id)
{
	switch (id)
	{
	case TROPHY_BUILDER:
		return 10;
	case TROPHY_HUNTER:
		return 50;
	case TROPHY_HIGH_SCORE:
		return 1000;
	default:
		return 1;
	}
}
