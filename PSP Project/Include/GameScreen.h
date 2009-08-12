//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

//Class Declarations
class GameGUI;

#include "../Include/ILib.h"
#include "../Include/Projectile.h"
#include "../Include/Tower.h"
#include "../Include/Enemy.h"
#include "../Include/GameGUI.h"
#include "../Include/Map.h"

enum GameState
{
	GS_SCROLL_MAP,		//User is scrolling on the map
	GS_MAP_PLACE_TOWER, //User has selected a tower to build and is placing it on the map
	GS_PAUSE_MENU,		//Pause menu in game
	GS_TOWER_MENU,		//User is choosing a tower from the menu
	GS_GAME_OVER		//Player has won or loose the game
};

class GameScreen : public IScreen
{
private:
	OSL_IMAGE *map;
	GameState mGameState;
	Map *mCurrentMap;
	GameGUI *mGameGUI;
	static GameScreen *sHighLander;
	int mPlayerLives;
	int mPlayerMoney;
	float mPlayerPoints;
	unsigned int mActiveWaves;
	bool mWaveIsRunning; 


public:
	GameScreen();
	OSL_IMAGE *LoadMapImage(const char* imageName);
	void LoadMap(const string &mapName);
	static GameScreen *InitGame();

	virtual ~GameScreen();

	virtual void draw();

	virtual void update();

	const GameState GetGameState();

	void SetGameState(const GameState &newState);

};
#endif
