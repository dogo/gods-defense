//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameScreen.h"
#include "../Include/ScreenManager.h"


GameScreen::GameScreen()
{
	cursor = oslLoadImageFilePNG("Res/cursor.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	map = oslLoadImageFilePNG("Res/maps/test/icarusfalls.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	if (!map || !cursor)
		oslFatalError("At least one file is missing. Please copy all the file in the game directory.");

	//Initialize variables
	cursor->centerY = cursor->sizeY / 2;
	cursor->x = 240;							//Place cursor at the center of the screen
	cursor->y = 136;
	map->x = 0;
	map->y = 0;
}

GameScreen::~GameScreen()
{
	oslDeleteImage(cursor);
	oslDeleteImage(map);
}

void GameScreen::draw()
{
	oslDrawImage(map);
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,120,"No Towers Defense for you!");
	oslDrawImage(cursor);
#ifdef DEBUG
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(0,15,"Value of joystick X : %d",osl_keys->analogX);
	
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(0,35,"Value of joystick Y : %d",osl_keys->analogY);
#endif
}

void GameScreen::update()
{
	/*
	*	Dogo : Vai buga futuramente, o pause nao pode deletar a tela anterior ou seja a tela do jogo,
	*	pois quando voltar do pause nao vai mais ter referencia do jogo.
	*   TODO : Pensar como pausar!
	*   Dogo 10/03/09 -> Congelar o jogo, pintar a tela de pause por cima, quando voltar ao jogo repintar e voltar o
	*   estado do jogo.
	*/

	//Temporary, for test
	//Joystick to move the cursor
    for (i=32;i<=120;i+=48)
    {
		//Move X Coords
        if (osl_keys->analogX > i)
        {
			if(cursor->x > 464 -1) //psp 480 - 16 cursor - 1 fine tunning
				cursor->x = 464;
			else
				cursor->x += 2;                
        }
        if (osl_keys->analogX < -i)
        {
			if(cursor->x < 0)
				cursor->x = 0;
			else
				cursor->x -= 2;                
        }    

        //Move Y Coords
        if (osl_keys->analogY > i)
        {
			cursor->y += 2;                
        }
        if (osl_keys->analogY < -i)
        {
			cursor->y -= 2;                
        }
	}

	if(osl_keys->pressed.L)
	{
		oslFlushKey();
		map->x = 0;
		map->y = -208;
	}

	if(osl_keys->pressed.R)
	{
		oslFlushKey();
		map->x = 0;
		map->y = 0;
	}
	//

	if(osl_keys->pressed.start)
	{	
		oslFlushKey();
		Screen = ScreenManager::SCREEN_PAUSE; //Pause game!
	}
	if(osl_keys->pressed.circle)
	{
		oslFlushKey();
		Screen = ScreenManager::SCREEN_GAME_OPTIONS; //go back CLR
	}
}
