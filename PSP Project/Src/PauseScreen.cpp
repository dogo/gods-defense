//**************************************************************************
//		PSP Project: 'Gods Defense' - PauseScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/PauseScreen.h"
#include "../Include/ScreenManager.h"


PauseScreen::PauseScreen()
{
}

void PauseScreen::draw()
{
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,120,"Game Paused");
}

void PauseScreen::update()
{
}
