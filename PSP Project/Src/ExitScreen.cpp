//**************************************************************************
//		PSP Project: 'Gods Defense' - ExitScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/ExitScreen.h"
#include "../Include/ScreenManager.h"


ExitScreen::ExitScreen()
{
	mCover = oslLoadImageFilePNG(Resource::IMG_COVER, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	gMenu = 0;
}

ExitScreen::~ExitScreen()
{
	oslDeleteImage(mCover);
}

void ExitScreen::draw()
{
	oslDrawImageXY(mCover,0,0);
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,100,Resource::STR_CONFIRM_QUIT);
	(gMenu == 0) ? oslIntraFontSetStyle(gFont, 0.8f,RGBA(175,137,62,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 0.6f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,140,Resource::STR_YES);
	(gMenu == 1) ? oslIntraFontSetStyle(gFont, 0.8f,RGBA(175,137,62,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 0.6f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,160,Resource::STR_NO);
}

void ExitScreen::update(u32 /*timePassed*/) //Parametro Formal, n�o d� warning
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