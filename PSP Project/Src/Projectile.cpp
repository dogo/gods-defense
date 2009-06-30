//**************************************************************************
//		PSP Project: 'Gods Defense' - Projectile.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Projectile.h"

OSL_IMAGE *ProjectileInstance::LoadProjectileImage(const char &projectileType)
{
	switch(projectileType)
	{
	case PT_Arrow:
		return m_ProjectileSprite = oslLoadImageFilePNG("/Res/ST_Arrow.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	
	case PT_Ice:
		return m_ProjectileSprite = oslLoadImageFilePNG("/Res/ST_Ice.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	/*case :
		return nm_ProjectileSprite = oslLoadImageFilePNG("/Res/circle.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	*/
	default:
		return NULL;
	}
}