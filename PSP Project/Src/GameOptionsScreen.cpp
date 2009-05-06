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
	oslDrawString(240,40,Resource::MAPSELECTION_CAPTION);
	oslDrawString(240,160," <- Fall of Icarus ->");
	oslDrawString(335,183,"X");
}

void GameOptionsScreen::update()
{
	if(osl_keys->pressed.cross)
	{				
		Screen = ScreenManager::SCREEN_GAME; //Start game!
	}
	if(osl_keys->pressed.circle)
	{
		Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
