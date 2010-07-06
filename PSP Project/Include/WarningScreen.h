//**************************************************************************
//		PSP Project: 'Gods Defense' - WarningScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef WARNINGSCREEN_H_INCLUDED
#define WARNINGSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class WarningScreen : public IScreen
{
private:
	OSL_IMAGE *mBack;
	OSL_IMAGE *mCover;

public:
	WarningScreen();

	~WarningScreen();

	virtual void draw();

	virtual void update(u32 timePassed);
};
#endif
