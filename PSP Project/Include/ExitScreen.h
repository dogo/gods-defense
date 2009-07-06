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

public:
	ExitScreen();

	virtual void draw();

	virtual void update();
};
#endif