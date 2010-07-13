//**************************************************************************
//		PSP Project: 'Gods Defense' - Sprites.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef SPRITES_H_
#define SPRITES_H_

#include "../../Include/ILib.h"

class Sprites
{

public:
	/** Draws a specific frame of an image at a specified location (like a real sprite)

	\code
	DrawImageFrameXY(OSL_IMAGE *img, int x, int y, int frame);
	\endcode */
#define DrawImageFrameXY(img, x, y, frame)do \
	{ oslSetImageFrame(img, frame); oslDrawImageXY(img, x, y); }while(0)


	/** Load an image specifying the frame size directly

	\code
	LoadSpriteFilePNG(char *filename, int location, int pixelFormat, int frameWidth, int frameHeight);
	\endcode */
	OSL_IMAGE static *LoadSpriteFilePNG(char *filename, int location, int pixelFormat, int frameWidth, int frameHeight);
};
#endif