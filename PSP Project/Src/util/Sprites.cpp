//**************************************************************************
//		PSP Project: 'Gods Defense' - Sprites.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/Sprites.h"


OSL_IMAGE  *Sprites::LoadSpriteFilePNG(char *filename, int location, int pixelFormat, int frameWidth, int frameHeight)
{
	OSL_IMAGE *img = oslLoadImageFilePNG(filename, location, pixelFormat);
	if (img)
		oslSetImageFrameSize(img, frameWidth, frameHeight);
	return img;
}

