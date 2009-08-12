//**************************************************************************
//		PSP Project: 'Gods Defense' - GameGUI.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_GAMEGUI_H
#define INCLUDED_GAMEGUI_H

#include "../Include/GodLibrary.h"
#include "../Include/GameScreen.h"

//Class Declarations
class GameScreen;

class GameGUI
{
public:
	void LoadStuffs();
	static GameGUI *Instance();
	static void InitGUI(GameScreen *gameLogic);
	void Update(unsigned timePassed);
	void draw();
	void PuttingTower(Tower *tower);

private:
	GameGUI(GameScreen *gameLogic);
	void CheckViewBounds();

	GameScreen *mGame;
	OSL_IMAGE *mCursor;
	static GameGUI *sHighLander;
	Tower *mPuttingTower;
};

#endif