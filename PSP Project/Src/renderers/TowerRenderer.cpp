//**************************************************************************
//		PSP Project: 'Gods Defense' - TowerRenderer.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/renderers/TowerRenderer.h"
#include "../../Include/util/Drawing.h"
#include "../../Include/util/Sprites.h"
#include <math.h>

void TowerRenderer::RenderTower(const Tower *tower, const Coordinates2D &position, float scrollOffset)
{
	if (tower && tower->mTowerImg)
	{
		if (tower->mTowerFrameCount > 1)
			DrawImageFrameXY(tower->mTowerImg, position.X, scrollOffset + position.Y, 0);
		else
			oslDrawImageXY(tower->mTowerImg, position.X, scrollOffset + position.Y);
	}
}

void TowerRenderer::RenderTowerInstance(const TowerInstance *towerInstance, float scrollOffset)
{
	if (towerInstance && towerInstance->mTower && towerInstance->mTower->mTowerImg)
	{
		int drawWidth = towerInstance->mTower->mTowerImg->sizeX;
		int drawHeight = towerInstance->mTower->mTowerImg->sizeY;
		if (towerInstance->mTower->mTowerFrameCount > 1)
		{
			drawWidth = towerInstance->mTower->mTowerFrameWidth;
			drawHeight = towerInstance->mTower->mTowerFrameHeight;
		}

		int x = towerInstance->mTowerPosition.X + (drawWidth / 2);
		int y = (drawHeight / 2) + towerInstance->mTowerPosition.Y + scrollOffset;

		if (towerInstance->mTower->mTowerFrameCount > 1)
			DrawImageFrameXY(towerInstance->mTower->mTowerImg, x, y, towerInstance->GetCurrentFrame());
		else
			oslDrawImageXY(towerInstance->mTower->mTowerImg, x, y);
	}
}

void TowerRenderer::RenderRangeCircle(const Tower *tower, const Coordinates2D &position, 
                                      unsigned int towerLevel, const OSL_COLOR color, float scrollOffset)
{
	if (tower && towerLevel < tower->mTowerVector.size())
	{
		Drawing::drawCircle(position.X, scrollOffset + position.Y, 
		                   tower->mTowerVector[towerLevel].mRange, color);
	}
}

void TowerRenderer::RenderTowerInstanceRangeCircle(const TowerInstance *towerInstance, 
                                                   const OSL_COLOR color, float scrollOffset)
{
	if (!towerInstance || !towerInstance->mTower)
		return;
	
	Coordinates2D buildingPosition = Coordinates2D(towerInstance->mTowerPosition.X, 
	                                             towerInstance->mTowerPosition.Y);
	//Snap :D \o/ workss
	buildingPosition.X = (((int)(buildingPosition.X) / 32) * 32) + 16; // 32 == Width
	buildingPosition.Y = (((int)(buildingPosition.Y) / 32) * 32) + 16; // 32 == Height
	
	RenderRangeCircle(towerInstance->mTower, buildingPosition, 
	                 towerInstance->mTowerLevel, color, scrollOffset);
}
