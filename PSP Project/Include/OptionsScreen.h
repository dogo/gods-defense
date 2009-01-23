//**************************************************************************
//		PSP Project: 'Gods Defense' - OptionsScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef OPTIONSSCREEN_H_INCLUDED
#define OPTIONSSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class OptionsScreen : public IScreen
{
private:
	OSL_IMAGE *back;
	OSL_IMAGE *select;

public:
	OptionsScreen();

	~OptionsScreen();

	virtual void draw();

	virtual void update();
};
#endif
