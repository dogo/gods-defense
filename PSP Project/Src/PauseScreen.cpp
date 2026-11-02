//**************************************************************************
//		PSP Project: 'Gods Defense' - PauseScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/PauseScreen.h"
#include "../Include/ScreenManager.h"
#include "../Include/util/MenuItem.h"
#include <math.h>


PauseScreen::PauseScreen()
{
	gMenu = 0;
	menuButtons = Sprites::LoadSpriteFilePNG(Resource::IMG_MAIN_MENU_BUTTONS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888, 192, 28);
	if (!menuButtons) {
		oslFatalError("At least one file is missing. Please copy all the files in the game directory.");
	}
}

PauseScreen::~PauseScreen()
{
	if (menuButtons != NULL) {
		oslDeleteImage(menuButtons);
	}
}

void PauseScreen::draw()
{
	oslDrawFillRect(0, 0, 480, 272, RGBA(9,7,5,255));
	oslDrawFillRect(108, 48, 372, 224, RGBA(93,64,18,255));
	oslDrawFillRect(110, 50, 370, 222, RGBA(189,149,36,255));
	oslDrawFillRect(111, 51, 369, 221, RGBA(20,12,8,255));
	oslDrawFillRect(136, 98, 344, 99, RGBA(93,64,18,255));

	MenuItem menuItems[] = {
		{Resource::STR_PAUSE_RESUME, 116},
		{Resource::STR_PAUSE_MENU, 156}
	};
	for (int i = 0; i < 2; ++i)
	{
		oslSetImageFrame(menuButtons, gMenu == i ? 1 : 0);
		if (gMenu == i)
		{
			int brightness = 235 + (int)(20 * sinf(osl_vblCount * 0.06f));
			oslSetAlpha(OSL_FX_TINT, RGBA(brightness, brightness, brightness, 255));
		}
		oslDrawImageXY(menuButtons, 144, menuItems[i].yPosition);
		oslSetAlpha(OSL_FX_DEFAULT, 0);
	}

	// intraFont changes the GU texture; draw labels after all button images.
	oslIntraFontSetStyle(gFont, 0.85f, RGBA(255,232,163,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 71, Resource::STR_PAUSE_CAPTION);
	for (int i = 0; i < 2; ++i)
	{
		oslIntraFontSetStyle(gFont, 0.60f,
			gMenu == i ? RGBA(255,232,163,255) : RGBA(225,214,192,255),
			RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER);
		oslDrawString(240, menuItems[i].yPosition + 10, menuItems[i].text);
	}
}

void PauseScreen::update(u32 /*timePassed*/)
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
	if(osl_keys->pressed.circle)
	{
		oslFlushKey();
		GameScreen::gPauseGame = !GameScreen::gPauseGame;
		GameScreen::gGameReference->SetGameState(GS_SCROLL_MAP); //go back CLR
	}
	if(osl_keys->pressed.cross)
	{
		oslFlushKey();
		if(gMenu == 0)
		{
			GameScreen::gPauseGame = !GameScreen::gPauseGame;
			GameScreen::gGameReference->SetGameState(GS_SCROLL_MAP); //go back CLR
		}
		else if (gMenu == 1)
		{
			mNextScreen = ScreenManager::SCREEN_MAIN_MENU;
			gMenu = 0;
			oslPlaySound(menuTheme, CHANNEL_0); //Plays the menu sound
		}
	}
}
