//**************************************************************************
//		PSP Project: 'Gods Defense' - MemoryWarningScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef MEMORYWARNINGSCREEN_H_INCLUDED
#define MEMORYWARNINGSCREEN_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/util/MemoryStick.h"

class MemoryWarningScreen : public IScreen
{
private:
	OSL_IMAGE *mCross;
	OSL_IMAGE *mCover;
	MemoryStick *mMemoryStick;
	int mType;

public:
	MemoryWarningScreen();

	~MemoryWarningScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

};
#endif
