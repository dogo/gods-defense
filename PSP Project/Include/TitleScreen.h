//**************************************************************************
//		PSP Project: 'Gods Defense' - TitleScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef TITLESCREEN_H_INCLUDED
#define TITLESCREEN_H_INCLUDED

#include "../Include/ILib.h"

class TitleScreen : public IScreen
{
private:
	OSL_IMAGE *GDSplash;

public:
	TitleScreen();

	virtual ~TitleScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

};
#endif
