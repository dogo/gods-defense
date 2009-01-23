//**************************************************************************
//		PSP Project: 'Gods Defense' - AnykeyScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef ANYKEYSCREEN_H_INCLUDED
#define ANYKEYSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class AnykeyScreen : public IScreen
{
private:
	OSL_IMAGE *Splash;

public:
	AnykeyScreen();

	virtual ~AnykeyScreen();

	virtual void draw();

	virtual void update();

};
#endif