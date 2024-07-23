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
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_WARNING_CAPTION);
	oslIntraFontSetStyle(gFont, 0.6f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,100,Resource::STR_WARNING_TEXT);
	oslDrawImageXY(mBack, (430) - (mBack->stretchX), (272) - (mBack->stretchY));
	oslIntraFontSetStyle(gFont, 0.7f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - mBack->stretchX,(272) - (mBack->stretchY/2),Resource::STR_BACK_SK);
}

void WarningScreen::update(u32 /*timePassed*/) //Parametro Formal, n�o d� warning
{
	if(osl_keys->pressed.circle)
	{
		oslFlushKey();
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
