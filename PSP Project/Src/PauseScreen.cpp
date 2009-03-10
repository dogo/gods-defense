//**************************************************************************
//		PSP Project: 'Gods Defense' - PauseScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/PauseScreen.h"
#include "../Include/ScreenManager.h"


PauseScreen::PauseScreen()
{
	gMenu = 0;
}

void PauseScreen::draw()
{
	//Screen Title
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,40,Resource::PAUSE_CAPTION);

	//Screen Options
	(gMenu == 0) ? oslIntraFontSetStyle(gFont, 1.3f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 100,Resource::PAUSE_RESUME);
	(gMenu == 1) ? oslIntraFontSetStyle(gFont, 1.3f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 120,Resource::OPTIONS_CAPTION);
	(gMenu == 2) ? oslIntraFontSetStyle(gFont, 1.3f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 140,Resource::PAUSE_MENU);
}

void PauseScreen::update()
{
	if(osl_keys->pressed.circle || osl_keys->pressed.start)
	{
		oslFlushKey();
		Screen = ScreenManager::SCREEN_GAME; //go back CLR
	}
}
