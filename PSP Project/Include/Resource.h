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
	static char const OPTIONS_CAPTION[];
	static char const ABOUT_TEXT[];
	static char const OPTIONS_SOUND[];
	static char const OPTIONS_ON[];
	static char const OPTIONS_OFF[];
	static char const BACK_SK[];
	static char const OPTIONS_CHANGE[];
	static char const PRESS_ANYKEY[];
	static char const GAME_TITLE[];
	static char const CONFIRM_QUIT[];
	static char const YES[];
	static char const NO[];
};


#undef DEFINE_RESOURCE


#endif
