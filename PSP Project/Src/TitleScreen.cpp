//**************************************************************************
//		PSP Project: 'Gods Defense' - AnykeyScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/TitleScreen.h"
#include "../Include/ScreenManager.h"


TitleScreen::TitleScreen()
{
}

void TitleScreen::draw()
{
	oslIntraFontSetStyle(gFont, 3.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,120,Resource::GAME_TITLE);
	
	//Flashing
	float t = ((float)(clock() % CLOCKS_PER_SEC)) / ((float)CLOCKS_PER_SEC);
	int val = (t < 0.5f) ? t*511 : (1.0f-t)*511;
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255),(0xFF<<24)+(val<<16)+(val<<8)+(val),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,220,Resource::PRESS_ANYKEY);
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
}

void TitleScreen::update()
{
}
