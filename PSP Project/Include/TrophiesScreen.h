//**************************************************************************
//		PSP Project: 'Gods Defense' - TrophiesScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef TROPHIESSCREEN_H_INCLUDED
#define TROPHIESSCREEN_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/util/MemoryStick.h"

class TrophiesScreen : public IScreen
{
private:
	OSL_IMAGE *back;

public:
	TrophiesScreen();

	~TrophiesScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

};
#endif