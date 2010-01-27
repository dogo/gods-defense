//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

//Class Declarations
class GameGUI;
class PauseScreen;

#include "../Include/ILib.h"
#include "../Include/Projectile.h"
#include "../Include/Tower.h"
#include "../Include/Enemy.h"
#include "../Include/GameGUI.h"
#include "../Include/Map.h"
#include "../Include/Adhoc.h"
#include "../Include/PauseScreen.h"
#include <map>
#include <list>

using namespace std;

enum GameState
{
	GS_SCROLL_MAP,			//User is scrolling on the map
	GS_MAP_PLACE_TOWER,		//User has selected a tower to build and is placing it on the map
	GS_PAUSE_MENU,			//Pause menu in game
	GS_TOWER_MENU,			//User is choosing a tower from the menu
	GS_GAME_OVER,			//Player has won or loose the game
	GS_GAME_LOADED,			//All game items are loaded
	GS_TOWER_UPGRADE_SELL	//User has selected a tower to upgrade or sell
};

enum GameConnectionState
{
	GCS_WAITING_CONNECTION, //Ad hoc server is waiting for a player
	GCS_CONNECTED,			//Ad hoc connection is ok
	GCS_DISCONNECTED		//Ad hoc connection is down or disconnected
};

class GameScreen : public IScreen
{
private:
	map<string, Tower*> mTowers;
	map<string, Enemy*> mEnemies;
	void LoadTower(const string &towerName);
	void LoadEnemy(const string &enemyName);
	void CleanTowers();
	void CleanEnemies();
	void RunNextWave(const bool &forceRunNow);
	int GetNextWaveNumber() const;
	int GetWaveCount() const;
	void drawGrid();

	OSL_IMAGE *mMap;
	GameState mGameState;
	Map *mGameMap;
	GameGUI *mGameGUI;
	int mPlayerLives;
	int mPlayerMoney;
	float mPlayerPoints;
	unsigned int mActiveWaves;
	bool mWaveIsRunning;
	bool mShowDesc;
	PauseScreen *pauseScreenReference;
	list<TowerInstance*> mRealTowers;  //Current builded towers
	//ad hoc
	Adhoc *mAdhocReference;
	GameConnectionState mGameConnectionState;

public:
	GameScreen();
	void LoadMap(const string &mapName);
	void LoadFirstPartForMap();
	string *GetMenuTowers() const;
	Tower *GetTower(const string &towerName) const;
	Tower *GetSelectedTower() const;
	int const GetPlayerMoney();
	int const GetPlayerLives();
	float const GetPlayerScore();
	bool TryBuildTower(Tower *tower, Coordinates2D position);
	bool TrySelectTower(const Coordinates2D &position);
	bool TryUpgradeSelectedTower();
	bool TrySellSelectedTower();
	void drawUpgradeCircle();
	Map *GetGameMap();
	void TryRunNextWave();
	unsigned int GetSelectedTowerLevel() const;
	bool mDeleteEnemy;
	static GameScreen *gGameReference;
	static bool gPauseGame;
	list<ProjectileInstance*> mRealProjectiles;   //Current shots
	list<EnemyInstance*> mRealEnemies; //Current spawned enemies
	TowerInstance *mSelectedTower; //Tower we have selected for upgrading/selling (or null)

	virtual ~GameScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

	const GameState GetGameState();
	void SetGameState(const GameState &newState);

	//ad hoc
	const GameConnectionState GetGameConnectionState();
	void SetGameConnectionState(const GameConnectionState &newState);
};
#endif
