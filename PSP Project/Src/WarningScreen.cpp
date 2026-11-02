//**************************************************************************
//		PSP Project: 'Gods Defense' - WarningScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/WarningScreen.h"
#include "../Include/ScreenManager.h"


WarningScreen::WarningScreen()
{
	mBack = oslLoadImageFilePNG(Resource::IMG_BACK, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mCover = oslLoadImageFilePNG(Resource::IMG_COVER, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

WarningScreen::~WarningScreen()
{
	oslDeleteImage(mBack);
	oslDeleteImage(mCover);
}

void WarningScreen::draw()
{
	oslDrawImageXY(mCover,0,0);
	Drawing::drawControlHint(mBack, 366, 240, Resource::STR_BACK_SK);
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_WARNING_CAPTION);
	oslIntraFontSetStyle(gFont, 0.6f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,100,Resource::STR_WARNING_TEXT);
}

void WarningScreen::update(u32 /*timePassed*/)
{
	if(osl_keys->pressed.circle)
	{
		oslFlushKey();
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
