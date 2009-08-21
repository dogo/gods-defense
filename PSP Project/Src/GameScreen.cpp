//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameScreen.h"
#include "../Include/ScreenManager.h"

GameScreen::GameScreen()
{
	GameGUI::InitGUI(this);
	
	mGameGUI = GameGUI::Instance();

	mGameMap = Map::InitMap();

	LoadMap(gChoosedMap);

	LoadFirstPartForMap();
	
	mSetViewX = 0;
	mSetViewY = 0;
}

void GameScreen::LoadMap(const string &mapName)
{
	mGameState = GS_SCROLL_MAP;
	mActiveWaves = 0;
	mWaveIsRunning = false;

	mPlayerPoints = 0;
	mGameMap->ResetMap();
	mGameMap->LoadMap(mapName);

	mPlayerLives = mGameMap->mInitialLives;
	mPlayerMoney = mGameMap->mInitialGold;
}

void GameScreen::LoadFirstPartForMap()
{
	//Load map image
	mGameMap->LoadMapImage();
	mGameGUI->LoadStuffs();
}

GameScreen::~GameScreen()
{
	delete(mGameMap);
	delete(mGameGUI);
}

void GameScreen::draw()
{

	//move camera

	mGameMap->draw();

	//mGameGUI->???;  render offset? cursor ?
	mGameGUI->draw();	
#ifdef DEBUG
	oslPrintf_xy(0,20,"Value of joystick X : %d",osl_keys->analogX);
	oslPrintf_xy(0,30,"Value of joystick Y : %d",osl_keys->analogY);
#endif
}

void GameScreen::SetView(const int &scrollX, const int &scrollY)
{
	mSetViewX = scrollX;
	mSetViewY = scrollY;

	oslPrintf_xy(0,30,"mSetViewX %d",mSetViewX);
	oslPrintf_xy(0,40,"mSetViewY %d",mSetViewY);

	if (mSetViewX < (480 - 16 * mGameMap->mGridTilesWidth))  //(PSP Screen - Tiles Size * Tiles)
		mSetViewX = (480 - 16 * mGameMap->mGridTilesWidth);
	if (mSetViewX > 0)
		mSetViewX = 0;

	if (mSetViewY < (480 - 16 * mGameMap->mGridTilesHeight))
		mSetViewY = (480 - 16 * mGameMap->mGridTilesHeight);
	if (mSetViewY > 0)
		mSetViewY = 0;
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
	mGameGUI->Update(/*timePassed*/);
	
	if(osl_keys->pressed.start)
	{	
		oslFlushKey();
		mNextScreen = ScreenManager::SCREEN_PAUSE; //Pause game!
	}
	if(osl_keys->pressed.circle)
	{
		oslFlushKey();
		mNextScreen = ScreenManager::SCREEN_GAME_OPTIONS; //go back CLR
	}
}

const GameState GameScreen::GetGameState()
{
	return mGameState;
}

void GameScreen::SetGameState(const GameState &newState)
{
	mGameState = newState;
}