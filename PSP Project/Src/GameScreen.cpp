//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameScreen.h"
#include "../Include/ScreenManager.h"

//Statics
bool gWin;
bool GameScreen::gPauseGame;
GameScreen *GameScreen::gGameReference = NULL;

GameScreen::GameScreen()
{
	GameGUI::InitGUI(this);
	
	mGameGUI = GameGUI::Instance();

	mGameMap = Map::InitMap();

	LoadMap(gChoosedMap);

	LoadFirstPartForMap();

	pauseScreenReference = new PauseScreen();

	mActiveWaves = 0;
	mWaveIsRunning = false;
	gPauseGame = false;

	gGameReference = this;

	gWin = false;

	mSelectedTower = NULL;

	mAdhocReference = NULL;

#ifndef JPCSP_EMULATOR
	if(gIsClient && oslIsWlanPowerOn())
	{
		mAdhocReference = new Adhoc();
		mAdhocReference->AdhocClient();
	}
	else if (gIsServer && oslIsWlanPowerOn())
	{
		mAdhocReference = new Adhoc();
		mAdhocReference->AdhocServer();
	}
#endif
	mShowDesc = true;
}

void GameScreen::LoadMap(const string &mapName)
{
	mGameState = GS_SCROLL_MAP;
	mGameConnectionState = GCS_DISCONNECTED;
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
	gIsClient = false;
	gIsServer = false;

	//Clear all instance lists
	while (!mRealEnemies.empty())
	{
		mRealEnemies.front()->RemoveReference();
		mRealEnemies.pop_front();
	}
	while (!mRealProjectiles.empty())
	{
		delete (mRealProjectiles.front());
		mRealProjectiles.pop_front();
	}
	while (!mRealTowers.empty())
	{
		delete (mRealTowers.front());
		mRealTowers.pop_front();
	}

	CleanTowers();
	CleanEnemies();
	delete(mGameMap);
	delete(mGameGUI);
	delete(pauseScreenReference);

	if(mAdhocReference != NULL){
		oslAdhocTerm();
		delete(mAdhocReference);
	}
}

void GameScreen::drawGrid()
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

void GameScreen::draw()
{
	//Draw Pause Screen
	if(mGameState == GS_PAUSE_MENU && gPauseGame)
	{
		pauseScreenReference->draw();
		return;
	}

	//Draw Map
	mGameMap->draw();

	//Draw Grid
	if(mGameState == GS_MAP_PLACE_TOWER)
	{
		drawGrid();
	}

	if(mGameState == GS_TOWER_UPGRADE_SELL)
	{
		drawUpgradeCircle();
		//mGameGUI->drawSelectedTowerOptions();
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

	//Draw the Projectiles
	list<ProjectileInstance*>::const_iterator si_iter;
	for (si_iter = mRealProjectiles.begin(); si_iter != mRealProjectiles.end(); si_iter++)
	{
		(*si_iter)->ProjectileRender();
	}

	//Draw GUI
	mGameGUI->RenderPlacingTower();
	mGameGUI->draw();

#ifdef _DEBUG
	if(gIsClient && oslIsWlanPowerOn())
		mAdhocReference->printInfo();
#endif
}

void GameScreen::update(u64 timePassed)
{
	//Run Pause
	if (mGameState == GS_PAUSE_MENU && gPauseGame)
	{
		pauseScreenReference->update(timePassed);
		return;
	}

#ifndef JPCSP_EMULATOR
	if (gIsServer && oslIsWlanPowerOn())
	{
		if(mGameConnectionState == GCS_DISCONNECTED || mGameConnectionState == GCS_WAITING_CONNECTION)
		{
			SetGameConnectionState(GCS_WAITING_CONNECTION);
			bool checkAdhoc = mAdhocReference->serverWaitingConnection();

			if(!checkAdhoc)
			{
				SetGameConnectionState(GCS_CONNECTED);	
			}
		}
		else
		{
			mAdhocReference->printInfo();
		}
	}
#endif
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
				ei->AddReference();
				mRealEnemies.push_back(ei);
			}
		}
		
		//Check for waves ending
		for (unsigned int j = 0; j < mActiveWaves; j++)
		{
			mWaveIsRunning = false;
	
			if (!mGameMap->mWaves[j]->EndOfWave())
			{
				mWaveIsRunning = true;
			}
		}
	}

	//Run Projectiles
	list<ProjectileInstance*>::iterator si_iter;
	for (si_iter = mRealProjectiles.begin(); si_iter != mRealProjectiles.end(); si_iter++)
	{
		(*si_iter)->Update(timePassed);
	}

	//Delete Projectiles that are done
	bool mDeleteProjectile = true;
	while (mDeleteProjectile)
	{
		mDeleteProjectile = false;
		for (si_iter = mRealProjectiles.begin(); si_iter != mRealProjectiles.end(); si_iter++)
		{
			if ((*si_iter)->DisappearProjectile())
			{
				delete (*si_iter);
				mRealProjectiles.erase(si_iter);
				mDeleteProjectile = true;
				break;
			}
		}
	}

	//Run Towers
	list<TowerInstance*>::const_iterator ti_iter;
	for (ti_iter = mRealTowers.begin(); ti_iter != mRealTowers.end(); ti_iter++)
	{
		(*ti_iter)->Update(timePassed, mRealEnemies);
	}

	//Run Enemies
	mDeleteEnemy = false;
	list<EnemyInstance*>::iterator ei_iter;
	for (ei_iter = mRealEnemies.begin(); ei_iter != mRealEnemies.end(); ei_iter++)
	{
		(*ei_iter)->Update(timePassed);

		EnemyState enemyState = (*ei_iter)->GetEnemyState();
		switch (enemyState)
		{
			case NOTHING_HAPPENING: //Nothing happened
			break;

			case ENEMY_DIED: //Just died, give player $$$
				//Award player money
				mPlayerMoney += (*ei_iter)->GetGold();
				//Award player points
				mPlayerPoints += ((*ei_iter)->GetPointsWorth());
			break;

			case ENEMY_HIT_THE_END: //Got to the end of the path, make the player lose a life and gold
				//Lose life
				mPlayerLives--;
				//Lose Gold
				mPlayerMoney -= ((*ei_iter)->GetGold());
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
				(*ei_iter)->RemoveReference();
				mRealEnemies.erase(ei_iter);
				mDeleteEnemy = true;
				break;
			}
		}
	}

	//Check if player is dead
	if (mGameState != GS_GAME_OVER)
	{
		//Show once map description
		if(mShowDesc)
		{
			SetGameState(GS_GAME_LOADED);
			mShowDesc = false;
		}

		if (mPlayerLives <= 0)
		{
			//Loose, if ad hoc is on the other player can continue to play
			sprintf(gScoreBuffer, "%d",(int) GetPlayerScore());
			SetGameState(GS_GAME_OVER);
			mNextScreen = ScreenManager::SCREEN_ENDING;
		}
		//Maybe end of game.
		else if (!mWaveIsRunning && mActiveWaves >= mGameMap->mWaves.size())
		{
			//Win
			sprintf(gScoreBuffer, "%d",(int) GetPlayerScore());
#ifndef JPCSP_EMULATOR
			if(gIsClient && oslIsWlanPowerOn())
			{
				/*
				 *	TODO : Recive msg from server with win status if true send client score and compare with server
				 *	if clientScore < serverScore -> Client loose else client win and set the new state
				 */
				mAdhocReference->clientSendScore(gScoreBuffer);
			}
#endif
			gWin = true;
			SetGameState(GS_GAME_OVER);
			mNextScreen = ScreenManager::SCREEN_ENDING;
		}
	}
	
	if(osl_keys->pressed.start && !gPauseGame)
	{	
		oslFlushKey();
		gPauseGame = !gPauseGame; //Pause game!
		SetGameState(GS_PAUSE_MENU);
	}
}

