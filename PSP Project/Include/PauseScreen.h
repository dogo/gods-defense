//**************************************************************************
//		PSP Project: 'Gods Defense' - PauseScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef PAUSESCREEN_H_INCLUDED
#define PAUSESCREEN_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/GameScreen.h"

class PauseScreen
{
private:

public:
	PauseScreen();
	~PauseScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

};
#endif
