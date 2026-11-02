//**************************************************************************
//		PSP Project: 'Gods Defense' - MainMenuScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MainMenuScreen.h"
#include "../Include/util/MenuItem.h"
#include "../Include/ScreenManager.h"
#include <math.h>

bool gIsMultiplayer = false;

MainMenuScreen::MainMenuScreen()
{
    gIsMultiplayer = false;
    menuButtons = Sprites::LoadSpriteFilePNG(Resource::IMG_MAIN_MENU_BUTTONS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888, 192, 28);
    menubg = oslLoadImageFilePNG(Resource::IMG_MAIN_MENU_BG, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

    if (!menubg || !menuButtons) {
        oslFatalError("At least one file is missing. Please copy all the files in the game directory.");
    }
}

MainMenuScreen::~MainMenuScreen()
{
    if (menuButtons != NULL) {
        oslDeleteImage(menuButtons);
    }
    if (menubg != NULL) {
        oslDeleteImage(menubg);
    }
}

void MainMenuScreen::draw()
{
    oslDrawImageXY(menubg, (480/2) - (menubg->stretchX/2), (272/2) - (menubg->stretchY/2));
    
    MenuItem menuItems[] = {
        {Resource::STR_START_GAME, 40},
        {Resource::STR_MULTIPLAYER_CAPTION, 70},
        {Resource::STR_HELP_CAPTION, 100},
        {Resource::STR_TROPHIES_CAPTION, 130},
        {Resource::STR_ABOUT_CAPTION, 160},
        {Resource::STR_EXIT_CAPTION, 190}
    };

    for (int i = 0; i < (int)(sizeof(menuItems)/sizeof(menuItems[0])); ++i)
    {
        const bool selected = gMenu == i;
        oslSetImageFrame(menuButtons, selected ? 1 : 0);
        if (selected)
        {
            int brightness = 235 + (int)(20 * sinf(osl_vblCount * 0.06f));
            oslSetAlpha(OSL_FX_TINT, RGBA(brightness, brightness, brightness, 255));
        }
        oslDrawImageXY(menuButtons, 268, menuItems[i].yPosition);
        oslSetAlpha(OSL_FX_DEFAULT, 0);
    }

    // intraFont changes the GU texture; draw labels after all button images.
    for (int i = 0; i < (int)(sizeof(menuItems)/sizeof(menuItems[0])); ++i)
    {
        const bool selected = gMenu == i;
        oslIntraFontSetStyle(gFont, 0.60f,
            selected ? RGBA(255,232,163,255) : RGBA(225,214,192,255),
            RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER);
        oslDrawString(364, menuItems[i].yPosition + 10, menuItems[i].text);
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
