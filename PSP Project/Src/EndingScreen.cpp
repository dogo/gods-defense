//**************************************************************************
//		PSP Project: 'Gods Defense' - EndingScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/EndingScreen.h"
#include "../Include/ScreenManager.h"

char gScoreBuffer[256];

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
	oslIntraFontSetStyle(gFont, 0.8f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	(gWin) ? oslDrawString(240,100,Resource::STR_CONGRATS) : oslDrawString(240,100,Resource::STR_LOSE);
	oslDrawStringf(240,175,"Score : %s", gScoreBuffer); //=( TODO: Format this string
	oslDrawImageXY(mCross, (430) - (mCross->stretchX), (272) - (mCross->stretchY));
}

void EndingScreen::update(u32 /*timePassed*/) //Parametro Formal, n�o d� warning
{
	if(osl_keys->pressed.cross)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go to main menu
		oslPlaySound(menuTheme, CHANNEL_0); //Plays the sound in the menu
	}
}