//**************************************************************************
//		PSP Project: 'Gods Defense' - PauseScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/PauseScreen.h"
#include "../Include/ScreenManager.h"


PauseScreen::PauseScreen()
{
	gMenu = 0;
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::draw()
{
	//Screen Title
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,40,Resource::STR_PAUSE_CAPTION);

	//Screen Options
	(gMenu == 0) ? oslIntraFontSetStyle(gFont, 0.9f,RGBA(175,137,62,255), RGBA(0,0,0,255),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 0.7f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 100,Resource::STR_PAUSE_RESUME);
	(gMenu == 1) ? oslIntraFontSetStyle(gFont, 0.9f,RGBA(175,137,62,255), RGBA(0,0,0,255),INTRAFONT_ALIGN_CENTER) : oslIntraFontSetStyle(gFont, 0.7f,RGBA(120,120,120,255), RGBA(0,0,0,0xFF),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, 120,Resource::STR_PAUSE_MENU);
}

void PauseScreen::update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	if(osl_keys->pressed.up){
		gMenu--;
		if (gMenu < 0)
		{
			gMenu = 1;
		}
	}
	if(osl_keys->pressed.down){
		gMenu++;
		gMenu%=2;
	}
	if(osl_keys->pressed.circle)
	{
		oslFlushKey();
		GameScreen::gPauseGame = !GameScreen::gPauseGame;
		GameScreen::gGameReference->SetGameState(GS_SCROLL_MAP); //go back CLR
	}
	if(osl_keys->pressed.cross)
	{
		oslFlushKey();
		if(gMenu == 0)
		{
			GameScreen::gPauseGame = !GameScreen::gPauseGame;
			GameScreen::gGameReference->SetGameState(GS_SCROLL_MAP); //go back CLR
		}
		else if (gMenu == 1)
		{
			mNextScreen = ScreenManager::SCREEN_MAIN_MENU;
			gMenu = 0;
			oslPlaySound(menuTheme, CHANNEL_0); //Plays the sound in the menu
		}
	}
}
