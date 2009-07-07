//**************************************************************************
//		PSP Project: 'Gods Defense' - GodLibrary.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GODLIBRARY_H_INCLUDED
#define GODLIBRARY_H_INCLUDED

#include "../Include/ILib.h"
#include <math.h>

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


/** Draws an formatted pixel at the specified x and y positions.

\code
drawPixel(float x, float y, osl_color color);
\endcode */
void static drawPixel(float x, float y, OSL_COLOR color);

/** Draws an circle pixel at the specified x and y positions.

\code
drawCircle(int x, int y, int radius, osl_color);
\endcode */
void static drawCircle(int x, int y, int radius, OSL_COLOR color);

};

//coordinates in pixels
class Point2D
{
public:
	Point2D(); //x=0,y=0 
	Point2D(float x, float y);
	float const AimTo(const Point2D &enemy);
	float const SquareDistance(const Point2D &enemy);
	
	float X;
	float Y;
};
#endif