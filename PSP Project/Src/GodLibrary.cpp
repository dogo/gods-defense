//**************************************************************************
//		PSP Project: 'Gods Defense' - GodLibrary.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GodLibrary.h"

short state = 0;
int fade = 255;

//Dogo : This is a cpu-killer wait function.
void GodLibrary::Wait(unsigned long iTime) {
	unsigned long lastTime = clock() / ((long) CLK_TCK/100);
	unsigned diffTime = lastTime + iTime;

	while(lastTime <= diffTime) {
		lastTime = clock() / ((long) CLK_TCK/100);
	}
}

void GodLibrary::drawSplash(int iTime, OSL_IMAGE *Splash) {
	oslDrawImageXY(Splash, (480/2) - (Splash->stretchX/2), (272/2) - (Splash->stretchY/2));
	if(state == 0 || state == 2) {
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, fade));
	}
	if (state == 0) {
		fade = fade - 2;
		if (fade <= 0) {
			fade = 0;
			state = 1;
		}
	} else if (state == 1) {
		sceKernelDelayThread(iTime);
		state = 2;
	} else if (state == 2) {
		fade = fade + 2;		 
	}
}