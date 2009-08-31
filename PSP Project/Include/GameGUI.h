//**************************************************************************
//		PSP Project: 'Gods Defense' - GameGUI.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_GAMEGUI_H
#define INCLUDED_GAMEGUI_H

#include "../Include/GodLibrary.h"
#include "../Include/GameScreen.h"
#include "../Include/Tower.h"
#include "../Include/Map.h"

//Class Declarations
class GameGUI;
class GameScreen;
class SidebarItem;
class TowerMenuItem;

class GameGUI
{
public:
	~GameGUI();
	void LoadStuffs();
	static GameGUI *Instance();
	static void InitGUI(GameScreen *gameLogic);
	void Update(/*unsigned timePassed*/);
	void draw();
	void PuttingTower(Tower *tower);

private:
	GameGUI(GameScreen *gameLogic);
	void CheckViewBounds();
	void SelectedTowerItem();

	GameScreen *mGame;
	OSL_IMAGE *mCursor;
	OSL_IMAGE *mSidebar;
	OSL_IMAGE *mSelectorSidebar;
	static GameGUI *sGameGUIReference;
	Tower *mPuttingTower;
	bool mShowSidebar;
	int mSelectedItemY;
	SidebarItem *mTowerItems[4];
};

class SidebarItem
{
public:
	void drawIcons(const bool &selected);

	int mY;

protected:
	OSL_IMAGE *mMenuIcon;

	~SidebarItem();
};

class TowerMenuItem : public SidebarItem
{
public:
	TowerMenuItem(Tower *tower, const int &y);

	Tower *mTower;
protected:
	~TowerMenuItem();
};

#endif