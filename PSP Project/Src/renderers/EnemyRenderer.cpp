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
	if (!enemyInstance || !enemyInstance->mEnemy || !enemyInstance->mEnemy->mEnemyImg)
		return;

	bool dying = (enemyInstance->mEnemyState == ENEMY_DYING);
	if (enemyInstance->EnemyIsDead() && !dying)
		return;

	OSL_IMAGE *img = enemyInstance->mEnemy->mEnemyImg;
	float y = scrollOffset + enemyInstance->mEnemyPosition.Y;

	// Flyers hover
	if (enemyInstance->EnemyCanFly())
		y += 2 * sinf(osl_vblCount * 0.15f + enemyInstance->mEnemyPosition.X);

	// Sprites are drawn upright facing right: mirror instead of rotating
	img->angle = 0;
	oslSetImageFrame(img, enemyInstance->mCurrentFrames);
	if (cosf(enemyInstance->mAngle) < 0)
		oslMirrorImageH(img);

	if (dying) // fade out
		oslSetAlpha(OSL_FX_TINT, RGBA(255, 255, 255, 255 - 255 * enemyInstance->mDeathTime / EnemyInstance::DEATH_FADE_TIME));
	else if (enemyInstance->mHitFlashTime > 0)
		oslSetAlpha(OSL_FX_TINT, RGBA(255, 90, 90, 255));
	else if (enemyInstance->mSlowLength > 0)
		oslSetAlpha(OSL_FX_TINT, RGBA(140, 180, 255, 255));

	oslDrawImageXY(img, enemyInstance->mEnemyPosition.X, y);
	oslSetAlpha(OSL_FX_DEFAULT, 0);

	if (!dying)
		RenderEnemyHealthBar(enemyInstance, scrollOffset);
}

void EnemyRenderer::RenderEnemyHealthBar(EnemyInstance *enemyInstance, float scrollOffset)
{
	if (!enemyInstance || !enemyInstance->mEnemy)
		return;
	
	unsigned int maxHealth = enemyInstance->mEnemy->mEnemyVector[enemyInstance->mStat].mHealth;
	if (maxHealth == 0)
		return;
	int w = 32 * enemyInstance->mHealth / (int)maxHealth;
	
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

