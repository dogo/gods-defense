//**************************************************************************
//		PSP Project: 'Gods Defense' - GameScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

#include "../Include/ILib.h"

class GameScreen : public IScreen
{
private:

public:
	GameScreen();

	virtual void draw();

	virtual void update();

};
#endif
