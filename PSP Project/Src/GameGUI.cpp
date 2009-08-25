//**************************************************************************
//		PSP Project: 'Gods Defense' - GameGUI.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameGUI.h"

GameGUI *GameGUI::sGameGUIReference = NULL;

GameGUI *GameGUI::Instance()
{
	return sGameGUIReference;
}

void GameGUI::InitGUI(GameScreen *gameLogic)
{
	if (sGameGUIReference != NULL)
	{
		oslFatalError("Error GameLogic is not NULL.");
		return;
	}
	
	sGameGUIReference = new GameGUI(gameLogic);
}

GameGUI::~GameGUI()
{
	if (mCursor != NULL)
		oslDeleteImage(mCursor);
	if (mSidebar != NULL)
		oslDeleteImage(mSidebar);
	if (mSelectorSidebar != NULL)
		oslDeleteImage(mSelectorSidebar);
	
	sGameGUIReference = NULL;
}

void GameGUI::LoadStuffs()
{
	//Load Cursor :D
	if (mCursor != NULL)
		oslDeleteImage(mCursor);
	if (mSidebar != NULL)
		oslDeleteImage(mSidebar);
	if (mSelectorSidebar != NULL)
		oslDeleteImage(mSelectorSidebar);
	
	mCursor = oslLoadImageFilePNG(Resource::IMG_CURSOR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mSidebar = oslLoadImageFilePNG(Resource::IMG_SIDEBAR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mSelectorSidebar = oslLoadImageFilePNG(Resource::IMG_SELECTOR_SIDEBAR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	//Initialize variables
	mCursor->centerY = mCursor->sizeY / 2;
	mCursor->x = 480/2;	//Place cursor at the center of the screen
	mCursor->y = 272/2;
}

GameGUI::GameGUI(GameScreen *gameLogic)
{
	mGame = gameLogic;
	mPuttingTower = NULL; //none tower is building
	mCursor = NULL;
	mSidebar = NULL;
	mShowSidebar = false;
	mSelectorSidebar = NULL;
	mSelectedItemY = 0;
}

void GameGUI::Update(/*unsigned timePassed*/)
{
	const GameState currentGameState = mGame->GetGameState();
	int i;

	//Scroll the map
	if (currentGameState == GS_SCROLL_MAP || currentGameState == GS_MAP_PLACE_TOWER)
	{
		for (i=32;i<=120;i+=48)
		{
			//Move X Coords
			if (osl_keys->analogX > i)
				mCursor->x += 2;                
			if (osl_keys->analogX < -i)
				mCursor->x -= 2;                

			//Move Y Coords
			if (osl_keys->analogY > i)
				mCursor->y += 2;                
			if (osl_keys->analogY < -i)
				mCursor->y -= 2;                
		}
		CheckViewBounds();
	}

	else if (currentGameState == GS_TOWER_MENU)
	{
		if (osl_keys->pressed.up)
			mSelectedItemY = (mSelectedItemY-1+4)%4;
		if (osl_keys->pressed.down)
			mSelectedItemY = (mSelectedItemY+1)%4;
						
		if (osl_keys->pressed.cross)
		{
			SelectedTowerItem();
		}
		
		if (osl_keys->pressed.square)
		{
			mShowSidebar = !mShowSidebar;
			mGame->SetGameState(GS_SCROLL_MAP);
		}
	}

	if((osl_keys->pressed.square) && (currentGameState == GS_SCROLL_MAP || currentGameState == GS_MAP_PLACE_TOWER))
	{
		mGame->SetGameState(GS_TOWER_MENU);
		mShowSidebar = !mShowSidebar;
	}
		
	oslPrintf_xy(0,20,"UpdateGUI");
}

void GameGUI::CheckViewBounds()
{
	if (mCursor->x < 0)
		mCursor->x = 0;
	else if (mCursor->x > 464 -1) //psp 480 - 16 cursor - 1 fine tunning
		mCursor->x = 464 -1;

	if (mCursor->y < 8) //0 + 16/2 cursor
		mCursor->y = 8;
	else if (mCursor->y > 264 - 1) //psp 272 - 16/2 cursor -1 fine tunning
		mCursor->y = 264 - 1;
}

void GameGUI::draw()
{
	if(mShowSidebar)
	{
		oslDrawImageXY(mSidebar,480-48, 0);
		oslDrawImageXY(mSelectorSidebar, 480-40, 29 + (mSelectedItemY * 61)); //(PSP Screen - sidebar - 8 to align, Side bar spacing + (Selected Item * Image->Y));
	}
	oslDrawImage(mCursor);
}
void GameGUI::PuttingTower(Tower *tower)
{
	mGame->SetGameState(GS_MAP_PLACE_TOWER);
	mPuttingTower = tower;
}

void GameGUI::SelectedTowerItem()
{
	/*if (mTowerItems[0][mSelectedItemY] == NULL)
	{
		return;
	}
	else
	{
		mTowerItems[0][mSelectedItemY];
	}*/
}