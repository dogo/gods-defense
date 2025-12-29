//**************************************************************************
//		PSP Project: 'Gods Defense' - MapRenderer.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_MAP_RENDERER_H
#define INCLUDED_MAP_RENDERER_H

#include "../Map.h"
#include "../Tower.h"
#include "../util/Coordinates2D.h"
#include <oslib/oslib.h>

/**
 * MapRenderer - Handles all rendering operations for maps
 */
class MapRenderer
{
public:
	/**
	 * Render the map image
	 * @param mapImage The map image to render
	 */
	static void RenderMap(OSL_IMAGE *mapImage);
	
	/**
	 * Render the build grid
	 * @param collisionMap The collision map
	 * @param gridWidth Width of the grid
	 * @param gridHeight Height of the grid
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderBuildGrid(bool **collisionMap, int gridWidth, int gridHeight, float scrollOffset);
};

#endif

