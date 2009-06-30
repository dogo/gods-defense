//**************************************************************************
//		PSP Project: 'Gods Defense' - Projectile.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_PROJECTILE_H
#define INCLUDED_PROJECTILE_H

//Class Declarations
class ProjectileInstance;

#include "../Include/Tower.h"
#include "../Include/Enemy.h"
#include "../Include/GodLibrary.h"

enum ProjectileType
{
	PT_Arrow,
	PT_Ice
	//TODO : Define all Projectiles Types
};

class ProjectileInstance
{
public:
	static void CreateProjectile(TowerInstance *shooter, EnemyInstance *target);
	virtual ~ProjectileInstance();

	OSL_IMAGE *LoadProjectileImage(const char &projectileType);

private:
	OSL_IMAGE *m_ProjectileSprite;
};

#endif