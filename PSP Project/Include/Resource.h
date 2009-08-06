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
	static char const STR_ABOUT_CAPTION[];
	static char const STR_MULTIPLAYER_CAPTION[];
	static char const STR_HELP_CAPTION[];
	static char const STR_START_GAME[];
	static char const STR_EXIT_CAPTION[];
	static char const STR_PAUSE_RESUME[];
	static char const STR_PAUSE_MENU[];
	static char const STR_PAUSE_CAPTION[];
	static char const STR_ABOUT_TEXT[];
	static char const STR_BACK_SK[];
	static char const STR_PRESS_START[];
	static char const STR_CONFIRM_QUIT[];
	static char const STR_YES[];
	static char const STR_NO[];
	static char const STR_WARNING_CAPTION[];
	static char const STR_WARNING_TEXT[];
	static char const STR_MAPSELECTION_CAPTION[];
	static char const STR_HELP_TEXT[];
	
	static char IMG_GAME_TITLE[];
	static char IMG_ANYKEY_SPLASH[];
	static char IMG_MAIN_MENU_BG[];
	static char IMG_CURSOR[];
};


#undef DEFINE_RESOURCE


#endif
