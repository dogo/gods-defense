//**************************************************************************
//		PSP Project: 'Gods Defense' - AnykeyScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/TitleScreen.h"
#include "../Include/ScreenManager.h"


TitleScreen::TitleScreen()
{
	GDSplash = oslLoadImageFilePNG(Resource::IMG_GAME_TITLE, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

TitleScreen::~TitleScreen()
{
	oslDeleteImage(GDSplash);
}

void TitleScreen::draw()
{
	//draw logo image
	oslDrawImageXY(GDSplash, (480/2) - (GDSplash->stretchX/2), (272/2) - (GDSplash->stretchY/2));
	
	//Flashing
	float t = ((float)(clock() % CLOCKS_PER_SEC)) / ((float)CLOCKS_PER_SEC);
	int val = (t < 0.5f) ? t*511 : (1.0f-t)*511;
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255),(0xFF<<24)+(val<<16)+(val<<8)+(val),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,220,Resource::STR_PRESS_START);
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
}

void TitleScreen::update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	if(osl_keys->pressed.start)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU;
		oslPlaySound(menuTheme, CHANNEL_0); //Plays the sound in the menu
	}
}
