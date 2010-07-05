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
	if (mUpgradebar != NULL)
		oslDeleteImage(mUpgradebar);
	if (mSelectorSidebar != NULL)
		oslDeleteImage(mSelectorSidebar);
	if (mHud != NULL)
		oslDeleteImage(mHud);
	if (mSell != NULL)
		oslDeleteImage(mSell);
	if (mUpgrade != NULL)
		oslDeleteImage(mUpgrade);
	
	sGameGUIReference = NULL;
}

void GameGUI::LoadStuffs()
{
	//Load Cursor :D
	if (mCursor != NULL)
		oslDeleteImage(mCursor);
	if (mSidebar != NULL)
		oslDeleteImage(mSidebar);
	if (mUpgradebar != NULL)
		oslDeleteImage(mUpgradebar);
	if (mSelectorSidebar != NULL)
		oslDeleteImage(mSelectorSidebar);
	if (mHud != NULL)
		oslDeleteImage(mHud);
	if (mSell != NULL)
		oslDeleteImage(mSell);
	if (mUpgrade != NULL)
		oslDeleteImage(mUpgrade);
	
	mCursor = oslLoadImageFilePNG(Resource::IMG_CURSOR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mSidebar = oslLoadImageFilePNG(Resource::IMG_SIDEBAR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mUpgradebar = oslLoadImageFilePNG(Resource::IMG_UPGRADEBAR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mSelectorSidebar = oslLoadImageFilePNG(Resource::IMG_SELECTOR_SIDEBAR, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mHud = oslLoadImageFilePNG(Resource::IMG_HUD, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mSell = oslLoadImageFilePNG(Resource::IMG_SELL, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mUpgrade = oslLoadImageFilePNG(Resource::IMG_UPGRADE, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	//Initialize variables
	mCursor->x = 480/2;	//Place cursor at the center of the screen
	mCursor->y = 272/2;

	string *menuTowers = mGame->GetMenuTowers();

	for (int y = 0; y < 4; y++)
	{
		if (menuTowers[y] == "")
		{
			mTowerItems[y] = NULL;
		}
		else
		{
			Tower *mCurrentTower = mGame->GetTower(menuTowers[y]);
			if (mCurrentTower != NULL)
				mTowerItems[y] = new SidebarItem(mCurrentTower, y);
		}
	}
}

GameGUI::GameGUI(GameScreen *gameLogic)
{
	mGame = gameLogic;
	mPuttingTower = NULL; //none tower is building
	mCursor = NULL;
	mSidebar = NULL;
	mUpgradebar = NULL;
	mHud = NULL;
	mSell = NULL;
	mUpgrade = NULL;
	mSelectorSidebar = NULL;
	mShowSidebar = false;
	mShowUpgradebar = false;
	mSelectedItemY = 0;
	mSelectedItemX = 0;
}

void GameGUI::Update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	const GameState currentGameState = mGame->GetGameState();
	const GameConnectionState currentGameConnectionState = mGame->GetGameConnectionState();
	int i;
#ifdef _DEBUG
	oslPrintf_xy(0,20,"currentGameState %d",currentGameState);
#endif
#ifndef JPCSP_EMULATOR
	//Server must wait other player to start 
	if(gIsServer && oslIsWlanPowerOn() && currentGameConnectionState == GCS_WAITING_CONNECTION)
		return;
#endif

	if(currentGameState == GS_GAME_LOADED)
	{
		oslMessageBox(mGame->GetGameMap()->mDescription[0], Resource::STR_MAP_DESC, oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
		mGame->SetGameState(GS_SCROLL_MAP);
	}

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
		if (osl_keys->pressed.triangle) // Next Wave
		{
			mGame->TryRunNextWave();
		}
		if(osl_keys->pressed.square)
		{
			mPuttingTower = NULL;
			mShowSidebar = !mShowSidebar;
			mGame->SetGameState(GS_TOWER_MENU);
		}
		else if(osl_keys->pressed.circle)
		{
			mPuttingTower = NULL;
			mGame->SetGameState(GS_SCROLL_MAP);
		}

		else if (osl_keys->pressed.cross)
		{
			if (currentGameState == GS_SCROLL_MAP)
			{
				if(mGame->TrySelectTower(Coordinates2D::Coordinates2D(mCursor->x, mCursor->y + fabsf(mGame->GetGameMap()->mScrollAmount))))
				{
					mShowUpgradebar = !mShowUpgradebar;
				}
			}
			else if (currentGameState == GS_MAP_PLACE_TOWER)
			{
				if (mGame->TryBuildTower(mPuttingTower, Coordinates2D::Coordinates2D(mCursor->x, mCursor->y + fabsf(mGame->GetGameMap()->mScrollAmount))))
				{
					mPuttingTower = NULL;					
					mGame->SetGameState(GS_SCROLL_MAP);
				}
				else
				{
					oslMessageBox("Can't build here.", "Warning", oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
				}
			}
		}
		CheckViewBounds();
	}

	if ((currentGameState == GS_TOWER_MENU) && (mShowSidebar))
	{
		if (osl_keys->pressed.up)
			mSelectedItemY = (mSelectedItemY-1+4)%4;
		else if (osl_keys->pressed.down)
			mSelectedItemY = (mSelectedItemY+1)%4;

		else if (osl_keys->pressed.cross)
		{
			mShowSidebar = !mShowSidebar;
			SelectedTowerItem();
		}
		else if ((osl_keys->pressed.square) || (osl_keys->pressed.circle) || (osl_keys->pressed.start))
		{
			mShowSidebar = !mShowSidebar;
			mGame->SetGameState(GS_SCROLL_MAP);
		}
	}
	if ((currentGameState == GS_TOWER_UPGRADE_SELL) && (mShowUpgradebar))
	{
		if (osl_keys->pressed.left)
			mSelectedItemX = (mSelectedItemX-1+2)%2;
		else if (osl_keys->pressed.right)
			mSelectedItemX = (mSelectedItemX+1)%2;

		else if ((osl_keys->pressed.circle) || (osl_keys->pressed.start))
		{
			mShowUpgradebar = !mShowUpgradebar;
			mGame->SetGameState(GS_SCROLL_MAP);
		}

		else if (osl_keys->pressed.cross)
		{
			if((mSelectedItemX == 0) && (mGame->TryUpgradeSelectedTower()))
			{
				mShowUpgradebar = !mShowUpgradebar;
				mGame->SetGameState(GS_SCROLL_MAP);
			}
			else if((mSelectedItemX == 0) && (!mGame->TryUpgradeSelectedTower()))
			{
				oslMessageBox("Can't upgrade.", "Warning", oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
			}
			if((mSelectedItemX == 1) && (mGame->TrySellSelectedTower()))
			{
				mShowUpgradebar = !mShowUpgradebar;
				mGame->SetGameState(GS_SCROLL_MAP);
			}
		}
	}
}

void GameGUI::RenderPlacingTower()
{
	const GameState currentGameState = mGame->GetGameState();

	if (currentGameState == GS_MAP_PLACE_TOWER)
	{
		Coordinates2D buildingPosition = Coordinates2D::Coordinates2D(mCursor->x, mCursor->y+fabsf(mGame->GetGameMap()->mScrollAmount));
		//Snap :D \o/ workss
		buildingPosition.X = (((int)(buildingPosition.X) / 32) * 32) + 16; // 32 == Width
		buildingPosition.Y = (((int)(buildingPosition.Y) / 32) * 32) + 16; // 32 == Heigth
		mPuttingTower->RenderRangeCircle(buildingPosition, 0, COLOR_RED);
		mPuttingTower->RenderTower(buildingPosition);
	}
}

void GameGUI::CheckViewBounds()
{
	if (mCursor->x < 0)
		mCursor->x = 0;
	else if (mCursor->x > 464 -1) //psp 480 - 16 cursor - 1 fine tunning
		mCursor->x = 464 -1;

	if (mCursor->y < 0)
		mCursor->y = 0;
	else if (mCursor->y > 256 - 1) //psp 272 - 16 cursor -1 fine tunning
		mCursor->y = 256 - 1;
}

void GameGUI::draw()
{

	GameState currentGameState = mGame->GetGameState();

	if(mShowSidebar && currentGameState == GS_TOWER_MENU)
	{
		oslDrawImageXY(mSidebar, (480-48), 0);
		for (int y = 0; y < 4; y++)
		{
			if (mTowerItems[y] == NULL)
			{
				continue; //Workaround :D
			}
			else
			{
				mTowerItems[y]->drawIcons();
			}
		}
		oslDrawImageXY(mSelectorSidebar, (480-43), 26 + (mSelectedItemY * 61)); //(PSP Screen - sidebar - 8 to align, Side bar spacing + (Selected Item * Image->Y));
		mTowerItems[mSelectedItemY]->drawTowerInfo(mSelectedItemY);
	}
	else if (mShowUpgradebar && currentGameState == GS_TOWER_UPGRADE_SELL)
	{
		oslDrawImageXY(mUpgradebar, 0, (272-48));
		oslDrawImageXY(mUpgrade, 28, (272-40));
		oslDrawImageXY(mSell, 89, (272-40));
		oslDrawImageXY(mSelectorSidebar, 26 + (mSelectedItemX * 61), (272-42));
		drawUpgradeSellInfo(mSelectedItemX);
	}
	oslDrawImageXY(mHud, 0, 0);
	oslDrawImage(mCursor);
	updateHud();
}
void GameGUI::PuttingTower(Tower *tower)
{
	mGame->SetGameState(GS_MAP_PLACE_TOWER);
	mPuttingTower = tower;
}

Tower *GameGUI::getTowerReference()
{
	return gTowerReference;
}

void GameGUI::setTowerReference(Tower *tower)
{
	gTowerReference = tower;
}

void GameGUI::SelectedTowerItem()
{
	if (mTowerItems[mSelectedItemY] == NULL)
	{
		return;
	}
	else
	{
		setTowerReference(mTowerItems[mSelectedItemY]->mTower);
		mTowerItems[mSelectedItemY]->Selected();
	}
}

//Heads-up display
void GameGUI::updateHud()
{
	//Update gold
	char goldBuffer[256];
	sprintf(goldBuffer, "%i", mGame->GetPlayerMoney());
	oslIntraFontSetStyle(gFont, 0.55f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
	oslDrawStringLimited(27, 7, 55, goldBuffer);

	//Update Lives
	char liveBuffer[256];
	sprintf(liveBuffer, "%i", mGame->GetPlayerLives());
	oslIntraFontSetStyle(gFont, 0.55f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
	oslDrawStringLimited(90, 7, 40, liveBuffer);
}

void SidebarItem::Selected()
{
	GameGUI *gamegui = GameGUI::Instance();
	Tower *mTower = gamegui->getTowerReference();

	if (mTower->mIsBuildable)
	{
		if (gamegui->mGame->GetPlayerMoney() >= mTower->mTowerVector[0].mCost)
		{
			gamegui->PuttingTower(mTower);
		}
		else
		{
			oslMessageBox("More gold is required.", "Warning", oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
			gamegui->mGame->SetGameState(GS_SCROLL_MAP);
		}
	}
}

SidebarItem::SidebarItem(Tower *tower, const int &y)
{
	mTower = tower;
	mY = y;
	mIcon = mTower->mMenuIcon;
}

SidebarItem::~SidebarItem()
{
	//06 job
}

void SidebarItem::drawIcons()
{	
	oslDrawImageXY(mIcon, (480-40),29 + (mY * 61));
}

void SidebarItem::drawTowerInfo(int y)
{
	char costBuffer[256];
	sprintf(costBuffer, "Cost: %i", mTower->mTowerVector[0].mCost); //Building is always 0
	oslIntraFontSetStyle(gFont, 0.45f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
	oslDrawString((480 -48 - (oslGetStringWidth(mTower->mTowerName))), 29 + (y * 61), mTower->mTowerName);
	oslDrawString((480 -48 - (oslGetStringWidth(mTower->mTowerName))), 42 + (y * 61), costBuffer);
}

void GameGUI::drawUpgradeSellInfo(int x)
{
	char costBuffer[256];
	Tower *mTower = mGame->GetSelectedTower();
	oslIntraFontSetStyle(gFont, 0.45f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
	
	if(x == 0)
	{	
		if(mGame->mSelectedTower->mTowerLevel+1 < mTower->mTowerVector.size())
		{
			sprintf(costBuffer, "Upgrade Cost: %i", mTower->mTowerVector[mGame->GetSelectedTowerLevel()+1].mCost);
			oslDrawString( 2, 272-60, costBuffer);
		}
		else
		{
			oslDrawString( 2, 272-60, Resource::STR_MAX_REACHED);
		}
	}
	else
	{
		sprintf(costBuffer, "Sell Amount: %i", mTower->mTowerVector[mGame->GetSelectedTowerLevel()].mSellAmount);
		oslDrawString( 89, 272-60, costBuffer);
	}
}