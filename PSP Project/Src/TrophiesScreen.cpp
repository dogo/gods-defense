//**************************************************************************
//		PSP Project: 'Gods Defense' - TrophiesScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/TrophiesScreen.h"
#include "../Include/ScreenManager.h"


TrophiesScreen::TrophiesScreen()
{
	back = oslLoadImageFilePNG(Resource::IMG_BACK, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	mSelectedTrophy = 0;
	TrophyManager::Init();
}

TrophiesScreen::~TrophiesScreen()
{
	oslDeleteImage(back);
}

void TrophiesScreen::draw()
{
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,20,Resource::STR_TROPHIES_CAPTION);

	oslIntraFontSetStyle(gFont, 0.65f,RGBA(210,210,210,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawStringf(240,45,"%d/%d unlocked", TrophyManager::GetUnlockedCount(), TrophyManager::GetTrophyCount());

	int firstVisibleTrophy = mSelectedTrophy - 2;
	if (firstVisibleTrophy < 0)
		firstVisibleTrophy = 0;
	if (firstVisibleTrophy > TrophyManager::GetTrophyCount() - 5)
		firstVisibleTrophy = TrophyManager::GetTrophyCount() - 5;
	if (firstVisibleTrophy < 0)
		firstVisibleTrophy = 0;

	for (int i = 0; i < 5 && firstVisibleTrophy + i < TrophyManager::GetTrophyCount(); i++)
	{
		DrawTrophyRow(firstVisibleTrophy + i, 70 + (i * 34));
	}

	oslDrawImageXY(back, (430) - (back->stretchX), (272) - (back->stretchY));
	oslIntraFontSetStyle(gFont, 0.7f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString((510) - back->stretchX,(272) - (back->stretchY/2),Resource::STR_BACK_SK);
}

void TrophiesScreen::DrawTrophyRow(const int &index, const int &yPosition)
{
	const TrophyInfo *trophyInfo = TrophyManager::GetTrophyInfo(index);
	if (trophyInfo == NULL)
		return;

	bool unlocked = TrophyManager::IsUnlocked(trophyInfo->id);
	int titleColor = unlocked ? RGBA(255,255,255,255) : RGBA(115,115,115,255);
	int descColor = unlocked ? RGBA(175,137,62,255) : RGBA(80,80,80,255);

	if (mSelectedTrophy == index)
	{
		oslDrawFillRect(35, yPosition - 4, 445, yPosition + 27, RGBA(40,40,40,180));
	}

	oslIntraFontSetStyle(gFont, 0.65f, titleColor, RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(48, yPosition, "%s %s", unlocked ? "[x]" : "[ ]", trophyInfo->name);

	oslIntraFontSetStyle(gFont, 0.48f, descColor, RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_LEFT);
	if (unlocked)
	{
		oslDrawString(70, yPosition + 15, trophyInfo->description);
	}
	else
	{
		int progress = TrophyManager::GetProgressValue(trophyInfo->id);
		int target = TrophyManager::GetProgressTarget(trophyInfo->id);
		if (progress > target)
			progress = target;
		oslDrawStringf(70, yPosition + 15, "Locked - %d/%d", progress, target);
	}
}

void TrophiesScreen::update(u32 /*timePassed*/)
{
	if(osl_keys->pressed.up)
	{
		mSelectedTrophy--;
		if (mSelectedTrophy < 0)
			mSelectedTrophy = TrophyManager::GetTrophyCount() - 1;
	}

	if(osl_keys->pressed.down)
	{
		mSelectedTrophy++;
		mSelectedTrophy %= TrophyManager::GetTrophyCount();
	}

	if(osl_keys->pressed.circle)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
	}
}
