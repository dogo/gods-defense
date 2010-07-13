//**************************************************************************
//		PSP Project: 'Gods Defense' - MemoryStick.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/MemoryStick.h"

// End list with ""
char nameList[][20] = { "0000", "0001", "0002", "0003", "0004", ""};

MemoryStick::MemoryStick()
{
	gameTitle = "Gods Defense";
	gameID = "GOD01";
	saveName = "0000";
	sprintf(message, "");
	sprintf(loadedData, "");	
}

MemoryStick::~MemoryStick()
{
}

void MemoryStick::Save(int type, char *aData)
{
	if (type == OSL_DIALOG_NONE)
	{
		memset(&MemoryStickData, 0, sizeof(MemoryStickData));
		strcpy(MemoryStickData.gameTitle, gameTitle);
		strcpy(MemoryStickData.gameID, gameID);
		strcpy(MemoryStickData.saveName, saveName);
		MemoryStickData.nameList = nameList;
		MemoryStickData.icon0 = icon0;
		MemoryStickData.size_icon0 = size_icon0;
		MemoryStickData.data = aData;
		MemoryStickData.dataSize = 100;
		oslInitAutoSaveDialog(&MemoryStickData);
		memset(message, 0, sizeof(message));
	}
}

void MemoryStick::Load(int type)
{
	if (type == OSL_DIALOG_NONE)
	{
		memset(&MemoryStickData, 0, sizeof(MemoryStickData));
		strcpy(MemoryStickData.gameID, gameID);
		strcpy(MemoryStickData.saveName, saveName);
		MemoryStickData.nameList = nameList;
		MemoryStickData.data = &loadedData;
		MemoryStickData.dataSize = 100;
		oslInitAutoLoadDialog(&MemoryStickData);
		memset(message, 0, sizeof(message));
	}
}

bool MemoryStick::Status(int type)
{
    if (type != OSL_DIALOG_NONE)
	{
        oslDrawSaveLoad();
        if (oslGetLoadSaveStatus() == PSP_UTILITY_DIALOG_NONE)
		{
            if (oslSaveLoadGetResult() == OSL_SAVELOAD_CANCEL)
				return false;
            else if ((type == OSL_DIALOG_LOAD) || (type == OSL_DIALOG_SAVE))
			{
				sprintf(message, "Data: %s", (char *)MemoryStickData.data);
				printf("message %s\n",message);
				oslEndSaveLoadDialog();
				return true;
			}
            oslEndSaveLoadDialog();
        }
	}
	return false;
}
          