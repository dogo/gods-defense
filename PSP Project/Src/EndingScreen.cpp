//**************************************************************************
//		PSP Project: 'Gods Defense' - EndingScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/EndingScreen.h"
#include "../Include/ScreenManager.h"
#include "../Include/Adhoc.h"

char gScoreBuffer[256];

EndingScreen::EndingScreen()
{
	mCross = oslLoadImageFilePNG(Resource::IMG_CROSS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

EndingScreen::~EndingScreen()
{
	oslDeleteImage(mCross);
	delete Adhoc::resultConnection;
	Adhoc::resultConnection = NULL;
}

void EndingScreen::draw()
{
	oslDrawImageXY(mCross, (430) - (mCross->stretchX), (272) - (mCross->stretchY));
	oslIntraFontSetStyle(gFont, 0.8f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	if (Adhoc::resultConnection && Adhoc::resultConnection->session()->result() == MultiplayerSession::Draw)
		oslDrawString(240, 100, "Draw!\nPress Cross to return to main menu.");
	else (gWin) ? oslDrawString(240,100,Resource::STR_CONGRATS) : oslDrawString(240,100,Resource::STR_LOSE);
	oslDrawStringf(240,175,"Score : %s", gScoreBuffer);
	if (Adhoc::resultConnection)
		oslDrawStringf(240, 200, "Opponent: %u", (unsigned int)Adhoc::resultConnection->session()->remoteScore());
}

void EndingScreen::update(u32 /*timePassed*/)
{
	if (Adhoc::resultConnection)
		Adhoc::resultConnection->updateSession((u32)(sceKernelGetSystemTimeWide() / 1000));
	if(osl_keys->pressed.cross)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go to main menu
		oslPlaySound(menuTheme, CHANNEL_0); //Plays the menu sound
	}
}