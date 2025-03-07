//**************************************************************************
//		PSP Project: 'Gods Defense' - AnykeyScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/AnykeyScreen.h"
#include "../Include/ScreenManager.h"

AnykeyScreen::AnykeyScreen()
{
	mWait = 0;
	AnykeySplash = oslLoadImageFilePNG(Resource::IMG_ANYKEY_SPLASH, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mySplash = new Drawing;
}

AnykeyScreen::~AnykeyScreen()
{
	oslDeleteImage(AnykeySplash);
	delete(mySplash);
}

void AnykeyScreen::draw()
{
	//draw logo image
	mySplash->drawSplash(200,AnykeySplash);
}

void AnykeyScreen::update(u32 /*timePassed*/) //Parametro Formal, n�o d� warning
{
	mWait++;
	if(mWait == 250) //wait 250 frames until this screen is over
	{
		mNextScreen = ScreenManager::SCREEN_TITLE;		
	}
}