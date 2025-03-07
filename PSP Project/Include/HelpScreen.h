//**************************************************************************
//		PSP Project: 'Gods Defense' - HelpScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef HELPSCREEN_H_INCLUDED
#define HELPSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class HelpScreen : public IScreen
{
private:
	OSL_IMAGE *mBack;
	OSL_IMAGE *mCover;

public:
	HelpScreen();

	~HelpScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

};
#endif
