//**************************************************************************
//		PSP Project: 'Gods Defense' - OptionsScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/OptionsScreen.h"
#include "../Include/ScreenManager.h"


OptionsScreen::OptionsScreen()
{
	back = oslLoadImageFilePNG("/Res/circle.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	select = oslLoadImageFilePNG("/Res/x.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

OptionsScreen::~OptionsScreen()
{
	oslDeleteImage(back);
	oslDeleteImage(select);
}

void OptionsScreen::draw()
{
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); 
	oslDrawString(240,40,Resource::OPTIONS_CAPTION);
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); 
	oslDrawString(240,100,Resource::OPTIONS_SOUND);
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); 
	(bSound) ? oslDrawString(300,100,Resource::OPTIONS_ON) : oslDrawString(300,100,Resource::OPTIONS_OFF);
	//Back SK
	oslDrawImageXY(back, (400) - (back->stretchX), (272) - (back->stretchY));
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((480) - back->stretchX,(272) - (back->stretchY/2),Resource::BACK_SK);
	//Select SK
	oslDrawImageXY(select, select->stretchX, (272) - (select->stretchY));
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((110) + select->stretchX,(272) - (select->stretchY/2),Resource::OPTIONS_CHANGE);
}

void OptionsScreen::update()
{
}