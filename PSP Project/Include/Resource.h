//**************************************************************************
//		PSP Project: 'Gods Defense' - Resource.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************


#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <oslib/oslib.h>

/**
 * Resource
 */
class Resource
{
public:
	/**
	 * Strings.
	 */
	static char const SETTINGS_FILENAME[]; //save
	static char const ABOUT_CAPTION[];
	static char const MULTIPLAYER_CAPTION[];
	static char const HELP_CAPTION[];
	static char const START_GAME[];
	static char const EXIT_CAPTION[];
	static char const OPTIONS_CAPTION[];
	static char const PAUSE_RESUME[];
	static char const PAUSE_MENU[];
	static char const PAUSE_CAPTION[];
	static char const ABOUT_TEXT[];
	static char const OPTIONS_SOUND[];
	static char const OPTIONS_ON[];
	static char const OPTIONS_OFF[];
	static char const BACK_SK[];
	static char const OPTIONS_CHANGE[];
	static char const PRESS_ANYKEY[];
	static char const CONFIRM_QUIT[];
	static char const YES[];
	static char const NO[];
	static char GAME_TITLE[];
	static char ANYKEY_SPLASH[];
	static char MAIN_MENU_BG[];
};


#undef DEFINE_RESOURCE


#endif
