//**************************************************************************
//		PSP Project: 'Gods Defense' - AnykeyScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef ANYKEYSCREEN_H_INCLUDED
#define ANYKEYSCREEN_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/GodLibrary.h"

class AnykeyScreen : public IScreen
{
private:
	GodLibrary *mySplash;
	OSL_IMAGE *AnykeySplash;
	int	mWait;

public:
	AnykeyScreen();

	virtual ~AnykeyScreen();

	virtual void draw();

	virtual void update(u32 timePassed);
};
#endif