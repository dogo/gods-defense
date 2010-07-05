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
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_ABOUT_CAPTION);
	oslIntraFontSetStyle(gFont, 0.6f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,45,Resource::STR_ABOUT_TEXT);
	oslDrawImageXY(mBack, (430) - (mBack->stretchX), (272) - (mBack->stretchY));
	oslIntraFontSetStyle(gFont, 0.7f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - mBack->stretchX,(272) - (mBack->stretchY/2),Resource::STR_BACK_SK);
}

void AboutScreen::update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	if(osl_keys->pressed.circle)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
