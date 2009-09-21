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
		mKindOfProjectile = new ArrowInstance(shooter, target);
		break;
	case PT_Ice:
		//TODO : kind of Projectile Instance
		break;
	case PT_Lightning:
		//TODO : kind of Projectile Instance
		break;
	case PT_Fire:
		//TODO : kind of Projectile Instance
		break;
	default:
		return;
	}
	GameScreen::gGameReference->mRealProjectiles.push_back(mKindOfProjectile);
}

OSL_IMAGE *ProjectileInstance::LoadProjectileImage(const char &projectileType, char *filename)
{
	switch(projectileType)
	{
	case PT_Arrow:
		return oslLoadImageFilePNG(filename, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	
	case PT_Ice:
		return oslLoadImageFilePNG(filename, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	case PT_Lightning:
		return oslLoadImageFilePNG(filename, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	case PT_Fire:
		return oslLoadImageFilePNG(filename, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	
	default:
		return NULL;
	}
}

ProjectileInstance::ProjectileInstance(TowerInstance *shooter, EnemyInstance *target)
{
	mDisappearProjectile = false;
	mProjectilePosition = shooter->mTowerPosition;
	mProjectileImg = shooter->mTower->mProjectileImg;
	mFireSound = shooter->mTower->mFireSound;
	mHitSound = shooter->mTower->mHitSound;
	mTarget = target;
	mHitSize = target->mEnemy->mSize;
	mHitsFlyer = shooter->mTower->mHitsFlyer;
	mHitsLand = shooter->mTower->mHitsLand;
	mSlowAmount = shooter->mTower->mTowerVector[shooter->mCurrentMap].mSlowAmount;
	mSlowLength = shooter->mTower->mTowerVector[shooter->mCurrentMap].mSlowLength;
	mTowerDamage = shooter->mTower->mTowerVector[shooter->mCurrentMap].mDamage;
}

ProjectileInstance::~ProjectileInstance()
{
}

bool ProjectileInstance::DisappearProjectile()
{
	return mDisappearProjectile;
}

//ArrowInstance
ArrowInstance::ArrowInstance(TowerInstance *shooter, EnemyInstance *target)	: ProjectileInstance(shooter, target)
{
	mMovementSpeed = shooter->mTower->mTowerVector[shooter->mCurrentMap].mSpeed;

	if (mFireSound != NULL)
		oslPlaySound(mFireSound,1);
	
}

ArrowInstance::~ArrowInstance()
{
}

void ArrowInstance::Update(u64 timePassed)
{
	//Calculate angle to target, move towards it
	float movement = mHitSize + (mMovementSpeed * timePassed / 1000.0f); //distance I'll move this tick
	movement *= movement;
	float xdif = mProjectilePosition.X - mTarget->mEnemyPosition.X;
	float ydif = mProjectilePosition.Y - mTarget->mEnemyPosition.Y;
	float distance = (xdif * xdif) + (ydif * ydif); //Pythagoras without the sqrt
	if (distance < movement)
	{
		//We hit!
		DealDamage();
		if (mHitSound != NULL)
			oslPlaySound(mHitSound,2);
		
		mDisappearProjectile = true;
	}

	//Calculate new position
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);
	float changeX = mMovementSpeed * cos(mAngle) * timePassed / 1000;
	float changeY = mMovementSpeed * sin(mAngle) * timePassed / 1000;
	mProjectilePosition.X += changeX;
	mProjectilePosition.Y += changeY;
}

void ArrowInstance::ProjectileRender()
{
	oslDrawImageXY(mProjectileImg, mProjectilePosition.X, GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount+mProjectilePosition.Y);
}

void ProjectileInstance::DealDamage()
{
	mProjectilePosition = mTarget->mEnemyPosition;
	mTarget->EnemyReciveDamage(mTowerDamage, mSlowAmount, mSlowLength);
}