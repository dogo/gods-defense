//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameScreen.h"
#include "../Include/ScreenManager.h"


GameScreen::GameScreen()
{
}

void GameScreen::draw()
{
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,120,"No Towers Defense for you!");
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
