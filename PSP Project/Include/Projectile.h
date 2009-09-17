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
	bool DisappearProjectile();
	virtual void Update(u64 timePassed) = 0;
	virtual void ProjectileRender() = 0;

	static OSL_IMAGE *LoadProjectileImage(const char &projectileType, char *filename);

	OSL_SOUND *mFireSound;
	OSL_SOUND *mHitSound;
	Coordinates2D mProjectilePosition;
	OSL_IMAGE *mProjectileImg;
	int mHitSize;
	EnemyInstance *mTarget;
	bool mDisappearProjectile;
private:
	int mTowerDamage;
	float mSlowAmount;
	int mSlowLength;
	bool mHitsFlyer;
	bool mHitsLand;

};


class ArrowInstance : public ProjectileInstance
{
public:
	ArrowInstance(TowerInstance *shooter, EnemyInstance *target);
	virtual ~ArrowInstance();

	//ShotInstance
	virtual void Update(u64 timePassed);
	virtual void ProjectileRender();
private:
	int mMovementSpeed;
	float mAngle; //Last calculated angle
};

#endif