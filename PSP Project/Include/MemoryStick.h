//**************************************************************************
//		PSP Project: 'Gods Defense' - MemoryStick.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef MEMORYSTICK_H_INCLUDED
#define MEMORYSTICK_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/icon.h"

class MemoryStick
{
public:
	/**
	*	Data for save and load:
	*/
	char *gameTitle;
	char *gameID;
	char *saveName;

	struct oslSaveLoad MemoryStickData;

    char message[100];
    char loadedData[100];

	MemoryStick();

	~MemoryStick();

	void Save(int type, char *aData);

	void Load(int type);

	bool Status(int type);
};

#endif