//**************************************************************************
//		PSP Project: 'Gods Defense' - AnykeyScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/AnykeyScreen.h"
#include "../Include/ScreenManager.h"


AnykeyScreen::AnykeyScreen()
{
	Splash = oslLoadImageFilePNG(Resource::ANYKEY_SPLASH, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}

AnykeyScreen::~AnykeyScreen()
{
	oslDeleteImage(Splash);
}

void AnykeyScreen::draw()
{
	//draw logo image
	oslDrawImageXY(Splash, (480/2) - (Splash->stretchX/2), (272/2) - (Splash->stretchY/2));
}

void AnykeyScreen::update()
{

}
