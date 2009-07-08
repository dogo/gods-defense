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
	mHasImunity = true;
	mCanFly = true;
}


EnemyInfo::EnemyInfo(TiXmlElement* infoNode)
{
	//Default Initializers
	mHealth = 0;
	mGoldValue = 0;
	mPointValue = 0;
	mSpeed = 0;
	mHasImunity = true;
	mCanFly = true;

	int temp;

	infoNode->QueryIntAttribute("Health", &temp);
	mHealth = temp;

	infoNode->QueryIntAttribute("GoldValue", &temp);
	mGoldValue = temp;

	infoNode->QueryIntAttribute("PointValue", &temp);
	mPointValue = temp;

	infoNode->QueryIntAttribute("Speed", &temp);
	mSpeed = temp;

	const char* HasImunity = infoNode->Attribute("HasImunity");
	if (HasImunity != NULL && !strcmp(HasImunity,"False")) //strcmp() return 0 if both string be the same.
	{
		mHasImunity = false;
	}
	const char* CanFly = infoNode->Attribute("CanFly");
	if (CanFly != NULL && !strcmp(CanFly,"False")) //strcmp() return 0 if both string be the same.
	{
		mCanFly = false;
	}
}