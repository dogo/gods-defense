//**************************************************************************
//		PSP Project: 'Gods Defense' - GodLibrary.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GODLIBRARY_H_INCLUDED
#define GODLIBRARY_H_INCLUDED

#include "../Include/ILib.h"

class GodLibrary
{
private:
	OSL_IMAGE *Splash;

public:

/** Suspends the current thread for a specified time.

\code
Wait(unsigned long iTime);
\endcode */
void Wait(unsigned long iTime);

/** Draws a formatted string literal at the specified x and y positions.

\code
oslDrawStringf(0, 0, "Test string %i", 1);
\endcode */
#define oslDrawStringf(x, y, ...)               { char __str[1000]; sprintf(__str , __VA_ARGS__); oslDrawString(x, y, __str); }


/** Draw splash with fade in and fade out.
	Fade States
	0 - FadeIN
	1 - Wait
	2 - FadeOut

\code
drawSplash(unsigned long iTime, OSL_IMAGE *Splash);
\endcode */
void drawSplash(int iTime, OSL_IMAGE *Splash);
};

//coordinates in pixels
class Point2D
{
public:
	Point2D(); //x=0,y=0 
	Point2D(float x, float y);
	
	float X;
	float Y;
};
#endif