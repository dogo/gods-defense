//**************************************************************************
//		PSP Project: 'Gods Defense' - Drawing.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/Drawing.h"

short gState = 0;
int gFade = 255;
OSL_IMAGE *pEllipse = NULL;

void Drawing::drawSplash(int iTime, OSL_IMAGE *Splash) {
	oslDrawImageXY(Splash, (480/2) - (Splash->stretchX/2), (272/2) - (Splash->stretchY/2));
	if(gState == 0 || gState == 2) {
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, gFade));
	}
	if (gState == 0) {
		gFade = gFade - 2;
		if (gFade <= 0) {
			gFade = 0;
			gState = 1;
		}
	} else if (gState == 1) {
		sceKernelDelayThread(iTime);
		gState = 2;
	} else if (gState == 2) {
		gFade = gFade + 2;		 
	}
}

void Drawing::drawPixel(float x, float y, OSL_COLOR color)
{
	oslDrawFillRect(x, y , x+1, y+1, color);
}

void Drawing::drawCircle(int x, int y, int radius, OSL_COLOR color)
{ 
	pEllipse->x = x - radius; // set the position of the image
	pEllipse->y = y - radius; // "
	pEllipse->stretchX = radius * 2; // set the width of the ellipsoid
	pEllipse->stretchY = radius * 2; // set the height "

	// store the current params
	OSL_ALPHA_PARAMS currentParameters;

	oslGetAlphaEx(&currentParameters);

	// now we set a filter to convert the white part of the ellipsoid image
	// (the circle part) to the color passed
	oslSetAlpha(OSL_FX_ALPHA | OSL_FX_COLOR, color);

	oslDrawImage(pEllipse); // draw it

	// back to normal
	oslSetAlphaEx(&currentParameters);
}

// run this function anywhere just once before drawing hte circle (usually the loading resources part of a game)
void Drawing::Initialize(int x, int y, int radius, OSL_COLOR color)
{
	if (pEllipse != NULL)
		oslDeleteImage(pEllipse);

	// create image
	pEllipse = oslCreateImage(200, 200, OSL_IN_VRAM, OSL_PF_8888);
	oslAssert(pEllipse);

	// clear to alpha
	oslClearImage(pEllipse, RGBA(0, 0, 0, 0));

	// set the draw buffer to the new image
	oslSetDrawBuffer(pEllipse);

	//Every pixel written will take the value 0 (transparent)
	oslSetAlphaWrite(OSL_FXAW_SET, 255, 0);

	//But do not draw transparent pixels (only those greater than 0).
	oslSetAlphaTest(OSL_FXAT_GREATER, 0);

	// draw the circle on it, radius = 1/2 dimensions
	for(float i=0;i<360.0;i+=0.40)
	{
		float tx = x + radius * oslSinf(i * M_PI/180.0);
		float ty = y - radius * oslCosf(i * M_PI/180.0);
		drawPixel(tx, ty, color);
	}

	// set the draw buffer back to the default
	oslSetDrawBuffer(OSL_DEFAULT_BUFFER);
}