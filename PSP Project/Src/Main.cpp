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


	OSL_SOUND *menuBg = oslLoadSoundFileMP3 ("/Res/bgm.mp3", OSL_FMT_STREAM); //Loads the MP3s

    // Load fonts
	gFont = oslLoadFontFile("flash0:/font/ltn8.pgf");
    oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT); //Tells the psp what font to use in intrafont
	oslSetFont(gFont);

	ScreenManager *mScreenManager = new ScreenManager();
	SaveLoad	*mSaveLoadManager	= new SaveLoad();
	loadState = mSaveLoadManager->load();

	SceCtrlData pad;

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
				if(wait == 200) //wait 200 frames until this screen is over
				{	
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_TITLE;		
				}
			}

			if(Screen == ScreenManager::SCREEN_TITLE){   
				mScreenManager->activate(ScreenManager::SCREEN_TITLE);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				//Get any key pressed
				sceCtrlReadBufferPositive(&pad, 1);
				if(pad.Buttons != 0)
				{
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_MAIN_MENU;
					oslPlaySound(menuBg, 1); //Plays the sound in the menu
				}
			}
			
			if(Screen == ScreenManager::SCREEN_MAIN_MENU){
				mScreenManager->activate(ScreenManager::SCREEN_MAIN_MENU);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				//menu keys
				if(osl_keys->pressed.up){
					gMenu--;
					if (gMenu < 0)
					{
						gMenu = 5;
					}
				}
				if(osl_keys->pressed.down){
					gMenu++;
					gMenu%=6;
				}
				if(osl_keys->pressed.cross){
					if(gMenu == 0)
					{
						oslFlushKey();
						mScreenManager->deactivate();
						Screen = ScreenManager::SCREEN_GAME_OPTIONS; // start game options!
					}
					if(gMenu == 1)
					{
						oslFlushKey();
						mScreenManager->deactivate();
						Screen = ScreenManager::SCREEN_MULTIPLAYER;
					}
					if(gMenu == 2)
					{
						oslFlushKey();
						mScreenManager->deactivate();
						Screen = ScreenManager::SCREEN_OPTIONS;
					}
					if(gMenu == 3)
					{
						oslFlushKey();
						mScreenManager->deactivate();
						Screen = ScreenManager::SCREEN_HELP;
					}
					if(gMenu == 4)
					{
						oslFlushKey();
						mScreenManager->deactivate();
						Screen = ScreenManager::SCREEN_ABOUT;
					}
					if(gMenu == 5)
					{
						oslFlushKey();
						mScreenManager->deactivate();
						Screen = ScreenManager::SCREEN_CONFIRM_EXIT;
					}
				}
			}
			if(Screen == ScreenManager::SCREEN_CONFIRM_EXIT){
				mScreenManager->activate(ScreenManager::SCREEN_CONFIRM_EXIT);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
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
				if(osl_keys->pressed.cross){
					if(gMenu == 0)
					{
						oslStopSound(menuBg);
						Screen = endOSLib(); //quit game
					}
					if(gMenu == 1)
					{
						oslFlushKey();
						mScreenManager->deactivate();
						gMenu = 0;
						Screen = ScreenManager::SCREEN_MAIN_MENU;
					}
				}
					if(osl_keys->pressed.circle)
					{
						mScreenManager->deactivate();
						Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
					}
			}
			if(Screen == ScreenManager::SCREEN_GAME_OPTIONS){
				mScreenManager->activate(ScreenManager::SCREEN_GAME_OPTIONS);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				if(osl_keys->pressed.cross)
				{				
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_GAME; //Start game!

				}
				if(osl_keys->pressed.circle)
				{
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
				}
			}
			if(Screen == ScreenManager::SCREEN_PAUSE){
				mScreenManager->activate(ScreenManager::SCREEN_PAUSE);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				if(osl_keys->pressed.circle || osl_keys->pressed.start)
				{
					oslFlushKey();
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_GAME; //go back CLR
				}
			}

			if(Screen == ScreenManager::SCREEN_GAME){
				mScreenManager->activate(ScreenManager::SCREEN_GAME);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				if(osl_keys->pressed.start)
				{	
					/*
					*	Dogo : Vai buga futuramente, o pause nao pode deletar a tela anterior ou seja a tela do jogo,
					*	pois quando voltar do pause nao vai mais ter referencia do jogo.
					*   TODO : Pensar como pausar!
					*/
					mScreenManager->deactivate(); 
					Screen = ScreenManager::SCREEN_PAUSE; //Start game!

				}
				if(osl_keys->pressed.circle)
				{
					oslFlushKey();
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_GAME_OPTIONS; //go back CLR
				}
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
						oslStopSound(menuBg);
					}
					if(loadState == 1)
					{
						bSound = true;
						mSaveLoadManager->save("0");
						oslPlaySound(menuBg,1);
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
					mScreenManager->mCurrentScreen->draw();
				if(osl_keys->pressed.circle)
				{
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
				}
			}
			if(Screen == ScreenManager::SCREEN_ABOUT){
				mScreenManager->activate(ScreenManager::SCREEN_ABOUT);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				if(osl_keys->pressed.circle)
				{
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
				}

			}

			if(Screen == ScreenManager::SCREEN_MULTIPLAYER){
				mScreenManager->activate(ScreenManager::SCREEN_MULTIPLAYER);
				if(mScreenManager->isActive())
					mScreenManager->mCurrentScreen->draw();
				if(osl_keys->pressed.circle)
				{	
					mScreenManager->deactivate();
					Screen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
				}
			}
			oslEndDrawing();
		}

        oslReadKeys();
        oslEndFrame();
    	skip = oslSyncFrame();
    }
	oslDeleteFont(gFont);
    oslIntraFontShutdown();
    endOSLib();
	
	sceKernelExitGame();
	return 0;
}
