//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/Projectile.h"
#include "../Include/Tower.h"
#include "../Include/Enemy.h"
#include "../Include/GameGUI.h"


enum GameState
{
	GS_SCROLL_MAP,		//User is scrolling on the map
	GS_MAP_PLACE_TOWER, //User has selected a tower to build and is placing it on the map
	GS_INGAME_MENU,		//Menu overlaid on the map
	GS_TOWER_MENU,		//User is choosing a tower from the menu
	GS_GAME_OVER		//Player has won or loose the game
};

class GameScreen : public IScreen
{
private:
	OSL_IMAGE *map;
	GameState mGameState;

public:
	GameScreen();

	virtual ~GameScreen();

	virtual void draw();

	virtual void update();

	const GameState GetGameState();

	void SetGameState(const GameState &newState);

};
#endif
