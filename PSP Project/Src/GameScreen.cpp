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

	//Load all Towers
	int dfd;
	dfd = sceIoDopen("/Res/towers");
	
	//get all the folders name in towers directory to load
	if(dfd > 0)
	{
		struct SceIoDirent dir;
		memset(&dir,0,sizeof(SceIoDirent));

		while(sceIoDread(dfd, &dir) > 0)
		{
			if(dir.d_stat.st_attr & FIO_SO_IFDIR)
			{
				if(dir.d_name[0] != '.')
				{
					LoadTower(dir.d_name);
				}
			}
			else
			{
				oslFatalError("Error reading towers folder!");
			}
		}
		sceIoDclose(dfd);
	}
	mGameGUI->LoadStuffs();
}

GameScreen::~GameScreen()
{
	delete(mGameMap);
	delete(mGameGUI);
}

void GameScreen::draw()
{
	mGameMap->draw();

	//mGameGUI->???;  render offset? cursor ?
	mGameGUI->draw();	
#ifdef DEBUG
	oslPrintf_xy(0,20,"Value of joystick X : %d",osl_keys->analogX);
	oslPrintf_xy(0,30,"Value of joystick Y : %d",osl_keys->analogY);
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
	mGameGUI->Update(/*timePassed*/);
	
	if(osl_keys->pressed.start)
	{	
		oslFlushKey();
		mNextScreen = ScreenManager::SCREEN_PAUSE; //Pause game!
	}
	if(osl_keys->pressed.circle)
	{
		oslFlushKey();
		//mNextScreen = ScreenManager::SCREEN_GAME_OPTIONS; //go back CLR
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

string **GameScreen::GetMenuTowers() const
{
	return mGameMap->mTowersMenu;
}

Tower *GameScreen::GetTower(const string &towerName) const
{
	map<string, Tower*>::const_iterator iter = mTowers.find(towerName);
	if (iter != mTowers.end())
		return iter->second;
	else
		return NULL;
}

void GameScreen::LoadTower(const string &towerName)
{
	Tower* t = new Tower(towerName);
	mTowers[t->mTowerDirName] = t;
}