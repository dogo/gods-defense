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
	Drawing::drawControlHint(mCross, 366, 240, Resource::STR_OK);
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_AUTOSAVE_CAPTION);
	oslIntraFontSetStyle(gFont, 0.65f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,100,Resource::STR_AUTOSAVE_TEXT);
}

void MemoryWarningScreen::update(u32 /*timePassed*/)
{
	mType = oslGetSaveLoadType();

	if(mMemoryStick->Status(mType))
		mNextScreen = ScreenManager::SCREEN_ANYKEY;

	if(osl_keys->pressed.cross)
	{
		oslFlushKey();
		mMemoryStick->Load();
	}
}



