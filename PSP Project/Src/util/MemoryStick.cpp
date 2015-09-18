//**************************************************************************
//		PSP Project: 'Gods Defense' - MemoryStick.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/MemoryStick.h"

// End list with ""
char nameList[][20] = { "0000", "0001", "0002", "0003", "0004", ""};

MemoryStick::MemoryStick()
{
	gameTitle = (char *)"Gods Defense";
	gameID = (char *)"GOD01";
	saveName = (char *)"0000";
	sprintf(message, "%s", "");
	sprintf(loadedData, "%s", "");	
}

MemoryStick::~MemoryStick()
{
}

void MemoryStick::Save(char *aData)
{
	printf("Saving... %s",aData);
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

void MemoryStick::Load()
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

bool MemoryStick::Status(int type)
{
	if (type != OSL_DIALOG_NONE)
	{
		oslDrawSaveLoad();
		if (oslSaveLoadGetResult() == OSL_SAVELOAD_CANCEL)
			sprintf(message, "Cancel");
		else if (type == OSL_DIALOG_LOAD)
			sprintf(message, "Loaded data: %s", (char *)MemoryStickData.data);
		else if (type == OSL_DIALOG_SAVE)
			sprintf(message, "Saved data: %s", (char *)MemoryStickData.data);
		oslEndSaveLoadDialog();
		return true;
	}
	return false;
}