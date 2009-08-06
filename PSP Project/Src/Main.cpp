//**************************************************************************
//		PSP Project: 'Gods Defense' - Main.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Main.h"

PSP_MODULE_INFO("Gods Defense", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

//Screen display
int mNextScreen = -1;
int	gScreen = 0;
int	gMenu = 0;
OSL_FONT *gFont;
OSL_SOUND *menuTheme;

//Initialization
int initOSLib(){
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
    oslSetQuitOnLoadFailure(1);
    oslSetKeyAutorepeatInit(40);
    oslSetKeyAutorepeatInterval(10);
    return 0;
}

//Terminate OSLib
int endOSLib(){
    oslEndGfx();
    osl_quit = 1;
    return 0;
}

int main()
{
	int skip = 0;
    initOSLib();
    oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_CP1252);

	menuTheme = oslLoadSoundFileBGM("/Res/menuTheme.bgm", OSL_FMT_STREAM); //Loads the Main menu theme music

    // Load fonts
	gFont = oslLoadFontFile("flash0:/font/ltn8.pgf");
    oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT); //Tells the psp what font to use in intrafont
	oslSetFont(gFont);

	if (!menuTheme /*|| !menubg*/ || !gFont)
		oslFatalError("At least one file is missing. Please copy all the file in the game directory.");

	ScreenManager *mScreenManager = new ScreenManager();
	mNextScreen = ScreenManager::SCREEN_ANYKEY;

    while(!osl_quit){
        if (!skip){
            oslStartDrawing();
			oslCls();

			if(mNextScreen != -1)
			{
				if(mScreenManager->isActive())
					mScreenManager->deactivate();

				mScreenManager->activate(mNextScreen);
			}

			if(mScreenManager->isActive())
			{		
				mScreenManager->mCurrentScreen->draw();
				mScreenManager->mCurrentScreen->update();
			}

			if(gScreen == ScreenManager::SCREEN_TITLE){   
				if(osl_keys->pressed.start)
				{
					oslPlaySound(menuTheme, 1); //Plays the sound in the menu
				}
			}
			oslEndDrawing();
		}

        oslReadKeys();
        oslEndFrame();
    	skip = oslSyncFrame();
    }

	oslDeleteSound(menuTheme);
	oslDeleteFont(gFont);
    oslIntraFontShutdown();
    endOSLib();
	
	sceKernelExitGame();
	return (0);
}
