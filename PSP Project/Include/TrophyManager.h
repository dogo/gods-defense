//**************************************************************************
//		PSP Project: 'Gods Defense' - TrophyManager.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef TROPHYMANAGER_H_INCLUDED
#define TROPHYMANAGER_H_INCLUDED

#include "../Include/ILib.h"

enum TrophyId
{
	TROPHY_FIRST_TOWER,
	TROPHY_FIRST_BLOOD,
	TROPHY_FIRST_UPGRADE,
	TROPHY_FIRST_SALE,
	TROPHY_BUILDER,
	TROPHY_HUNTER,
	TROPHY_HIGH_SCORE,
	TROPHY_DEFENDER,
	TROPHY_COUNT
};

struct TrophyInfo
{
	TrophyId id;
	const char *name;
	const char *description;
};

class TrophyManager
{
public:
	static void Init();
	static void NotifyTowerBuilt();
	static void NotifyTowerUpgraded();
	static void NotifyTowerSold();
	static void NotifyEnemyKilled(const int &score);
	static void NotifyGameFinished(const bool &won, const int &score);

	static bool IsUnlocked(const TrophyId &id);
	static const TrophyInfo *GetTrophyInfo(const int &index);
	static int GetTrophyCount();
	static int GetUnlockedCount();
	static int GetProgressValue(const TrophyId &id);
	static int GetProgressTarget(const TrophyId &id);

private:
	static void Load();
	static void Save();
	static bool Unlock(const TrophyId &id);
	static void CheckProgressUnlocks(const int &score);
};

#endif
