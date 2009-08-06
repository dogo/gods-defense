//**************************************************************************
//		PSP Project: 'Gods Defense' - MainMenuScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef MAINMENUSCREEN_H_INCLUDED
#define MAINMENUSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class MainMenuScreen : public IScreen
{
private:
	OSL_IMAGE *menubg;
public:
	MainMenuScreen();

	virtual ~MainMenuScreen();

	virtual void draw();

	virtual void update();

};
#endif
