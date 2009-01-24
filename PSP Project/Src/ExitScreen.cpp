//**************************************************************************
//		PSP Project: 'Gods Defense' - ExitScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/ExitScreen.h"
#include "../Include/ScreenManager.h"


ExitScreen::ExitScreen()
{
	gMenu = 0;
}

void ExitScreen::draw()
{
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,120,Resource::CONFIRM_QUIT);
	(gMenu == 0) ? oslIntraFontSetStyle(gFont, 1.0f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,160,Resource::YES);
	(gMenu == 1) ? oslIntraFontSetStyle(gFont, 1.0f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,180,Resource::NO);
}

void ExitScreen::update()
{
}