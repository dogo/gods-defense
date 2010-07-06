//**************************************************************************
//		PSP Project: 'Gods Defense' - MemoryWarningScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MemoryWarningScreen.h"
#include "../Include/ScreenManager.h"

MemoryWarningScreen::MemoryWarningScreen()
{
	mType = OSL_DIALOG_NONE;
	mCross = oslLoadImageFilePNG(Resource::IMG_CROSS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mCover = oslLoadImageFilePNG(Resource::IMG_COVER, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mMemoryStick = new MemoryStick();
}

MemoryWarningScreen::~MemoryWarningScreen()
{
	oslDeleteImage(mCross);
	oslDeleteImage(mCover);
	delete(mMemoryStick);
}

void MemoryWarningScreen::draw()
{
	oslDrawImageXY(mCover,0,0);
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_AUTOSAVE_CAPTION);
	oslIntraFontSetStyle(gFont, 0.65f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,100,Resource::STR_AUTOSAVE_TEXT);
	oslDrawImageXY(mCross, (430) - (mCross->stretchX), (272) - (mCross->stretchY));
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - mCross->stretchX,(272) - (mCross->stretchY/2),Resource::STR_OK);
}

void MemoryWarningScreen::update(u32 /*timePassed*/) //Parametro Formal, n�o d� warning
{
	mType = oslGetSaveLoadType();

	if(mMemoryStick->Status(mType))
		mNextScreen = ScreenManager::SCREEN_ANYKEY;

	if(osl_keys->pressed.cross)
	{
		oslFlushKey();
		mMemoryStick->Load(mType);
	}
}



