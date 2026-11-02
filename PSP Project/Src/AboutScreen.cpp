//**************************************************************************
//		PSP Project: 'Gods Defense' - AboutScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/AboutScreen.h"
#include "../Include/ScreenManager.h"


AboutScreen::AboutScreen()
{
	mBack = oslLoadImageFilePNG(Resource::IMG_BACK, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mCover = oslLoadImageFilePNG(Resource::IMG_COVER, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

AboutScreen::~AboutScreen()
{
	oslDeleteImage(mBack);
	oslDeleteImage(mCover);
}

void AboutScreen::draw()
{
	oslDrawImageXY(mCover,0,0);
	Drawing::drawControlHint(mBack, 366, 240, Resource::STR_BACK_SK);
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_ABOUT_CAPTION);
	oslIntraFontSetStyle(gFont, 0.6f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,45,Resource::STR_ABOUT_TEXT);
}

void AboutScreen::update(u32 /*timePassed*/)
{
	if(osl_keys->pressed.circle)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
