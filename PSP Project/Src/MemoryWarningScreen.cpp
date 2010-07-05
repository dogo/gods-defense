//**************************************************************************
//		PSP Project: 'Gods Defense' - MemoryWarningScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/MemoryWarningScreen.h"
#include "../Include/ScreenManager.h"

MemoryWarningScreen::MemoryWarningScreen()
{
	type = OSL_DIALOG_NONE;
	cross = oslLoadImageFilePNG(Resource::IMG_CROSS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	myMemoryStick = new MemoryStick();
}

MemoryWarningScreen::~MemoryWarningScreen()
{
	oslDeleteImage(cross);
	delete(myMemoryStick);
}

void MemoryWarningScreen::draw()
{
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_AUTOSAVE_CAPTION);
	oslIntraFontSetStyle(gFont, 0.65f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,100,Resource::STR_AUTOSAVE_TEXT);
	oslDrawImageXY(cross, (430) - (cross->stretchX), (272) - (cross->stretchY));
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - cross->stretchX,(272) - (cross->stretchY/2),Resource::STR_OK);
}

void MemoryWarningScreen::update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	type = oslGetSaveLoadType();

	if(myMemoryStick->Status(type))
		mNextScreen = ScreenManager::SCREEN_ANYKEY;

	if(osl_keys->pressed.cross)
	{
		oslFlushKey();
		myMemoryStick->Load(type);
	}
}



