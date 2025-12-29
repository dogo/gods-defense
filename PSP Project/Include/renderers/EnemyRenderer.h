//**************************************************************************
//		PSP Project: 'Gods Defense' - EnemyRenderer.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_ENEMY_RENDERER_H
#define INCLUDED_ENEMY_RENDERER_H

#include "../Enemy.h"
#include "../util/Coordinates2D.h"
#include <oslib/oslib.h>

/**
 * EnemyRenderer - Handles all rendering operations for enemies
 */
class EnemyRenderer
{
public:
	/**
	 * Render an enemy instance
	 * @param enemyInstance The enemy instance to render
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderEnemy(EnemyInstance *enemyInstance, float scrollOffset);
	
	/**
	 * Render the health bar for an enemy
	 * @param enemyInstance The enemy instance
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderEnemyHealthBar(EnemyInstance *enemyInstance, float scrollOffset);
};

#endif

