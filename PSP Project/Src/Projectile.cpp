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
	mProjectilePosition = shooter->mTowerPosition;
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
	mSplashRangeSqrd = shooter->mTower->mTowerVector[shooter->mTowerLevel].mSplashRange;
	mSplashRangeSqrd *= mSplashRangeSqrd;

	mTarget->AddReference();
}

ProjectileInstance::~ProjectileInstance()
{
	mTarget->RemoveReference();
}

bool ProjectileInstance::DisappearProjectile()
{
	return mDisappearProjectile;
}

void ProjectileInstance::DealDamage()
{
	mProjectilePosition = mTarget->mEnemyPosition;
	mTarget->EnemyReciveDamage(mTowerDamage, mSlowAmount, mSlowLength);

	//If we aren't splash, just hit the target.
	if (mSplashRangeSqrd == 0)
		return;
	
	//Else, we are splash. loop all enemies checking range.
	list<EnemyInstance*>::iterator end_iter = GameScreen::gGameReference->mRealEnemies.end();

	list<EnemyInstance*>::iterator ei_iter;
	for (ei_iter =  GameScreen::gGameReference->mRealEnemies.begin(); ei_iter != end_iter; ei_iter++)
	{
		//Have already damaged the target, don't need to shoot it again :)
		if (*ei_iter == mTarget)
		{
			continue;
		}
		//We hit it && Isn't dead && In splash range
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
			oslPlaySound(mHitSound, CHANNEL_2);
		
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
	mProjectileImg->angle = (mAngle * 180/M_PI);
	oslDrawImageXY(mProjectileImg, mProjectilePosition.X, GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount+mProjectilePosition.Y);
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
			oslPlaySound(mHitSound, CHANNEL_4);
		
		mDisappearProjectile = true;
	}

	//Calculate new position
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);
	float changeX = mMovementSpeed * cos(mAngle) * timePassed / 1000;
	float changeY = mMovementSpeed * sin(mAngle) * timePassed / 1000;
	mProjectilePosition.X += changeX;
	mProjectilePosition.Y += changeY;
}

void IceInstance::ProjectileRender()
{
	mProjectileImg->angle = (mAngle * 180/M_PI);
	oslDrawImageXY(mProjectileImg, mProjectilePosition.X, GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount+mProjectilePosition.Y);
}

//LightningInstance
LightningInstance::LightningInstance(TowerInstance *shooter, EnemyInstance *target)	: ProjectileInstance(shooter, target)
{
	mAnimationTime = 0;
	DealDamage();
	if (mHitSound != NULL)
		oslPlaySound(mHitSound, CHANNEL_5);
}

LightningInstance::~LightningInstance()
{
}

void LightningInstance::Update(u32 timePassed)
{
	mAnimationTime += timePassed;
	if(mAnimationTime > 400)
	{
		mDisappearProjectile = true;
	}
}

void LightningInstance::ProjectileRender()
{
	mProjectileImg->centerX = mProjectileImg->sizeX/2;
	mProjectileImg->centerY = mProjectileImg->sizeY/2;
	oslDrawImageXY(mProjectileImg, mTarget->mEnemyPosition.X, GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount+mTarget->mEnemyPosition.Y);
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
			oslPlaySound(mHitSound, CHANNEL_7);
		
		mDisappearProjectile = true;
	}

	//Calculate new position
	mAngle = mProjectilePosition.AimTo(mTarget->mEnemyPosition);
	float changeX = mMovementSpeed * cos(mAngle) * timePassed / 1000;
	float changeY = mMovementSpeed * sin(mAngle) * timePassed / 1000;
	mProjectilePosition.X += changeX;
	mProjectilePosition.Y += changeY;
}

void FireInstance::ProjectileRender()
{
	mProjectileImg->angle = (mAngle * 180/M_PI);
	oslDrawImageXY(mProjectileImg, mProjectilePosition.X, GameGUI::Instance()->mGame->GetGameMap()->mScrollAmount+mProjectilePosition.Y);
}