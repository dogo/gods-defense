//**************************************************************************
//		PSP Project: 'Gods Defense' - Projectile.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Projectile.h"
#include "../Include/renderers/ProjectileRenderer.h"
#include "../Include/GameGUI.h"


void ProjectileInstance::CreateProjectile(TowerInstance *shooter, EnemyInstance *target)
{
	ProjectileInstance *mKindOfProjectile = NULL;

	switch(shooter->mTower->mProjectileType)
	{
	case PT_Arrow:
		mKindOfProjectile = new ArrowInstance(shooter, target);
		break;
	case PT_Ice:
		mKindOfProjectile = new IceInstance(shooter, target);
		break;
	case PT_Lightning:
		mKindOfProjectile = new LightningInstance(shooter, target);
		break;
	case PT_Fire:
		mKindOfProjectile = new FireInstance(shooter, target);
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
	int towerDrawWidth = shooter->mTower->mTowerImg->sizeX;
	int towerDrawHeight = shooter->mTower->mTowerImg->sizeY;
	if (shooter->mTower->mTowerFrameCount > 1)
	{
		towerDrawWidth = shooter->mTower->mTowerFrameWidth;
		towerDrawHeight = shooter->mTower->mTowerFrameHeight;
	}
	mProjectilePosition.X = shooter->mTowerPosition.X + towerDrawWidth / 2.0f;
	mProjectilePosition.Y = shooter->mTowerPosition.Y + towerDrawHeight / 2.0f;
	mProjectileImg = shooter->mTower->mProjectileImg;
	mFireSound = shooter->mTower->mFireSound;
	mHitSound = shooter->mTower->mHitSound;
	mTarget = target;
	mHitSize = target->mEnemy->mSize;
	mHitsFlyer = shooter->mTower->mHitsFlyer;
	mHitsLand = shooter->mTower->mHitsLand;
	mSlowAmount = shooter->mTower->mTowerVector[shooter->mTowerLevel].mSlowAmount;
	mSlowLength = shooter->mTower->mTowerVector[shooter->mTowerLevel].mSlowLength;
	mTowerDamage = shooter->mTower->mTowerVector[shooter->mTowerLevel].mDamage;
	mFrameCount = shooter->mTower->mProjectileFrameCount;
	mFrameTime = shooter->mTower->mProjectileFrameTime;
	mFrameWidth = shooter->mTower->mProjectileFrameWidth;
	mFrameHeight = shooter->mTower->mProjectileFrameHeight;
	mAnimationTime = 0;
	mCurrentFrame = 0;
	mSplashRangeSqrd = shooter->mTower->mTowerVector[shooter->mTowerLevel].mSplashRange;
	mSplashRangeSqrd *= mSplashRangeSqrd;

	mTarget->AddReference();
}

ProjectileInstance::~ProjectileInstance()
{
	mTarget->RemoveReference();
}

void ProjectileInstance::AdvanceAnimation(u32 timePassed)
{
	if (mFrameCount <= 1 || mFrameTime <= 0)
		return;

	mAnimationTime += timePassed;
	while (mAnimationTime >= mFrameTime)
	{
		mAnimationTime -= mFrameTime;
		mCurrentFrame++;
		mCurrentFrame %= mFrameCount;
	}
}

bool ProjectileInstance::DisappearProjectile()
{
	return mDisappearProjectile;
}

void ProjectileInstance::DealDamage()
{
	mProjectilePosition = mTarget->mEnemyPosition;
	mTarget->EnemyReciveDamage(mTowerDamage, mSlowAmount, mSlowLength);

	//If this isn't a splash projectile, just hit the target.
	if (mSplashRangeSqrd == 0)
		return;
	
	//Otherwise, this is a splash projectile. Loop through all enemies checking range.
	list<EnemyInstance*>::iterator end_iter = GameScreen::gGameReference->mRealEnemies.end();

	list<EnemyInstance*>::iterator ei_iter;
	for (ei_iter =  GameScreen::gGameReference->mRealEnemies.begin(); ei_iter != end_iter; ei_iter++)
	{
		//Have already damaged the target, don't need to shoot it again :)
		if (*ei_iter == mTarget)
		{
			continue;
		}
		//We hit it && is not dead && in splash range
		if (((mHitsFlyer && (*ei_iter)->EnemyCanFly()) || (mHitsLand && !(*ei_iter)->EnemyCanFly())) &&	
			!(*ei_iter)->EnemyIsDead() && mProjectilePosition.SquareDistance((*ei_iter)->mEnemyPosition) <= mSplashRangeSqrd)
		{
			(*ei_iter)->EnemyReciveDamage(mTowerDamage, mSlowAmount, mSlowLength);
		}
	}
}

//ArrowInstance
ArrowInstance::ArrowInstance(TowerInstance *shooter, EnemyInstance *target)	: ProjectileInstance(shooter, target)
{
	mMovementSpeed = shooter->mTower->mTowerVector[shooter->mTowerLevel].mSpeed;
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);

	if (mFireSound != NULL)
		oslPlaySound(mFireSound, CHANNEL_1);
	
}

ArrowInstance::~ArrowInstance()
{
}

