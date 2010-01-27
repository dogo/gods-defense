//**************************************************************************
//		PSP Project: 'Gods Defense' - AboutScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef ABOUTSCREEN_H_INCLUDED
#define ABOUTSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class AboutScreen : public IScreen
{
private:
	OSL_IMAGE *back;

public:
	AboutScreen();

	~AboutScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

};
#endif
