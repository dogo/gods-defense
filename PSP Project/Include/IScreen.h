//**************************************************************************
//		PSP Project: 'Gods Defense' - IScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************


#ifndef ISCREEN_H_INCLUDED
#define ISCREEN_H_INCLUDED

class IScreen
{
public:
	virtual ~IScreen() {};

	virtual void draw() = 0;

	virtual void update(u32 timePassed) = 0;
};
#endif
