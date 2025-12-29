//**************************************************************************
//		PSP Project: 'Gods Defense' - ProjectileRenderer.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/renderers/ProjectileRenderer.h"
#include "../../Include/GameGUI.h"
#include "../../Include/Enemy.h"
#include <math.h>

void ProjectileRenderer::RenderArrow(const ProjectileInstance *projectile, float angle, float scrollOffset)
{
	if (!projectile || !projectile->mProjectileImg)
		return;
	
	projectile->mProjectileImg->angle = (angle * 180/M_PI);
	oslDrawImageXY(
		projectile->mProjectileImg, 
		projectile->mProjectilePosition.X, 
		scrollOffset + projectile->mProjectilePosition.Y
	);
}

void ProjectileRenderer::RenderIce(const ProjectileInstance *projectile, float angle, float scrollOffset)
{
	if (!projectile || !projectile->mProjectileImg)
		return;
	
	projectile->mProjectileImg->angle = (angle * 180/M_PI);
	oslDrawImageXY(
		projectile->mProjectileImg, 
		projectile->mProjectilePosition.X, 
		scrollOffset + projectile->mProjectilePosition.Y
	);
}

void ProjectileRenderer::RenderFire(const ProjectileInstance *projectile, float angle, float scrollOffset)
{
	if (!projectile || !projectile->mProjectileImg)
		return;
	
	projectile->mProjectileImg->angle = (angle * 180/M_PI);
	oslDrawImageXY(
		projectile->mProjectileImg, 
		projectile->mProjectilePosition.X, 
		scrollOffset + projectile->mProjectilePosition.Y
	);
}

void ProjectileRenderer::RenderLightning(const ProjectileInstance *projectile, 
                                        const Coordinates2D &targetPosition, float scrollOffset)
{
	if (!projectile || !projectile->mProjectileImg)
		return;
	
	projectile->mProjectileImg->centerX = projectile->mProjectileImg->sizeX/2;
	projectile->mProjectileImg->centerY = projectile->mProjectileImg->sizeY/2;
	oslDrawImageXY(
		projectile->mProjectileImg, 
		targetPosition.X, 
		scrollOffset + targetPosition.Y
	);
}

