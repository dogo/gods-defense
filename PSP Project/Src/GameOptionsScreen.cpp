//**************************************************************************
//		PSP Project: 'Gods Defense' - GameOptionsScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameOptionsScreen.h"
#include "../Include/ScreenManager.h"


GameOptionsScreen::GameOptionsScreen()
{
}

void GameOptionsScreen::draw()
{
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,120,"No Game Options yet!");
	oslDrawString(240,160,"Press Cross to play!");
}

void GameOptionsScreen::update()
{
}
