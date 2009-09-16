//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameScreen.h"
#include "../Include/ScreenManager.h"

//Statics
bool gWin;

GameScreen::GameScreen()
{
	GameGUI::InitGUI(this);
	
	mGameGUI = GameGUI::Instance();

	mGameMap = Map::InitMap();

	LoadMap(gChoosedMap);

	LoadFirstPartForMap();

	mActiveWaves = 0;
	mWaveIsRunning = false;

	gWin = false;
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
	oslPrintf_xy(0,40,"mPlayerLives %d\n",mPlayerLives);
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

void GameScreen::update(u64 timePassed)
{
	/*
	*	Dogo : Vai buga futuramente, o pause nao pode deletar a tela anterior ou seja a tela do jogo,
	*	pois quando voltar do pause nao vai mais ter referencia do jogo.
	*   TODO : Pensar como pausar!
	*   Dogo 10/03/09 -> Congelar o jogo, pintar a tela de pause por cima, quando voltar ao jogo repintar e voltar o
	*   estado do jogo.
	*/
	mGameGUI->Update(timePassed);

	//Run Waves
	if (mWaveIsRunning)
	{
		//Spawn Enemies
		for (unsigned int i = 0; i < mActiveWaves; i++)
		{
			if (mGameMap->mWaves[i]->SpawnUpdate(timePassed))
			{
				string newEnemy = "";
				int newEnemyLevel = 0;
				mGameMap->mWaves[i]->GetCurrentWaveEnemy(newEnemy, newEnemyLevel);
				EnemyInstance *ei = new EnemyInstance(mGameMap->mWaves[i], mEnemies[newEnemy], mGameMap->mWaves[i]->mPath, newEnemyLevel);
				mRealEnemies.push_back(ei);
			}
		}
		
		//Check for waves ending
		for (unsigned int j = 0; j < mActiveWaves; j++)
		{
			mWaveIsRunning = false;

			if (mGameMap->mWaves[j]->EndOfWave())
			{
				//Give Money
				mPlayerMoney = (mPlayerMoney * (1.5));
				printf("mPlayerMoney: %d\n", mPlayerMoney);
			}
			
			if (!mGameMap->mWaves[j]->EndOfWave())
			{
				mWaveIsRunning = true;
				printf("Wave Is Running\n");
			}
		}
	}

	//Run Enemies
	mDeleteEnemy = false;
	list<EnemyInstance*>::iterator ei_iter;
	for (ei_iter = mRealEnemies.begin(); ei_iter != mRealEnemies.end(); ei_iter++)
	{
		(*ei_iter)->Update(timePassed);

		EnemyState enemyState = (*ei_iter)->GetEnemyState();
		printf("EnemyState %d\n",enemyState);
		switch (enemyState)
		{
		case NOTHING_HAPPENING: //Nothing happened
		break;

		case ENEMY_DIED: //Just died, death animation in progress, give player $$$
			{
			//Award player money
			mPlayerMoney += (*ei_iter)->GetGold();
			}
		break;

		case ENEMY_HIT_THE_END: //Got to the end of the path, make the player lose a life
			//Lose life
			mPlayerLives--;
		break;

		case ENEMY_FULLY_DEAD: //Dead and done
			mDeleteEnemy = true;
		break;
		}
	}

	//Delete enemies from list that are fully dead
	while (mDeleteEnemy)
	{
		mDeleteEnemy = false;
		for (ei_iter = mRealEnemies.begin(); ei_iter != mRealEnemies.end(); ei_iter++)
		{
			if ((*ei_iter)->GetEnemyState() == ENEMY_FULLY_DEAD)
			{
				mRealEnemies.erase(ei_iter);
				mDeleteEnemy = true;
				break;
			}
		}
	}

	//Check if player is dead
	if (mGameState != GS_GAME_OVER)
	{
		if (mPlayerLives <= 0)
		{
			//Loose
			SetGameState(GS_GAME_OVER);
			mNextScreen = ScreenManager::SCREEN_ENDING;
		}
		//Maybe end of game.
		else if (!mWaveIsRunning && mActiveWaves >= mGameMap->mWaves.size())
		{
			//Win
			gWin = true;
			SetGameState(GS_GAME_OVER);
			mNextScreen = ScreenManager::SCREEN_ENDING;
		}
	}
	
	if(osl_keys->pressed.start)
	{	
		oslFlushKey();
		mNextScreen = ScreenManager::SCREEN_PAUSE; //Pause game!
	}
	if(osl_keys->pressed.circle)
	{
		oslFlushKey();
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
	{
		return;
	}

	mWaveIsRunning = true;
	if(mActiveWaves < mGameMap->mWaves.size());
	{
		mGameMap->mWaves[mActiveWaves]->StartEnemySpawn();
		mActiveWaves++;
	}
}