void ArrowInstance::Update(u32 timePassed)
{
	AdvanceAnimation(timePassed);

	//Calculate angle to target, move towards it
	float movement = mHitSize + (mMovementSpeed * timePassed / 1000.0f); //Distance to move this tick
	movement *= movement;
	float xdif = mProjectilePosition.X - mTarget->mEnemyPosition.X;
	float ydif = mProjectilePosition.Y - mTarget->mEnemyPosition.Y;
	float distance = (xdif * xdif) + (ydif * ydif); //Pythagoras without the sqrt
	if (distance < movement)
	{
		//We hit!
		DealDamage();
		if (mHitSound != NULL)
			oslPlaySound(mHitSound, CHANNEL_2);
		
		mDisappearProjectile = true;
		return;
	}

	//Calculate new position
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);
	float changeX = mMovementSpeed * cos(mAngle) * timePassed / 1000;
	float changeY = mMovementSpeed * sin(mAngle) * timePassed / 1000;
	mProjectilePosition.X += changeX;
	mProjectilePosition.Y += changeY;
}

void ArrowInstance::Render(float scrollOffset)
{
	ProjectileRenderer::RenderArrow(this, mAngle, scrollOffset);
}

//IceInstance
IceInstance::IceInstance(TowerInstance *shooter, EnemyInstance *target)	: ProjectileInstance(shooter, target)
{
	mMovementSpeed = shooter->mTower->mTowerVector[shooter->mTowerLevel].mSpeed;
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);

	if (mFireSound != NULL)
		oslPlaySound(mFireSound, CHANNEL_3);
	
}

IceInstance::~IceInstance()
{
}

void IceInstance::Update(u32 timePassed)
{
	AdvanceAnimation(timePassed);

	//Calculate angle to target, move towards it
	float movement = mHitSize + (mMovementSpeed * timePassed / 1000.0f); //Distance to move this tick
	movement *= movement;
	float xdif = mProjectilePosition.X - mTarget->mEnemyPosition.X;
	float ydif = mProjectilePosition.Y - mTarget->mEnemyPosition.Y;
	float distance = (xdif * xdif) + (ydif * ydif); //Pythagoras without the sqrt
	if (distance < movement)
	{
		//We hit!
		DealDamage();
		if (mHitSound != NULL)
			oslPlaySound(mHitSound, CHANNEL_4);
		
		mDisappearProjectile = true;
		return;
	}

	//Calculate new position
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);
	float changeX = mMovementSpeed * cos(mAngle) * timePassed / 1000;
	float changeY = mMovementSpeed * sin(mAngle) * timePassed / 1000;
	mProjectilePosition.X += changeX;
	mProjectilePosition.Y += changeY;
}

void IceInstance::Render(float scrollOffset)
{
	ProjectileRenderer::RenderIce(this, mAngle, scrollOffset);
}

//LightningInstance
LightningInstance::LightningInstance(TowerInstance *shooter, EnemyInstance *target)	: ProjectileInstance(shooter, target)
{
	mLifetime = 0;
	DealDamage();
	if (mHitSound != NULL)
		oslPlaySound(mHitSound, CHANNEL_5);
}

LightningInstance::~LightningInstance()
{
}

void LightningInstance::Update(u32 timePassed)
{
	AdvanceAnimation(timePassed);

	mLifetime += timePassed;
	if(mLifetime > 400)
	{
		mDisappearProjectile = true;
	}
}

void LightningInstance::Render(float scrollOffset)
{
	ProjectileRenderer::RenderLightning(this, mTarget->mEnemyPosition, scrollOffset);
}

//FireInstance
FireInstance::FireInstance(TowerInstance *shooter, EnemyInstance *target)	: ProjectileInstance(shooter, target)
{
	mMovementSpeed = shooter->mTower->mTowerVector[shooter->mTowerLevel].mSpeed;
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);

	if (mFireSound != NULL)
		oslPlaySound(mFireSound, CHANNEL_6);
}

FireInstance::~FireInstance()
{
}

void FireInstance::Update(u32 timePassed)
{
	AdvanceAnimation(timePassed);

	//Calculate angle to target, move towards it
	float movement = mHitSize + (mMovementSpeed * timePassed / 1000.0f); //Distance to move this tick
	movement *= movement;
	float xdif = mProjectilePosition.X - mTarget->mEnemyPosition.X;
	float ydif = mProjectilePosition.Y - mTarget->mEnemyPosition.Y;
	float distance = (xdif * xdif) + (ydif * ydif); //Pythagoras without the sqrt
	if (distance < movement)
	{
		//We hit!
		DealDamage();
		if (mHitSound != NULL)
			oslPlaySound(mHitSound, CHANNEL_7);
		
		mDisappearProjectile = true;
		return;
	}

	//Calculate new position
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);
	float changeX = mMovementSpeed * cos(mAngle) * timePassed / 1000;
	float changeY = mMovementSpeed * sin(mAngle) * timePassed / 1000;
	mProjectilePosition.X += changeX;
	mProjectilePosition.Y += changeY;
}

void FireInstance::Render(float scrollOffset)
{
	ProjectileRenderer::RenderFire(this, mAngle, scrollOffset);
}
