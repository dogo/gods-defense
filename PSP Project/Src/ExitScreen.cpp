//**************************************************************************
//		PSP Project: 'Gods Defense' - ExitScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/ExitScreen.h"
#include "../Include/ScreenManager.h"
#include "../Include/util/MenuItem.h"

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
    oslDrawImageXY(mCover, 0, 0);

    oslIntraFontSetStyle(gFont, 1.0f, RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
    oslDrawString(240, 100, Resource::STR_CONFIRM_QUIT);

    MenuItem menuItems[] = {
        {Resource::STR_YES, 140},
        {Resource::STR_NO, 160}
    };

    for (int i = 0; i < sizeof(menuItems) / sizeof(menuItems[0]); ++i)
    {
        if (gMenu == i)
        {
            oslIntraFontSetStyle(gFont, 0.8f, RGBA(175,137,62,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER);
        }
        else
        {
            oslIntraFontSetStyle(gFont, 0.6f, RGBA(120,120,120,255), RGBA(0,0,0,0xFF), 0.f, INTRAFONT_ALIGN_CENTER);
        }
        oslDrawString(240, menuItems[i].yPosition, menuItems[i].text);
    }
}

void ExitScreen::update(u32 /*timePassed*/)
{
    if (osl_keys->pressed.up) {
        gMenu--;
        if (gMenu < 0) {
            gMenu = 1;
        }
    }
    if (osl_keys->pressed.down) {
        gMenu++;
        gMenu %= 2;
    }
    if (osl_keys->pressed.cross) {
        if (gMenu == 0) {
            oslStopSound(menuTheme);
            osl_quit = 1; // Quit Game
        }
        if (gMenu == 1) {
            oslFlushKey();
            gMenu = 0;
            mNextScreen = ScreenManager::SCREEN_MAIN_MENU;
        }
    }
    if (osl_keys->pressed.circle) {
        gMenu = 0;
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
    }
}