//**************************************************************************
//		PSP Project: 'Gods Defense' - Main.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Main.h"
#include "../Include/SaveLoad.h"

PSP_MODULE_INFO("Gods Defense", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

//Screen display
int	Screen = 0;
int	wait = 0;
int	gMenu = 0;
OSL_FONT *gFont;
OSL_SOUND *menuTheme;
int loadState = -1;
bool bSound = true;

//Initialization
int initOSLib(){
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
    oslInitAudioME (OSL_FMT_MP3);
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
    oslIntraFontInit(INTRAFONT_CACHE_MED);

	menuTheme = oslLoadSoundFileMP3 ("/Res/bgm.mp3", OSL_FMT_STREAM); //Loads the MP3s

	OSL_IMAGE *menubg = oslLoadImageFilePNG(Resource::MAIN_MENU_BG, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

    // Load fonts
	gFont = oslLoadFontFile("flash0:/font/ltn8.pgf");
    oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT); //Tells the psp what font to use in intrafont
	oslSetFont(gFont);

	ScreenManager *mScreenManager = new ScreenManager();
	SaveLoad	*mSaveLoadManager	= new SaveLoad();
	loadState = mSaveLoadManager->load();

    while(!osl_quit){
        if (!skip){
            oslStartDrawing();
			oslCls();
			if(Screen == ScreenManager::SCREEN_ANYKEY){
				mScreenManager->activate(ScreenManager::SCREEN_ANYKEY);
				if(mScreenManager->isActive())
				{		
					mScreenManager->mCurrentScreen->draw();
					wait++;
				}
				if(wait == 250) //wait 250 frames until this screen is over
				{	
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_TITLE;		
				}
			}

			if(Screen == ScreenManager::SCREEN_TITLE){   
				mScreenManager->activate(ScreenManager::SCREEN_TITLE);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				if(osl_keys->pressed.start)
				{
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_MAIN_MENU;
					oslPlaySound(menuTheme, 1); //Plays the sound in the menu
				}
			}
			
			if(Screen == ScreenManager::SCREEN_MAIN_MENU){
				mScreenManager->activate(ScreenManager::SCREEN_MAIN_MENU);
				if(mScreenManager->isActive())
				{
					oslDrawImageXY(menubg, (480/2) - (menubg->stretchX/2), (272/2) - (menubg->stretchY/2));
					mScreenManager->mCurrentScreen->draw();
					mScreenManager->mCurrentScreen->update();
				}
				mScreenManager->deactivate();
			}

			if(Screen == ScreenManager::SCREEN_CONFIRM_EXIT){
				mScreenManager->activate(ScreenManager::SCREEN_CONFIRM_EXIT);
				if(mScreenManager->isActive())
				{
					mScreenManager->mCurrentScreen->draw();
					mScreenManager->mCurrentScreen->update();
				}
				//mScreenManager->deactivate();
			}

			if(Screen == ScreenManager::SCREEN_GAME_OPTIONS){
				mScreenManager->activate(ScreenManager::SCREEN_GAME_OPTIONS);
				if(mScreenManager->isActive())
				{
					mScreenManager->mCurrentScreen->draw();
					mScreenManager->mCurrentScreen->update();
				}
				mScreenManager->deactivate();
			}

			if(Screen == ScreenManager::SCREEN_PAUSE){
				mScreenManager->activate(ScreenManager::SCREEN_PAUSE);
				if(mScreenManager->isActive())
				{
					mScreenManager->mCurrentScreen->draw();
					mScreenManager->mCurrentScreen->update();
				}
				mScreenManager->deactivate();
			}

			if(Screen == ScreenManager::SCREEN_GAME){
				mScreenManager->activate(ScreenManager::SCREEN_GAME);
				if(mScreenManager->isActive())
				{
					mScreenManager->mCurrentScreen->draw();
					mScreenManager->mCurrentScreen->update();
				}
				mScreenManager->deactivate();
			}
			
			if(Screen == ScreenManager::SCREEN_OPTIONS){
				mScreenManager->activate(ScreenManager::SCREEN_OPTIONS);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				if(osl_keys->pressed.cross)
				{	
					loadState = mSaveLoadManager->load();
					if(loadState == 0)
					{				
						bSound = false;
						mSaveLoadManager->save("1");
						oslStopSound(menuTheme);
					}
					if(loadState == 1)
					{
						bSound = true;
						mSaveLoadManager->save("0");
						oslPlaySound(menuTheme,1);
					}
				}
				if(osl_keys->pressed.circle)
				{
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
				}
			}
			if(Screen == ScreenManager::SCREEN_HELP){
				mScreenManager->activate(ScreenManager::SCREEN_HELP);
				if(mScreenManager->isActive())
				{
					mScreenManager->mCurrentScreen->draw();
					mScreenManager->mCurrentScreen->update();
				}
				mScreenManager->deactivate();
			}
			if(Screen == ScreenManager::SCREEN_ABOUT){
				mScreenManager->activate(ScreenManager::SCREEN_ABOUT);
				if(mScreenManager->isActive())
				{
					mScreenManager->mCurrentScreen->draw();
					mScreenManager->mCurrentScreen->update();
				}
				mScreenManager->deactivate();
			}

			if(Screen == ScreenManager::SCREEN_MULTIPLAYER){
				mScreenManager->activate(ScreenManager::SCREEN_MULTIPLAYER);
				if(mScreenManager->isActive())
				{
					mScreenManager->mCurrentScreen->draw();
					mScreenManager->mCurrentScreen->update();
				}
				mScreenManager->deactivate();
			}
			oslEndDrawing();
		}

        oslReadKeys();
        oslEndFrame();
    	skip = oslSyncFrame();
    }

	oslDeleteImage(menubg);
	oslDeleteSound(menuTheme);
	oslDeleteFont(gFont);
    oslIntraFontShutdown();
    endOSLib();
	
	sceKernelExitGame();
	return 0;
}
