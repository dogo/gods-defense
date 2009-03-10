//**************************************************************************
//		PSP Project: 'Gods Defense' - HelpScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/HelpScreen.h"
#include "../Include/ScreenManager.h"


HelpScreen::HelpScreen()
{
}

void HelpScreen::draw()
{
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,120,"No Help yet!");
}

void HelpScreen::update()
{
	if(osl_keys->pressed.circle)
	{
		Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
