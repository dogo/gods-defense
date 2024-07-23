//**************************************************************************
//		PSP Project: 'Gods Defense' - TrophiesScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/TrophiesScreen.h"
#include "../Include/ScreenManager.h"


TrophiesScreen::TrophiesScreen()
{
	back = oslLoadImageFilePNG(Resource::IMG_BACK, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

TrophiesScreen::~TrophiesScreen()
{
	oslDeleteImage(back);
}

void TrophiesScreen::draw()
{
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_TROPHIES_CAPTION);

	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,120,"Coming Soon!");

	oslDrawImageXY(back, (430) - (back->stretchX), (272) - (back->stretchY));
	oslIntraFontSetStyle(gFont, 0.7f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - back->stretchX,(272) - (back->stretchY/2),Resource::STR_BACK_SK);
}

void TrophiesScreen::update(u32 /*timePassed*/) //Parametro Formal, n�o d� warning
{
	if(osl_keys->pressed.circle)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}