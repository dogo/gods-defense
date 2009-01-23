//**************************************************************************
//		PSP Project: 'Gods Defense' - GameOptionsScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GAMEOPTIONSSCREEN_H_INCLUDED
#define GAMEOPTIONSSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class GameOptionsScreen : public IScreen
{
private:

public:
	GameOptionsScreen();

	virtual void draw();

	virtual void update();

};
#endif
