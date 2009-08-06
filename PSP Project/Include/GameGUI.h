//**************************************************************************
//		PSP Project: 'Gods Defense' - GameGUI.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_GAMEGUI_H
#define INCLUDED_GAMEGUI_H

#include "../Include/GodLibrary.h"
#include "../Include/GameScreen.h"

class GameGUI
{
public:
	void LoadStuffs();
	static void InitGUI(GameScreen *gameLogic);

private:
	GameGUI(GameScreen *gameLogic);

	GameScreen *mGame;
	OSL_IMAGE *mCursor;
	static GameGUI *mHighLander;
};

#endif