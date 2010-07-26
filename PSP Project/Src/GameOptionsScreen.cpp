//**************************************************************************
//		PSP Project: 'Gods Defense' - GameOptionsScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameOptionsScreen.h"
#include "../Include/ScreenManager.h"

string gChoosedMap;

GameOptionsScreen::GameOptionsScreen()
{
	imgBack = oslLoadImageFilePNG(Resource::IMG_BACK, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	imgSelect = oslLoadImageFilePNG(Resource::IMG_CROSS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	imgLetArrow = oslLoadImageFilePNG(Resource::IMG_LEFTARROW, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	imgRightArrow = oslLoadImageFilePNG(Resource::IMG_RIGHTARROW, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	gChoosedMap = "NULL";
	mSelectedMap = 0;
	int dfd = sceIoDopen("/Res/maps");
	char buffer[255];
	mMiniMap = NULL;

	//get all the folders name in map directory to fill mMap vector 
	if(dfd > 0)
	{
		struct SceIoDirent dir;
		memset(&dir,0,sizeof(SceIoDirent));

		while(sceIoDread(dfd, &dir) > 0)
		{
			if(dir.d_stat.st_attr & FIO_SO_IFDIR)
			{
				if(dir.d_name[0] != '.')
				{
					mMap.push_back(dir.d_name); //Add folder name to mMap vector
					sprintf(buffer,"/Res/maps/%s/%s.png",dir.d_name,dir.d_name);
					mMiniMap = oslScaleImageCreate(oslLoadImageFilePNG(buffer, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888), OSL_IN_RAM | OSL_SWIZZLED, 100, 100, OSL_PF_8888);
					mMapImages.push_back(mMiniMap);
				}
			}
			else
			{
				oslFatalError("Error reading maps folder!");
			}
		}
		sceIoDclose(dfd);
	}
}


GameOptionsScreen::~GameOptionsScreen()
{
	oslDeleteImage(imgBack);
	oslDeleteImage(imgSelect);
	oslDeleteImage(mMiniMap);
	oslDeleteImage(imgLetArrow);
	oslDeleteImage(imgRightArrow);
	mMapImages.clear();
}

void GameOptionsScreen::draw()
{
	oslIntraFontSetStyle(gFont, 1.2f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,40,Resource::STR_MAPSELECTION_CAPTION);

	oslIntraFontSetStyle(gFont, 0.6f,RGBA(175,137,62,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	
	oslDrawImageXY(mMapImages[mSelectedMap],(480/2 - mMapImages[mSelectedMap]->sizeX/2),(272/2 - mMapImages[mSelectedMap]->sizeY/2));

	oslDrawString(240,210,mMap[mSelectedMap].c_str());
	oslDrawImageXY(imgRightArrow,(233 + mMapImages[mSelectedMap]->sizeX),(272/2 -imgRightArrow->stretchY/2));
	oslDrawImageXY(imgLetArrow,(210 - mMapImages[mSelectedMap]->sizeX),(272/2 -imgLetArrow->stretchY/2));

	oslDrawImageXY(imgBack, (430) - (imgBack->stretchX), (272) - (imgBack->stretchY));
	oslDrawString((510) - imgBack->stretchX,(272) - (imgBack->stretchY/2),Resource::STR_BACK_SK);

	oslDrawImageXY(imgSelect, 10, (272) - (imgSelect->stretchY));
	oslDrawString(28 + imgSelect->stretchX, (272) - (imgSelect->stretchY/2),Resource::STR_SELECT);
}

void GameOptionsScreen::update(u32 /*timePassed*/) //Parametro Formal, não dá warning
{
	if(osl_keys->pressed.cross)
	{		
		ChooseMap();
		mNextScreen = ScreenManager::SCREEN_GAME; //Start game!
		oslStopSound(menuTheme);
	}
	if(osl_keys->pressed.circle)
	{
		if(!gIsServer && !gIsClient)
			mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
		else if (gIsServer || gIsClient)
			mNextScreen = ScreenManager::SCREEN_MULTIPLAYER; //go back CLR
	}
	if(osl_keys->pressed.right)
	{
		mSelectedMap = (mSelectedMap-1+mMap.size())%mMap.size();
	}
	if(osl_keys->pressed.left)
	{
		mSelectedMap = (mSelectedMap+1)%mMap.size();
	}
}

void GameOptionsScreen::ChooseMap()
{
	gChoosedMap = mMap[mSelectedMap];
}
