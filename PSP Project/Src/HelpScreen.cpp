//**************************************************************************
//		PSP Project: 'Gods Defense' - HelpScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/HelpScreen.h"
#include "../Include/ScreenManager.h"


HelpScreen::HelpScreen()
{
	mBack = oslLoadImageFilePNG(Resource::IMG_BACK, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mCover = oslLoadImageFilePNG(Resource::IMG_COVER, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

HelpScreen::~HelpScreen()
{
	oslDeleteImage(mBack);
	oslDeleteImage(mCover);
}

void HelpScreen::draw()
{
	oslDrawImageXY(mCover,0,0);
	Drawing::drawControlHint(mBack, 366, 240, Resource::STR_BACK_SK);
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_HELP_CAPTION);
	oslIntraFontSetStyle(gFont, 0.55f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,40,Resource::STR_HELP_TEXT);
}

void HelpScreen::update(u32 /*timePassed*/)
{
	if(osl_keys->pressed.circle)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
