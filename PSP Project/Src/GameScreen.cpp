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

	mActiveWaves = 0;
	mWaveIsRunning = false;
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
	//reset towers :D
	CleanTowers();

	//reset enemies :D
	CleanEnemies();

	//Load map image
	mGameMap->LoadMapImage();

	//Load all Enemies
	int roorDirEnemies = sceIoDopen("/Res/enemies");

	//get all the folders name in enemies directory to load
	if(roorDirEnemies > 0)
	{
		struct SceIoDirent dir;
		memset(&dir,0,sizeof(SceIoDirent));

		while(sceIoDread(roorDirEnemies, &dir) > 0)
		{
			if(dir.d_stat.st_attr & FIO_SO_IFDIR)
			{
				if(dir.d_name[0] != '.')
				{
					LoadEnemy(dir.d_name);
				}
			}
			else
			{
				oslFatalError("Error reading enemies folder!");
			}
		}
		sceIoDclose(roorDirEnemies);
	}

	//Load all Towers
	int roorDirTowers = sceIoDopen("/Res/towers");
	
	//get all the folders name in towers directory to load
	if(roorDirTowers > 0)
	{
		struct SceIoDirent dir;
		memset(&dir,0,sizeof(SceIoDirent));

		while(sceIoDread(roorDirTowers, &dir) > 0)
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
		sceIoDclose(roorDirTowers);
	}
	mGameGUI->LoadStuffs();
}

GameScreen::~GameScreen()
{
	CleanTowers();
	delete(mGameMap);
	delete(mGameGUI);
}

void GameScreen::draw()
{
	mGameMap->draw();
	oslPrintf_xy(0,20,"mPlayerMoney %d", mPlayerMoney);

	if(mGameState == GS_MAP_PLACE_TOWER)
	{
		for (int i=0; i<15 ; i++)
			for (int j=0; j<15; j++)
			{
				if(mGameMap->mCollisionMap[i][j])
				{
					oslDrawFillRect(i*32,j*32+mGameMap->mScrollAmount,i*32+31,j*32+31+mGameMap->mScrollAmount,ALPHA_COLOR_BLACK);
					oslDrawRect(i*32,j*32+mGameMap->mScrollAmount,i*32+32,j*32+32+mGameMap->mScrollAmount,COLOR_WHITE);
				}
			}
	}
	//dogo : not working yet
	//Draw the enemies
	list<EnemyInstance*>::const_iterator realEnemies_iter;
	for (realEnemies_iter = mRealEnemies.begin(); realEnemies_iter != mRealEnemies.end(); realEnemies_iter++)
	{
		(*realEnemies_iter)->RenderEnemy();
	}

	//Draw the towers
	list<TowerInstance*>::const_iterator realTowers_iter;
	for (realTowers_iter = mRealTowers.begin(); realTowers_iter != mRealTowers.end(); realTowers_iter++)
	{
		(*realTowers_iter)->RenderTower();
	}

	mGameGUI->RenderPlacingTower();
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

	//Check if we need to run a new wave
	if (mActiveWaves > 0)
	{
		RunNextWave(true);
	}
	//Run Waves
	if (mWaveIsRunning)
	{
		//TODO :  Spawn the enemies and check for waves ending.
	}
	
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

string *GameScreen::GetMenuTowers() const
{
	return mGameMap->mTowersMenu;
}

int const GameScreen::GetPlayerMoney()
{
	return mPlayerMoney;
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
	Tower *t = new Tower(towerName);
	mTowers[t->mTowerDirName] = t;
}

void GameScreen::LoadEnemy(const string &enemyName)
{
	Enemy* e = new Enemy(enemyName);
	mEnemies[e->mEnemyDirName] = e;
}

void GameScreen::CleanTowers()
{
	//Clean Towers
	map<string, Tower*>::iterator t_iter;
	for (t_iter = mTowers.begin(); t_iter != mTowers.end(); t_iter++)
	{
		delete t_iter->second;
	}
	mTowers.clear();
}

void GameScreen::CleanEnemies()
{
	//Clear Enemies
	map<string, Enemy*>::iterator e_iter;
	for (e_iter = mEnemies.begin(); e_iter != mEnemies.end(); e_iter++)
	{
		delete e_iter->second;
	}
	mEnemies.clear();
}

bool GameScreen::TryBuildTower(Tower *tower, Coordinates2D position)
{
	if (mGameMap->TestBuildCollision(position, tower))
	{
		mGameMap->DeployTowerAt(position, tower);
		mPlayerMoney -= tower->mTowerVector[0].mCost;
		mRealTowers.push_back(new TowerInstance(tower, position));
		return true;
	}
	else
	{
		//Player can't build here
		return false;
	}
}

Map *GameScreen::GetGameMap()
{
	return mGameMap;
}

void GameScreen::TryRunNextWave()
{
	RunNextWave(false);
}

void GameScreen::RunNextWave(const bool &forceRunNow)
{
	if (!forceRunNow && mWaveIsRunning)
		return;

	mWaveIsRunning = true;
	mGameMap->mWaves[mActiveWaves]->StartEnemySpawn();
	mActiveWaves++;
}
