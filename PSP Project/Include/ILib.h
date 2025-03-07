//**************************************************************************
//		PSP Project: 'Gods Defense' - ILib.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************


#ifndef ILIB_H_INCLUDED
#define ILIB_H_INCLUDED


#include <oslib/oslib.h>
#include "../Include/IScreen.h"
#include "../Include/Resource.h"
#include "../Include/util/Sprites.h"
#include "../Include/util/Drawing.h"
#include <string>

using namespace std;

extern OSL_FONT *gFont;
extern OSL_SOUND *menuTheme;
extern OSL_IMAGE *pEllipse;
extern int gMenu;
extern short gState;
extern int gFade;
extern int gScreen;
extern int mNextScreen;
extern string gChoosedMap;
extern bool gWin;
extern char gScoreBuffer[256];
extern bool gIsMultiplayer;
extern bool gIsServer;
extern bool gIsClient;
extern char nameList[][20];

/*
	Sound Channels
*/

#define CHANNEL_0 0
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define CHANNEL_4 4
#define CHANNEL_5 5
#define CHANNEL_6 6
#define CHANNEL_7 7

#endif
