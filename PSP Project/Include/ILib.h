//**************************************************************************
//		PSP Project: 'Gods Defense' - ILib.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************


#ifndef ILIB_H_INCLUDED
#define ILIB_H_INCLUDED


#include <oslib/oslib.h>
#include "../Include/IScreen.h"
//#include "../Include/Sound.h"
#include "../Include/Resource.h"

extern OSL_FONT *gFont;
extern int gMenu;
extern bool bSound;
extern int loadState;


/** Draws a formatted string literal at the specified x and y positions.

\code
oslDrawStringf(0, 0, "Test string %i", 1);
\endcode */
#define oslDrawStringf(x, y, ...)               { char __str[1000]; sprintf(__str , __VA_ARGS__); oslDrawString(x, y, __str); }

#endif
