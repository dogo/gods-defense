//**************************************************************************
//		PSP Project: 'Gods Defense' - ScreenManager.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************


#ifndef SCREENMANAGER_H_INCLUDED
#define SCREENMANAGER_H_INCLUDED

#include "../Include/ILib.h"

/**
* ScreenManager
*/
class ScreenManager
{

private:
	bool screenActive;

	bool activeScreen;

public:

	IScreen *mCurrentScreen;

	/**
	 * The screen indices.
	 */
	enum
	{
		SCREEN_ANYKEY = 0,
		SCREEN_TITLE = 1,
		SCREEN_MAIN_MENU = 2,
		SCREEN_GAME = 3,
		SCREEN_ABOUT = 4,
		SCREEN_MULTIPLAYER = 5,
		SCREEN_OPTIONS = 6,
		SCREEN_HELP = 7,
		SCREEN_ENDING = 8,
		SCREEN_WARNING = 9,
		SCREEN_GAME_OPTIONS = 10,
		SCREEN_PAUSE = 11,
		SCREEN_CONFIRM_EXIT = 12,
		NUM_SCREENS = 13

	};

	ScreenManager();

	virtual void activate(int aIndex);

	virtual void deactivate();

	virtual IScreen * createScreen(int aIndex);

	virtual bool isActive();
};
#endif
