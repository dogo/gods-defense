//**************************************************************************
//		PSP Project: 'Gods Defense' - MultiplayerScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MultiplayerScreen.h"
#include "../Include/ScreenManager.h"


MultiplayerScreen::MultiplayerScreen()
{
}

MultiplayerScreen::~MultiplayerScreen()
{
}

void MultiplayerScreen::draw()
{
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,120,"MULTIPLAYER Screen");
}

void MultiplayerScreen::update()
{
	if(osl_keys->pressed.circle)
	{	
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
