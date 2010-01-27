//**************************************************************************
//		PSP Project: 'Gods Defense' - MultiplayerScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef MULTIPLAYERSCREEN_H_INCLUDED
#define MULTIPLAYERSCREEN_H_INCLUDED

#include "../Include/ILib.h"

class MultiplayerScreen : public IScreen
{
private:
	OSL_IMAGE *imgBack;
	OSL_IMAGE *imgServer;
	OSL_IMAGE *imgClient;

public:
	MultiplayerScreen();
	~MultiplayerScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

};
#endif
