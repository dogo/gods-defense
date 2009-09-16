//**************************************************************************
//		PSP Project: 'Gods Defense' - EndingScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/EndingScreen.h"
#include "../Include/ScreenManager.h"


EndingScreen::EndingScreen()
{
	mCross = oslLoadImageFilePNG(Resource::IMG_CROSS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

EndingScreen::~EndingScreen()
{
	oslDeleteImage(mCross);
}

void EndingScreen::draw()
{
	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	(gWin) ? oslDrawString(240,100,Resource::STR_CONGRATS) : oslDrawString(240,100,Resource::STR_LOSE);
	oslDrawImageXY(mCross, (430) - (mCross->stretchX), (272) - (mCross->stretchY));
}

void EndingScreen::update(u64 /*timePassed*/) //Parametro Formal, não dá warning
{
	if(osl_keys->pressed.cross)
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go to main menu
}