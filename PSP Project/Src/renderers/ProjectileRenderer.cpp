//**************************************************************************
//		PSP Project: 'Gods Defense' - ProjectileRenderer.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/renderers/ProjectileRenderer.h"
#include "../../Include/GameGUI.h"
#include "../../Include/Enemy.h"
#include "../../Include/util/Sprites.h"
#include <math.h>

void ProjectileRenderer::RenderArrow(const ProjectileInstance *projectile, float angle, float scrollOffset)
{
	if (!projectile || !projectile->mProjectileImg)
		return;
	
	projectile->mProjectileImg->centerX = projectile->GetFrameCount() > 1 ? projectile->GetFrameWidth() / 2 : projectile->mProjectileImg->sizeX / 2;
	projectile->mProjectileImg->centerY = projectile->GetFrameCount() > 1 ? projectile->GetFrameHeight() / 2 : projectile->mProjectileImg->sizeY / 2;
	projectile->mProjectileImg->angle = (angle * 180/M_PI);
	DrawImageFrameXY(
		projectile->mProjectileImg,
		projectile->mProjectilePosition.X,
		scrollOffset + projectile->mProjectilePosition.Y,
		projectile->GetCurrentFrame()
	);
}

void ProjectileRenderer::RenderIce(const ProjectileInstance *projectile, float angle, float scrollOffset)
{
	if (!projectile || !projectile->mProjectileImg)
		return;
	
	projectile->mProjectileImg->centerX = projectile->GetFrameCount() > 1 ? projectile->GetFrameWidth() / 2 : projectile->mProjectileImg->sizeX / 2;
	projectile->mProjectileImg->centerY = projectile->GetFrameCount() > 1 ? projectile->GetFrameHeight() / 2 : projectile->mProjectileImg->sizeY / 2;
	projectile->mProjectileImg->angle = (angle * 180/M_PI);
	DrawImageFrameXY(
		projectile->mProjectileImg,
		projectile->mProjectilePosition.X,
		scrollOffset + projectile->mProjectilePosition.Y,
		projectile->GetCurrentFrame()
	);
}

void ProjectileRenderer::RenderFire(const ProjectileInstance *projectile, float angle, float scrollOffset)
{
	if (!projectile || !projectile->mProjectileImg)
		return;
	
	projectile->mProjectileImg->centerX = projectile->GetFrameCount() > 1 ? projectile->GetFrameWidth() / 2 : projectile->mProjectileImg->sizeX / 2;
	projectile->mProjectileImg->centerY = projectile->GetFrameCount() > 1 ? projectile->GetFrameHeight() / 2 : projectile->mProjectileImg->sizeY / 2;
	projectile->mProjectileImg->angle = (angle * 180/M_PI);
	DrawImageFrameXY(
		projectile->mProjectileImg,
		projectile->mProjectilePosition.X,
		scrollOffset + projectile->mProjectilePosition.Y,
		projectile->GetCurrentFrame()
	);
}

void ProjectileRenderer::RenderLightning(const ProjectileInstance *projectile, 
                                        const Coordinates2D &targetPosition, float scrollOffset)
{
	if (!projectile || !projectile->mProjectileImg)
		return;
	
	projectile->mProjectileImg->centerX = projectile->GetFrameCount() > 1 ? projectile->GetFrameWidth() / 2 : projectile->mProjectileImg->sizeX / 2;
	projectile->mProjectileImg->centerY = projectile->GetFrameCount() > 1 ? projectile->GetFrameHeight() / 2 : projectile->mProjectileImg->sizeY / 2;
	DrawImageFrameXY(
		projectile->mProjectileImg,
		targetPosition.X,
		scrollOffset + targetPosition.Y,
		projectile->GetCurrentFrame()
	);
}
