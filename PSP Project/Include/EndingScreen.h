//**************************************************************************
//		PSP Project: 'Gods Defense' - EndingScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef ENDINGSCREN_H_INCLUDED
#define ENDINGSCREN_H_INCLUDED

#include "../Include/ILib.h"

class EndingScreen : public IScreen
{
private:
	OSL_IMAGE *mCross;

public:
	EndingScreen();

	~EndingScreen();

	virtual void draw();

	virtual void update(u64 timePassed);

};
#endif