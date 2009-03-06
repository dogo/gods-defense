//**************************************************************************
//		PSP Project: 'Gods Defense' - MainMenuScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MainMenuScreen.h"
#include "../Include/ScreenManager.h"


MainMenuScreen::MainMenuScreen()
{
	//menubg = oslLoadImageFilePNG(Resource::MAIN_MENU_BG, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

MainMenuScreen::~MainMenuScreen()
{
	//oslDeleteImage(menubg);
}

void MainMenuScreen::draw()
{
	//oslDrawImageXY(menubg, (480/2) - (menubg->stretchX/2), (272/2) - (menubg->stretchY/2));
	(gMenu == 0) ? oslIntraFontSetStyle(gFont, 1.2f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 100,Resource::START_GAME);
	(gMenu == 1) ? oslIntraFontSetStyle(gFont, 1.2f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 120,Resource::MULTIPLAYER_CAPTION);
	(gMenu == 2) ? oslIntraFontSetStyle(gFont, 1.2f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 140,Resource::OPTIONS_CAPTION);
	(gMenu == 3) ? oslIntraFontSetStyle(gFont, 1.2f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 160,Resource::HELP_CAPTION);
	(gMenu == 4) ? oslIntraFontSetStyle(gFont, 1.2f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 180,Resource::ABOUT_CAPTION);
	(gMenu == 5) ? oslIntraFontSetStyle(gFont, 1.2f,RGBA(0,255,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,0,0,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 200,Resource::EXIT_CAPTION);
}

void MainMenuScreen::update()
{
}
