//**************************************************************************
//		PSP Project: 'Gods Defense' - ExitScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef EXITSCREEN_H_INCLUDED
#define EXITSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class ExitScreen : public IScreen
{
private:
	OSL_IMAGE *mCover;

public:
	ExitScreen();
	~ExitScreen();

	virtual void draw();

	virtual void update(u32 timePassed);
};
#endif