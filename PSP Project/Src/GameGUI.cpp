//**************************************************************************
//		PSP Project: 'Gods Defense' - GameGUI.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameGUI.h"

GameGUI *GameGUI::mHighLander = NULL;

static void GameGUI::InitGUI(GameScreen *gameLogic)
{
	if (gameLogic != NULL)
	{
		oslFatalError("Error GameLogic == NULL .");
		return;
	}
	
	mHighLander = new GameUI(gameLogic);
}

void GameGUI::LoadStuffs()
{
	//Load Cursor :D
	if (mCursor != NULL)
		oslDeleteImage(mCursor);
	
	mCursor = oslLoadImageFilePNG(Resource::IMG_CURSOR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	//Initialize variables
	mCursor->centerY = mCursor->sizeY / 2;
}

GameGUI::GameGUI(GameScreen *gameLogic)
{
	mGame = gameLogic;
	
	mCursor->x = 480/2;	//Place cursor at the center of the screen
	mCursor->y = 272/2;
}

void GameGUI::Update(unsigned timePassed)
{
	const GameState currentGameState = mGame->GetGameState();
	
	//Scroll the map
	if (currentGameState == GS_SCROLL_MAP || currentGameState == GS_MAP_PLACE_TOWER)
	{
		mCursor->x += (mCursor->x * timePassed) / 5;
		mCursor->y += (mCursor->y * timePassed) / 5;
	}
}