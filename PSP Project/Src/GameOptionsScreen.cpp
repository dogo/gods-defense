//**************************************************************************
//		PSP Project: 'Gods Defense' - GameOptionsScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameOptionsScreen.h"
#include "../Include/ScreenManager.h"

string gChoosedMap;

GameOptionsScreen::GameOptionsScreen()
{
	gChoosedMap = "NULL";
	mSelectedMap = 0;
	int dfd = sceIoDopen("/Res/maps");

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
}

void GameOptionsScreen::draw()
{
	oslIntraFontSetStyle(gFont, 2.0f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER); //Tells the PSP what size and shape the text is
	oslDrawString(240,40,Resource::STR_MAPSELECTION_CAPTION);
	oslDrawString(335,183,"X");

	oslIntraFontSetStyle(gFont, 1.5f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_CENTER);
	oslDrawString(240,160,mMap[mSelectedMap].c_str());
	oslDrawString(240- oslGetStringWidth(mMap[mSelectedMap].c_str()),160,"<-");
	oslDrawString(240+ oslGetStringWidth(mMap[mSelectedMap].c_str()),160,"->");
}

void GameOptionsScreen::update()
{
	if(osl_keys->pressed.cross)
	{		
		ChooseMap();
		mNextScreen = ScreenManager::SCREEN_GAME; //Start game!
		oslStopSound(menuTheme);
	}
	if(osl_keys->pressed.circle)
	{
		mNextScreen = ScreenManager::SCREEN_MAIN_MENU; //go back CLR
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
