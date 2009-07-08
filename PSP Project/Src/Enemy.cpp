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
	mHasImunity = true;

	int temp;

	infoNode->QueryIntAttribute("Health", &temp);
	mHealth = temp;

	infoNode->QueryIntAttribute("GoldAmouth", &temp);
	mGoldValue = temp;

	infoNode->QueryIntAttribute("PointValue", &temp);
	mPointValue = temp;

	infoNode->QueryIntAttribute("Speed", &temp);
	mSpeed = temp;

	const char* mCanSlow = infoNode->Attribute("HasImunity");
	if (mCanSlow != NULL && !strcmp(mHasImunity,"False")) //strcmp() return 0 if both string be the same.
	{
		mHasImunity = false;
	}
}