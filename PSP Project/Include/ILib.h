//**************************************************************************
//		PSP Project: 'Gods Defense' - ILib.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************


#ifndef ILIB_H_INCLUDED
#define ILIB_H_INCLUDED


#include <oslib/oslib.h>
#include "../Include/IScreen.h"
#include "../Include/Resource.h"
#include <string>

using namespace std;

extern OSL_FONT *gFont;
extern OSL_SOUND *menuTheme;
extern int gMenu;
extern short gState;
extern int gFade;
extern int gScreen;
extern int mNextScreen;
extern string gChoosedMap;

#endif
