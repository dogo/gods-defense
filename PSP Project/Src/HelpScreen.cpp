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
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_HELP_CAPTION);
	oslIntraFontSetStyle(gFont, 0.6f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,40,Resource::STR_HELP_TEXT);
	oslDrawImageXY(mBack, (430) - (mBack->stretchX), (272) - (mBack->stretchY));
	oslIntraFontSetStyle(gFont, 0.7f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - mBack->stretchX,(272) - (mBack->stretchY/2),Resource::STR_BACK_SK);
}

void HelpScreen::update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	if(osl_keys->pressed.circle)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
