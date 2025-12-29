//**************************************************************************
//		PSP Project: 'Gods Defense' - TowerRenderer.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_TOWER_RENDERER_H
#define INCLUDED_TOWER_RENDERER_H

#include "../Tower.h"
#include "../util/Coordinates2D.h"
#include <oslib/oslib.h>

/**
 * TowerRenderer - Handles all rendering operations for towers
 */
class TowerRenderer
{
public:
	/**
	 * Render a tower at the specified position
	 * @param tower The tower template to render
	 * @param position The position to render at
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderTower(const Tower *tower, const Coordinates2D &position, float scrollOffset);
	
	/**
	 * Render a tower instance
	 * @param towerInstance The tower instance to render
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderTowerInstance(const TowerInstance *towerInstance, float scrollOffset);
	
	/**
	 * Render the range circle for a tower
	 * @param tower The tower template
	 * @param position The position of the tower
	 * @param towerLevel The level of the tower
	 * @param color The color of the circle
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderRangeCircle(const Tower *tower, const Coordinates2D &position, 
	                              unsigned int towerLevel, const OSL_COLOR color, float scrollOffset);
	
	/**
	 * Render the range circle for a tower instance
	 * @param towerInstance The tower instance
	 * @param color The color of the circle
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderTowerInstanceRangeCircle(const TowerInstance *towerInstance, 
	                                           const OSL_COLOR color, float scrollOffset);
};

#endif

