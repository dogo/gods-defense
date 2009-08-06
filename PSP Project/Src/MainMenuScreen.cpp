//**************************************************************************
//		PSP Project: 'Gods Defense' - MainMenuScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MainMenuScreen.h"
#include "../Include/ScreenManager.h"


MainMenuScreen::MainMenuScreen()
{
	menubg = oslLoadImageFilePNG(Resource::IMG_MAIN_MENU_BG, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

MainMenuScreen::~MainMenuScreen()
{
	oslDeleteImage(menubg);
}

void MainMenuScreen::draw()
{
	oslDrawImageXY(menubg, (480/2) - (menubg->stretchX/2), (272/2) - (menubg->stretchY/2));
	(gMenu == 0) ? oslIntraFontSetStyle(gFont, 1.8f,RGBA(255,255,255,255), RGBA(0,0,0,255),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.2f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(340, 100,Resource::STR_START_GAME);
	(gMenu == 1) ? oslIntraFontSetStyle(gFont, 1.8f,RGBA(255,255,255,255), RGBA(0,0,0,255),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.2f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(340, 120,Resource::STR_MULTIPLAYER_CAPTION);
	(gMenu == 2) ? oslIntraFontSetStyle(gFont, 1.8f,RGBA(255,255,255,255), RGBA(0,0,0,255),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.2f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(340, 140,Resource::STR_HELP_CAPTION);
	(gMenu == 3) ? oslIntraFontSetStyle(gFont, 1.8f,RGBA(255,255,255,255), RGBA(0,0,0,255),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.2f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(340, 160,Resource::STR_ABOUT_CAPTION);
	(gMenu == 4) ? oslIntraFontSetStyle(gFont, 1.8f,RGBA(255,255,255,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.2f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(340, 180,Resource::STR_EXIT_CAPTION);
}

void MainMenuScreen::update()
{
	//menu keys
	if(osl_keys->pressed.up){
		gMenu--;
		if (gMenu < 0)
		{
			gMenu = 4;
		}
	}
	if(osl_keys->pressed.down){
		gMenu++;
		gMenu%=5;
	}
	if(osl_keys->pressed.cross){
		if(gMenu == 0)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_GAME_OPTIONS; // start game options!
		}
		if(gMenu == 1)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_MULTIPLAYER;
		}
		if(gMenu == 2)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_HELP;
		}
		if(gMenu == 3)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_ABOUT;
		}
		if(gMenu == 4)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_CONFIRM_EXIT;
		}
	}
}
