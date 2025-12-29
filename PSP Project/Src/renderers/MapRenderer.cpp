//**************************************************************************
//		PSP Project: 'Gods Defense' - MapRenderer.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/renderers/MapRenderer.h"
#include "../../Include/util/Drawing.h"

void MapRenderer::RenderMap(OSL_IMAGE *mapImage)
{
	if (mapImage)
	{
		oslDrawImage(mapImage);
	}
}

void MapRenderer::RenderBuildGrid(bool **collisionMap, int gridWidth, int gridHeight, float scrollOffset)
{
	if (!collisionMap)
		return;
	
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			if (collisionMap[i][j])
			{
				oslDrawFillRect(i*32, j*32 + scrollOffset, i*32+31, j*32+31 + scrollOffset, ALPHA_COLOR_BLACK);
				oslDrawRect(i*32, j*32 + scrollOffset, i*32+32, j*32+32 + scrollOffset, COLOR_WHITE);
			}
		}
	}
}

