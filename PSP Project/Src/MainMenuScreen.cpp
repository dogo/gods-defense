//**************************************************************************
//		PSP Project: 'Gods Defense' - MainMenuScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MainMenuScreen.h"
#include "../Include/ScreenManager.h"

bool gIsMultiplayer = false;

MainMenuScreen::MainMenuScreen()
{
	gIsMultiplayer = false;
	menubg = oslLoadImageFilePNG(Resource::IMG_MAIN_MENU_BG, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	if (!menubg)
		oslFatalError("At least one file is missing. Please copy all the file in the game directory.");
}

MainMenuScreen::~MainMenuScreen()
{
	if(menubg != NULL)
		oslDeleteImage(menubg);
}

void MainMenuScreen::draw()
{
    oslDrawImageXY(menubg, (480/2) - (menubg->stretchX/2), (272/2) - (menubg->stretchY/2));
    
    struct MenuItem
    {
        const char* text;
        int yPosition;
    };
    
    MenuItem menuItems[] = {
        {Resource::STR_START_GAME, 100},
        {Resource::STR_MULTIPLAYER_CAPTION, 120},
        {Resource::STR_HELP_CAPTION, 140},
        {Resource::STR_TROPHIES_CAPTION, 160},
        {Resource::STR_ABOUT_CAPTION, 180},
        {Resource::STR_EXIT_CAPTION, 200}
    };
    
    for (int i = 0; i < sizeof(menuItems)/sizeof(menuItems[0]); ++i)
    {
        if (gMenu == i)
        {
            oslIntraFontSetStyle(gFont, 1.2f, RGBA(175,137,62,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER);
        }
        else
        {
            oslIntraFontSetStyle(gFont, 0.6f, RGBA(120,120,120,255), RGBA(0,0,0,0xFF), 0.f, INTRAFONT_ALIGN_CENTER);
        }
        oslDrawString(340, menuItems[i].yPosition, menuItems[i].text);
    }
}

void MainMenuScreen::update(u32 /*timePassed*/) //Parametro Formal, n�o d� warning
{
	//menu keys
	if(osl_keys->pressed.up){
		gMenu--;
		if (gMenu < 0)
		{
			gMenu = 5;
		}
	}
	if(osl_keys->pressed.down){
		gMenu++;
		gMenu%=6;
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
#ifndef JPCSP_EMULATOR
			if(oslIsWlanPowerOn())
			{
				gIsMultiplayer = true;
				mNextScreen = ScreenManager::SCREEN_MULTIPLAYER;
			}
			else
				mNextScreen = ScreenManager::SCREEN_WARNING;
#else
			gIsMultiplayer = true;
			mNextScreen = ScreenManager::SCREEN_MULTIPLAYER;
#endif // JPCSP_EMULATOR
		}
		if(gMenu == 2)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_HELP;
		}
		if(gMenu == 3)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_TROPHIE;
		}
		if(gMenu == 4)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_ABOUT;
		}
		if(gMenu == 5)
		{
			oslFlushKey();
			mNextScreen = ScreenManager::SCREEN_CONFIRM_EXIT;
		}
	}
}
