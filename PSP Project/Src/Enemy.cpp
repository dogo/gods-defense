//**************************************************************************
//		PSP Project: 'Gods Defense' - Enemy.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Enemy.h"

EnemyInfo::EnemyInfo()
{
	//Default Initializers
	mHealth = 0;
	mGoldValue = 0;
	mPointValue = 0;
	mSpeed = 0;
	mCanSlow = true;
}

EnemyInfo::EnemyInfo(TiXmlElement* infoNode)
{
	//Default Initializers
	mHealth = 0;
	mGoldValue = 0;
	mPointValue = 0;
	mSpeed = 0;
	mCanSlow = true;

	int temp;

	infoNode->QueryIntAttribute("Health", &temp);
	mHealth = temp;

	infoNode->QueryIntAttribute("GoldValue", &temp);
	mGoldValue = temp;

	infoNode->QueryIntAttribute("PointValue", &temp);
	mPointValue = temp;

	infoNode->QueryIntAttribute("Speed", &temp);
	mSpeed = temp;

	const char* mCanSlow = infoNode->Attribute("CanSlow");
	if (mCanSlow != NULL && !strcmp(mCanSlow,"False")) //strcmp() return 0 if both string be the same.
	{
		mCanSlow = false;
	}
}