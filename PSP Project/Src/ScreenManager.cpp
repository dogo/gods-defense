//**************************************************************************
//		PSP Project: 'Gods Defense' - ScreenManager.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/ScreenManager.h"
#include "../Include/AnykeyScreen.h"
#include "../Include/TitleScreen.h"
#include "../Include/MainMenuScreen.h"
#include "../Include/GameOptionsScreen.h"
#include "../Include/GameScreen.h"
#include "../Include/HelpScreen.h"
#include "../Include/AboutScreen.h"
#include "../Include/MultiplayerScreen.h"
#include "../Include/PauseScreen.h"
#include "../Include/ExitScreen.h"
#include "../Include/WarningScreen.h"

ScreenManager::ScreenManager()
{
	activeScreen = false;
}

void ScreenManager::activate(int aIndex)
{
	if(!activeScreen){
		mCurrentScreen = ScreenManager::createScreen(aIndex);
		gScreen = aIndex;
		mNextScreen = -1;
		activeScreen = true;
	}
}

bool ScreenManager::isActive()
{
	return activeScreen;
}

void ScreenManager::deactivate()
{
	delete(mCurrentScreen);
	mCurrentScreen = NULL;
	activeScreen = false;
	gScreen = -1;
}

IScreen * ScreenManager::createScreen(int aIndex)
{
	switch(aIndex)
	{
	case SCREEN_ANYKEY:				return new AnykeyScreen();
	case SCREEN_WARNING: 			return new WarningScreen();
	case SCREEN_TITLE: 				return new TitleScreen();
	case SCREEN_MAIN_MENU: 			return new MainMenuScreen();
	case SCREEN_GAME: 				return new GameScreen();
	case SCREEN_GAME_OPTIONS:		return new GameOptionsScreen();
	case SCREEN_ENDING:				return 0;//new EndingScreen(mLibrary, mContext);
	case SCREEN_HELP: 				return new HelpScreen();
	case SCREEN_MULTIPLAYER:		return new MultiplayerScreen();
	case SCREEN_ABOUT: 				return new AboutScreen();
	case SCREEN_PAUSE:				return new PauseScreen();
	case SCREEN_CONFIRM_EXIT:		return new ExitScreen();
	default: 						return NULL;
	}
}
