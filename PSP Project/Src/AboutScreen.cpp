//**************************************************************************
//		PSP Project: 'Gods Defense' - AboutScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/AboutScreen.h"
#include "../Include/ScreenManager.h"


AboutScreen::AboutScreen()
{
	back = oslLoadImageFilePNG("/Res/circle.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

AboutScreen::~AboutScreen()
{
	oslDeleteImage(back);
}

void AboutScreen::draw()
{
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::ABOUT_CAPTION);
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,40,Resource::ABOUT_TEXT);
	oslDrawImageXY(back, (430) - (back->stretchX), (272) - (back->stretchY));
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - back->stretchX,(272) - (back->stretchY/2),Resource::BACK_SK);
}

void AboutScreen::update()
{
	if(osl_keys->pressed.circle)
	{
		Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
