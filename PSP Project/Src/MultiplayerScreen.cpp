//**************************************************************************
//		PSP Project: 'Gods Defense' - MultiplayerScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MultiplayerScreen.h"
#include "../Include/ScreenManager.h"

bool gIsClient = false;
bool gIsServer = false;

MultiplayerScreen::MultiplayerScreen()
{
	imgBack = oslLoadImageFilePNG(Resource::IMG_BACK, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	imgServer = oslLoadImageFilePNG(Resource::IMG_CROSS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	imgClient = oslLoadImageFilePNG(Resource::IMG_SQUARE, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	imgCover = oslLoadImageFilePNG(Resource::IMG_COVER, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	if (!imgBack || !imgClient || !imgServer || !imgCover)
		oslFatalError("At least one file is missing. Please copy all the file in the game directory.");

	gIsClient = false;
	gIsServer = false;
}

MultiplayerScreen::~MultiplayerScreen()
{
	oslDeleteImage(imgBack);
	oslDeleteImage(imgClient);
	oslDeleteImage(imgServer);
	oslDeleteImage(imgCover);
}

void MultiplayerScreen::draw()
{
	//Cover
	oslDrawImageXY(imgCover,0,0);

	//Title
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_MULTIPLAYER_CAPTION);
	
	//Options
	oslIntraFontSetStyle(gFont, 0.6f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	//Server
	oslDrawString(240,100,Resource::STR_ACT_LIKE_SERVER);
	oslDrawImageXY(imgServer, (145) - (imgServer->stretchX), (130) - (imgServer->stretchY));
	
	//Client
	oslDrawString(240,160,Resource::STR_ACT_LIKE_CLIENT);
	oslDrawImageXY(imgClient, (145) - (imgClient->stretchX), (190) - (imgClient->stretchY));
	
	//Back
	oslDrawImageXY(imgBack, (430) - (imgBack->stretchX), (272) - (imgBack->stretchY));
	oslIntraFontSetStyle(gFont, 0.7f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - imgBack->stretchX,(272) - (imgBack->stretchY/2),Resource::STR_BACK_SK);
}

void MultiplayerScreen::update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	if(osl_keys->pressed.circle)
	{	
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
	else if (osl_keys->pressed.square)
	{	
		gIsClient = true;
		gIsServer = false;
		mNextScreen = ScreenManager::SCREEN_GAME_OPTIONS;
	}
	else if (osl_keys->pressed.cross)
	{	
		gIsServer = true;
		gIsClient = false;
		mNextScreen = ScreenManager::SCREEN_GAME_OPTIONS;
	}
#ifndef JPCSP_EMULATOR
	if(!oslIsWlanPowerOn())
	{
		mNextScreen = ScreenManager::SCREEN_WARNING;
	}
#endif // JPCSP_EMULATOR
}
