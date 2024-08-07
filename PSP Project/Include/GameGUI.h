//**************************************************************************
//		PSP Project: 'Gods Defense' - GameGUI.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_GAMEGUI_H
#define INCLUDED_GAMEGUI_H

#include "../Include/GameScreen.h"
#include "../Include/Tower.h"
#include "../Include/Map.h"
#include <math.h>

//Class Declarations
class GameGUI;
class GameScreen;
class SidebarItem;

#define COLOR_RED RGB(255, 0, 0)
#define COLOR_BLUE RGB(0, 0, 255)
#define COLOR_GREEN RGB(0, 255, 0)
#define COLOR_WHITE RGB(255, 255, 255)
#define ALPHA_COLOR_BLACK RGBA(0, 0, 0, 128)

class GameGUI
{
public:
	~GameGUI();
	void LoadStuffs();
	static GameGUI *Instance();
	static void InitGUI(GameScreen *gameLogic);
	void Update(u32 timePassed);
	void draw();
	void PuttingTower(Tower *tower);
	void setTowerReference(Tower *tower);
	Tower *getTowerReference();
	void RenderPlacingTower();
	void updateHud();
	void drawUpgradeSellInfo(int x);

	Tower *gTowerReference;
	GameScreen *mGame;

private:
	GameGUI(GameScreen *gameLogic);
	void CheckViewBounds();
	void SelectedTowerItem();

	OSL_IMAGE *mCursor;
	OSL_IMAGE *mSidebar;
	OSL_IMAGE *mUpgradebar;
	OSL_IMAGE *mSelectorSidebar;
	OSL_IMAGE *mHud;
	OSL_IMAGE *mSell;
	OSL_IMAGE *mUpgrade;
	static GameGUI *sGameGUIReference;
	Tower *mPuttingTower;
	bool mShowSidebar;
	bool mShowUpgradebar;
	int mSelectedItemY;
	int mSelectedItemX;
	SidebarItem *mTowerItems[4];
};

class SidebarItem
{
public:
	SidebarItem(Tower *tower, const int &y);
	void drawIcons();
	void drawTowerInfo(int y);
	void Selected();

	int mY;
	Tower *mTower;

protected:
	OSL_IMAGE *mIcon;

	~SidebarItem();
};
#endif