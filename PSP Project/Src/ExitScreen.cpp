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

ExitScreen::~ExitScreen()
{
}

void ExitScreen::draw()
{
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,120,Resource::STR_CONFIRM_QUIT);
	(gMenu == 0) ? oslIntraFontSetStyle(gFont, 1.4f,RGBA(255,255,255,255), RGBA(0,0,0,255),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.2f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,160,Resource::STR_YES);
	(gMenu == 1) ? oslIntraFontSetStyle(gFont, 1.4f,RGBA(255,255,255,255), RGBA(0,0,0,255),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.2f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,180,Resource::STR_NO);
}

void ExitScreen::update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	if(osl_keys->pressed.up){
		gMenu--;
		if (gMenu < 0)
		{
			gMenu = 1;
		}
	}
	if(osl_keys->pressed.down){
		gMenu++;
		gMenu%=2;
	}
	if(osl_keys->pressed.cross){
		if(gMenu == 0)
		{
			oslStopSound(menuTheme);
			osl_quit = 1; //Quit Game
		}
		if(gMenu == 1)
		{
			oslFlushKey();
			gMenu = 0;
			mNextScreen = ScreenManager::SCREEN_MAIN_MENU;
		}
	}
	if(osl_keys->pressed.circle)
	{
		gMenu = 0;
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}