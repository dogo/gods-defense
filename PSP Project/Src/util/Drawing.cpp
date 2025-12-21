//**************************************************************************
//		PSP Project: 'Gods Defense' - Drawing.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/Drawing.h"
#include <math.h>

short gState = 0;
int gFade = 255;

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
	oslDrawFillRect((int)x, (int)y, (int)x+1, (int)y+1, color);
}

// Draw a smooth pixel with anti-aliasing effect (2x2 block for thin smooth line)
static void drawSmoothPixel(int x, int y, OSL_COLOR color)
{
	// Draw a 2x2 block for smooth but thin appearance
	oslDrawFillRect(x, y, x+2, y+2, color);
}

void Drawing::drawCircle(int x, int y, int radius, OSL_COLOR color)
{ 
	// Validate radius
	if (radius <= 0 || radius > 500)
		return;
	
	// Draw circle using trigonometry with very small step for perfectly smooth line
	// Using step of 0.2 degrees ensures smoothness with good performance
	float step = 0.2f;
	for (float angle = 0.0f; angle < 360.0f; angle += step)
	{
		float rad = angle * M_PI / 180.0f;
		float px = x + radius * oslSinf(rad);
		float py = y - radius * oslCosf(rad);
		
		// Draw smooth pixel with anti-aliasing effect (2x2 block for thin smooth line)
		int px_int = (int)(px + 0.5f); // Round to nearest integer
		int py_int = (int)(py + 0.5f);
		drawSmoothPixel(px_int, py_int, color);
	}
}