const GameState GameScreen::GetGameState()
{
	return mGameState;
}

void GameScreen::SetGameConnectionState(const GameConnectionState &newState)
{
	mGameConnectionState = newState;
}

const GameConnectionState GameScreen::GetGameConnectionState()
{
	return mGameConnectionState;
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

int const GameScreen::GetPlayerLives()
{
	return mPlayerLives;
}

float const GameScreen::GetPlayerScore()
{
	return mPlayerPoints;
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

//Try select the tower under the cursor
bool GameScreen::TrySelectTower(const Coordinates2D &position)
{
	mSelectedTower = NULL;
	int cursorX = ((int)position.X / 32);
	int cursorY = ((int)position.Y / 32);

	//Test each tower for a collision
	list<TowerInstance*>::const_iterator ti_iter;
	for (ti_iter = mRealTowers.begin(); ti_iter != mRealTowers.end(); ti_iter++)
	{
		TowerInstance *t = (*ti_iter);
		int towerX = (int)((t->mTowerPosition.X) / 32);
		int towerY = (int)((t->mTowerPosition.Y) / 32);
		
		//If tower collides with cursor position
		if (towerX == cursorX && towerY == cursorY)
		{
			//printf("TOWER SELECTED\n");
			mSelectedTower = t;
			SetGameState(GS_TOWER_UPGRADE_SELL);
			break;
		}
	}
	
	return (mSelectedTower != NULL);
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
		char title[256];
		sprintf(title, "Wave %i of %i", GetNextWaveNumber(), GetWaveCount());
		oslMessageBox(mGameMap->mWaves[mActiveWaves]->mWaveDescription, title, oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
		sceKernelDelayThread(1400);
		mGameMap->mWaves[mActiveWaves]->StartEnemySpawn();
		mActiveWaves++;
	}
}

int GameScreen::GetNextWaveNumber() const
{
	return mActiveWaves + 1;
}

int GameScreen::GetWaveCount() const
{
	return mGameMap->mWaves.size();
}

void GameScreen::drawUpgradeCircle()
{
	//Draw the current range for any selected tower
	mSelectedTower->RenderRangeCircle(COLOR_RED);
	if (mSelectedTower->mTowerLevel+1 < mSelectedTower->mTower->mTowerVector.size()) //If there is any upgrade to do
	{
		Coordinates2D buildingPosition = Coordinates2D::Coordinates2D(mSelectedTower->mTowerPosition.X, mSelectedTower->mTowerPosition.Y);
		buildingPosition.X = (((int)(buildingPosition.X) / 32) * 32) + 16; // 32 == Width
		buildingPosition.Y = (((int)(buildingPosition.Y) / 32) * 32) + 16; // 32 == Heigth
		mSelectedTower->mTower->RenderRangeCircle(buildingPosition, mSelectedTower->mTowerLevel+1, COLOR_BLUE);
	}
}

bool GameScreen::TryUpgradeSelectedTower()
{
	Tower *t = mSelectedTower->mTower;

	//Tower not maxed can afford
	if (mSelectedTower->mTowerLevel+1 < t->mTowerVector.size() && mPlayerMoney >= t->mTowerVector[mSelectedTower->mTowerLevel+1].mCost) 
	{
		mPlayerMoney -= t->mTowerVector[mSelectedTower->mTowerLevel+1].mCost;
		mSelectedTower->mTowerLevel += 1;
		printf("Upgraded to level %d\n",mSelectedTower->mTowerLevel);
		return true;
	}
	else
	{
		return false;
	}
}
