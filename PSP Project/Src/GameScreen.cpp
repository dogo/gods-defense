//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameScreen.h"
#include "../Include/ScreenManager.h"

GameScreen::GameScreen()
{
	LoadMap(gChoosedMap);
	
	GameGUI::InitGUI(this);
	
	mGameGUI = GameGUI::Instance();

	mCurrentMap = Map::InitMap();
	
	mSetViewX = 0;
	mSetViewY = 0;

	map = LoadMapImage(mCurrentMap->mImgMapName);

	if (!map)
		oslFatalError("At least one file is missing. Please copy all the file in the game directory.");
	map->x = 0;
	map->y = 0;
	
}

void GameScreen::LoadMap(const string &mapName)
{
	mGameState = GS_SCROLL_MAP;
	mActiveWaves = 0;
	mWaveIsRunning = false;

	mPlayerPoints = 0;
	mCurrentMap->LoadMap(mapName);

	mPlayerLives = mCurrentMap->mInitialLives;
	mPlayerMoney = mCurrentMap->mInitialGold;
}

OSL_IMAGE *GameScreen::LoadMapImage(const char *imageName)
{
	char temp[256];
	OSL_IMAGE *mMapImg = NULL;

	sprintf(temp, "Res/maps/%s/%s", mCurrentMap->mMapName, imageName);
	mMapImg = oslLoadImageFilePNG(temp, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	return mMapImg;
}

//void GameScreen::LoadFirstPartForMap()
//{
//	//Load map image
//	mCurrentMap->LoadImage();
//}

GameScreen::~GameScreen()
{
	//oslDeleteImage(cursor);
	oslDeleteImage(map);
}

void GameScreen::draw()
{

	mCurrentMap->draw();

	//mGameGUI->???;  render offset? cursor ?
	mGameGUI->draw();	
/*
#ifdef DEBUG
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(0,15,"Value of joystick X : %d",osl_keys->analogX);
	
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(0,35,"Value of joystick Y : %d",osl_keys->analogY);
#endif*/
}

void GameScreen::SetView(const int &scrollX, const int &scrollY)
{
	mSetViewX = scrollX;
	mSetViewY = scrollY;

	if (mSetViewX < (480 - 32 * mCurrentMap->mGridTilesWidth))  //(PSP Screen - Tiles Size * Tiles)
		mSetViewX = (480 - 32 * mCurrentMap->mGridTilesWidth);
	if (mSetViewX > 0)
		mSetViewX = 0;

	if (mSetViewY < (480 - 32* mCurrentMap->mGridTilesHeight))
		mSetViewY = (480 - 32* mCurrentMap->mGridTilesHeight);
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

	//Temporary, for test
	//Joystick to move the cursor
	/*
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
	*/
	//

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