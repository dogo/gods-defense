//**************************************************************************
//		PSP Project: 'Gods Defense' - ProjectileRenderer.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_PROJECTILE_RENDERER_H
#define INCLUDED_PROJECTILE_RENDERER_H

#include "../Projectile.h"
#include "../util/Coordinates2D.h"
#include <oslib/oslib.h>

/**
 * ProjectileRenderer - Handles all rendering operations for projectiles
 */
class ProjectileRenderer
{
public:
	/**
	 * Render an arrow projectile
	 * @param projectile The projectile instance
	 * @param angle The angle of the projectile
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderArrow(const ProjectileInstance *projectile, float angle, float scrollOffset);
	
	/**
	 * Render an ice projectile
	 * @param projectile The projectile instance
	 * @param angle The angle of the projectile
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderIce(const ProjectileInstance *projectile, float angle, float scrollOffset);
	
	/**
	 * Render a fire projectile
	 * @param projectile The projectile instance
	 * @param angle The angle of the projectile
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderFire(const ProjectileInstance *projectile, float angle, float scrollOffset);
	
	/**
	 * Render a lightning projectile
	 * @param projectile The projectile instance
	 * @param targetPosition The target position
	 * @param scrollOffset The scroll offset for the map
	 */
	static void RenderLightning(const ProjectileInstance *projectile, 
	                           const Coordinates2D &targetPosition, float scrollOffset);
};

#endif

