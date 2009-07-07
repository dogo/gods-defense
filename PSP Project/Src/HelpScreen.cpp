//**************************************************************************
//		PSP Project: 'Gods Defense' - HelpScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/HelpScreen.h"
#include "../Include/ScreenManager.h"


HelpScreen::HelpScreen()
{
	back = oslLoadImageFilePNG("/Res/circle.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

void HelpScreen::draw()
{
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_HELP_CAPTION);
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,40,Resource::STR_HELP_TEXT);
	oslDrawImageXY(back, (430) - (back->stretchX), (272) - (back->stretchY));
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - back->stretchX,(272) - (back->stretchY/2),Resource::STR_BACK_SK);
}

void HelpScreen::update()
{
	if(osl_keys->pressed.circle)
	{
		Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
