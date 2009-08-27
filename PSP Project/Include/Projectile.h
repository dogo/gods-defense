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
#include "../Include/GameScreen.h"
#include "../Include/GodLibrary.h"

enum ProjectileType
{
	PT_Arrow,
	PT_Ice,
	PT_Lightning,
	PT_Fire
};

class ProjectileInstance
{
public:
	ProjectileInstance(TowerInstance *shooter, EnemyInstance *target);
	virtual ~ProjectileInstance();
	static void CreateProjectile(TowerInstance *shooter, EnemyInstance *target);

	//TODO : :D write this functions
	//virtual void Update(unsigned timePassed) = 0;
	//virtual void ProjectileRender() = 0;

	static OSL_IMAGE *LoadProjectileImage(const char &projectileType, char *filename);

private:
	bool mEnemyIsDead;
	Coordinates2D mProjectilePosition;
	EnemyInstance *mTarget;
	OSL_IMAGE *mProjectileSprite;
	OSL_SOUND *mFireSound;
	OSL_SOUND *mHitSound;
	int mTowerDamage;
	float mSlowAmount;
	int mSlowLength;
	bool mHitsFlyer;
	bool mHitsLand;
};

#endif