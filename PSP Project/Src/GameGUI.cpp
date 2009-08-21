//**************************************************************************
//		PSP Project: 'Gods Defense' - GameGUI.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameGUI.h"

GameGUI *GameGUI::sHighLander = NULL;
GameGUI *GameGUI::Instance()
{
	return sHighLander;
}

void GameGUI::InitGUI(GameScreen *gameLogic)
{
	if (sHighLander != NULL)
	{
		oslFatalError("Error GameLogic is not NULL .");
		return;
	}
	
	sHighLander = new GameGUI(gameLogic);
}

void GameGUI::LoadStuffs()
{
	//Load Cursor :D
	if (mCursor != NULL)
		oslDeleteImage(mCursor);
	if (mSidebar != NULL)
		oslDeleteImage(mSidebar);
	
	mCursor = oslLoadImageFilePNG(Resource::IMG_CURSOR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mSidebar = oslLoadImageFilePNG(Resource::IMG_SIDEBAR,OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	//Initialize variables
	mCursor->centerY = mCursor->sizeY / 2;
}

GameGUI::GameGUI(GameScreen *gameLogic)
{
	mGame = gameLogic;
	
	mCursor->x = 480/2;	//Place cursor at the center of the screen
	mCursor->y = 272/2;

	mPuttingTower = NULL; //none tower is building
	mCursor = NULL;
	mSidebar = NULL;
	mShowSidebar = false;
}

void GameGUI::Update(/*unsigned timePassed*/)
{	//Dogo : temporary removed, we need to change update
	/*const GameState currentGameState = mGame->GetGameState();
	
	//Scroll the map
	if (currentGameState == GS_SCROLL_MAP || currentGameState == GS_MAP_PLACE_TOWER)
	{
		mCursor->x += (mCursor->x * timePassed) / 5;
		mCursor->y += (mCursor->y * timePassed) / 5;
		CheckViewBounds();
	}*/
	if(osl_keys->pressed.square)
		mShowSidebar = !mShowSidebar ;
		
	oslPrintf_xy(0,20,"UpdateGUI");
}

void GameGUI::CheckViewBounds()
{
	//
	if (mCursor->x < 0)
		mCursor->x = 0;
	else if (mCursor->x > 464 -1) //psp 480 - 16 cursor - 1 fine tunning
		mCursor->x = 464 -1;

	if (mCursor->y < 0)
		mCursor->y = 0;
	else if (mCursor->y > 256 - 1) //psp 272 - 16 cursor -1 fine tunning
		mCursor->y = 256 - 1;

	mGame->SetView((480/2) - mCursor->x, (480/2) - mCursor->y);
}

void GameGUI::draw()
{
	if(mShowSidebar)
		oslDrawImageXY(mSidebar,480-48, 0);
}
void GameGUI::PuttingTower(Tower *tower)
{
	mGame->SetGameState(GS_MAP_PLACE_TOWER);
	mPuttingTower = tower;
}