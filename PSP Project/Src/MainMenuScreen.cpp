//**************************************************************************
//		PSP Project: 'Gods Defense' - MainMenuScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MainMenuScreen.h"
#include "../Include/util/MenuItem.h"
#include "../Include/ScreenManager.h"

bool gIsMultiplayer = false;

MainMenuScreen::MainMenuScreen()
{
    gIsMultiplayer = false;
    menubg = oslLoadImageFilePNG(Resource::IMG_MAIN_MENU_BG, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

    if (!menubg) {
        oslFatalError("At least one file is missing. Please copy all the files in the game directory.");
    }
}

MainMenuScreen::~MainMenuScreen()
{
    if (menubg != NULL) {
        oslDeleteImage(menubg);
    }
}

void MainMenuScreen::draw()
{
    oslDrawImageXY(menubg, (480/2) - (menubg->stretchX/2), (272/2) - (menubg->stretchY/2));
    
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

void MainMenuScreen::update(u32 /*timePassed*/) // Prevents compiler warning for unused parameter
{
    // Handle menu navigation
    if (osl_keys->pressed.up) {
        gMenu--;
        if (gMenu < 0) {
            gMenu = 5;
        }
    }
    if (osl_keys->pressed.down) {
        gMenu++;
        gMenu %= 6;
    }
    if (osl_keys->pressed.cross) {
        oslFlushKey();
        switch (gMenu) {
            case 0:
                mNextScreen = ScreenManager::SCREEN_GAME_OPTIONS; // Start game options!
                break;
            case 1:
#ifndef JPCSP_EMULATOR
                if (oslIsWlanPowerOn()) {
                    gIsMultiplayer = true;
                    mNextScreen = ScreenManager::SCREEN_MULTIPLAYER;
                } else {
                    mNextScreen = ScreenManager::SCREEN_WARNING;
                }
#else
                gIsMultiplayer = true;
                mNextScreen = ScreenManager::SCREEN_MULTIPLAYER;
#endif // JPCSP_EMULATOR
                break;
            case 2:
                mNextScreen = ScreenManager::SCREEN_HELP;
                break;
            case 3:
                mNextScreen = ScreenManager::SCREEN_TROPHIE;
                break;
            case 4:
                mNextScreen = ScreenManager::SCREEN_ABOUT;
                break;
            case 5:
                mNextScreen = ScreenManager::SCREEN_CONFIRM_EXIT;
                break;
        }
    }
}
