//**************************************************************************
//		PSP Project: 'Gods Defense' - GodLibrary.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GODLIBRARY_H_INCLUDED
#define GODLIBRARY_H_INCLUDED

#include "../Include/ILib.h"
#include <math.h>

/** Draws a specific frame of an image at a specified location (like a real sprite)

\code
DrawImageFrameXY(OSL_IMAGE *img, int x, int y, int frame);
\endcode */
#define DrawImageFrameXY(img, x, y, frame)do \
	{ oslSetImageFrame(img, frame); oslDrawImageXY(img, x, y); }while(0)

class GodLibrary
{
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

/** Get real time info about memory.

\code
GetMemoryInfo();
    Arena:	Current total non-mmapped bytes allocated from system.
    Used:	Current used memory.
    Free:	Current free memory.
\endcode */
void static GetMemoryInfo();

/** Load an image specifying the frame size directly

\code
LoadSpriteFilePNG(char *filename, int location, int pixelFormat, int frameWidth, int frameHeight);
\endcode */
OSL_IMAGE static *LoadSpriteFilePNG(char *filename, int location, int pixelFormat, int frameWidth, int frameHeight);
};

//coordinates in pixels
class Coordinates2D
{
public:
	Coordinates2D(); //x=0,y=0 
	Coordinates2D(float x, float y);
	float const AimTo(const Coordinates2D &enemy);
/** Calculates the distance between two coordenates

\code
http://pt.wikipedia.org/wiki/Teorema_de_Pit%C3%A1goras -> Distância entre dois pontos
SquareDistance(const Coordinates2D &enemy);
\endcode */
	float const SquareDistance(const Coordinates2D &enemy);
	
	float X;
	float Y;
};

void lowerCase(string &str); //http://www.cplusplus.com/forum/beginner/613/

class ReferenceCounted
{
public:
	ReferenceCounted();
	
	void AddReference();
	void RemoveReference();
private:
	int mReferenceCount;
};

#endif