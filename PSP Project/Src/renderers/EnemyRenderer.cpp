//**************************************************************************
//		PSP Project: 'Gods Defense' - EnemyRenderer.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/renderers/EnemyRenderer.h"
#include "../../Include/util/Sprites.h"
#include "../../Include/GameGUI.h"
#include <math.h>

void EnemyRenderer::RenderEnemy(EnemyInstance *enemyInstance, float scrollOffset)
{
	if (!enemyInstance || enemyInstance->EnemyIsDead() || !enemyInstance->mEnemy || !enemyInstance->mEnemy->mEnemyImg)
		return;

	enemyInstance->mEnemy->mEnemyImg->centerX = 16; // Enemy / 2
	enemyInstance->mEnemy->mEnemyImg->angle = (enemyInstance->mAngle * 180/M_PI);
	
	DrawImageFrameXY(
		enemyInstance->mEnemy->mEnemyImg, 
		enemyInstance->mEnemyPosition.X, 
		scrollOffset + enemyInstance->mEnemyPosition.Y, 
		enemyInstance->mCurrentFrames
	);
	
	RenderEnemyHealthBar(enemyInstance, scrollOffset);
}

void EnemyRenderer::RenderEnemyHealthBar(EnemyInstance *enemyInstance, float scrollOffset)
{
	if (!enemyInstance || !enemyInstance->mEnemy)
		return;
	
	int w = 32 * enemyInstance->mHealth / enemyInstance->mEnemy->mEnemyVector[enemyInstance->mStat].mHealth;
	
	// Red background
	oslDrawFillRect(
		enemyInstance->mEnemyPosition.X - 16, 
		scrollOffset + enemyInstance->mEnemyPosition.Y - 20, 
		enemyInstance->mEnemyPosition.X + 16, 
		scrollOffset + enemyInstance->mEnemyPosition.Y - 16, 
		COLOR_RED
	);
	
	// Green health bar
	oslDrawFillRect(
		enemyInstance->mEnemyPosition.X - 16, 
		scrollOffset + enemyInstance->mEnemyPosition.Y - 20, 
		(enemyInstance->mEnemyPosition.X - 16) + w, 
		scrollOffset + enemyInstance->mEnemyPosition.Y - 16, 
		COLOR_GREEN
	);
}

