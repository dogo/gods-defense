//**************************************************************************
//		PSP Project: 'Gods Defense' - Projectile.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Projectile.h"


void ProjectileInstance::CreateProjectile(TowerInstance *shooter, EnemyInstance *target)
{
	ProjectileInstance *mKindOfProjectile = NULL;

	switch(shooter->mTower->mProjectileType)
	{
	case PT_Arrow:
		//TODO : kind of Projectile Instance
		break;
	case PT_Ice:
		//TODO : kind of Projectile Instance
		break;
	default:
		return;
	}
}

OSL_IMAGE *ProjectileInstance::LoadProjectileImage(const char &projectileType, char *filename)
{
	switch(projectileType)
	{
	case PT_Arrow:
		return oslLoadImageFilePNG(filename, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	
	case PT_Ice:
		return oslLoadImageFilePNG(filename, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	/*case :
		return oslLoadImageFilePNG(filename, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	*/
	default:
		return NULL;
	}
}

ProjectileInstance::ProjectileInstance(TowerInstance *shooter, EnemyInstance *target)
{
	mEnemyIsDead = false;
	mProjectilePosition = shooter->mPosition;
	mProjectileSprite = shooter->mTower->mProjectileImg;
	mFireSound = shooter->mTower->mFireSound;
	mHitSound = shooter->mTower->mHitSound;
	mTarget = target;
	mHitsFlyer = shooter->mTower->mHitsFlyer;
	mHitsLand = shooter->mTower->mHitsLand;
	mSlowAmount = shooter->mTower->mLevels[shooter->mCurrentMap].mSlowAmount;
	mSlowLength = shooter->mTower->mLevels[shooter->mCurrentMap].mSlowLength;
	mTowerDamage = shooter->mTower->mLevels[shooter->mCurrentMap].mDamage;
}

ProjectileInstance::~ProjectileInstance()
{
}