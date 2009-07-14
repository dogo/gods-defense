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

void GodLibrary::drawPixel(float x, float y, OSL_COLOR color)
{
	oslDrawFillRect(x, y , x+1, y+1, color);
}

void GodLibrary::drawCircle(int x, int y, int radius, OSL_COLOR color)
{
	for(int i=0;i<360;i+=30)
	{
		float tx = x + sinf((i*(M_PI/180))*radius);
		float ty = y - cosf((i*(M_PI/180))*radius);
		drawPixel(tx, ty, color);
	}
}

void GodLibrary::Animation(OSL_IMAGE *mAnimateImg, int mMAXFRAMES, int mSpritePosition, int mImageWidth, int mImageHeight)
{
	//time of the animation
	mTempAnimation++;
	if (mTempAnimation == mMAXFRAMES)
	{
		//relaunch the time
		mTempAnimation = 0;

		//next step of the animation
		mAnimation++;

		//display the right position
		//oslSetImageTileSize (image, x, y, width, height); 
		oslSetImageTileSize(mAnimateImg,(mAnimation * mImageWidth), mSpritePosition, mImageWidth, mImageHeight);
		mAnimateImg->centerX = (mAnimation * mImageWidth) >> 1;		//Sprite hotspot

		//relaunch animation
		if (mAnimation == mMAXFRAMES)
			mAnimation = 0;
	}
}

Point2D::Point2D()
{
	X = 0;
	Y = 0;
}

Point2D::Point2D(float x, float y)
{
	X = x;
	Y = y;
}

float const Point2D::AimTo(const Point2D &enemy)
{
	float dy = enemy.Y - this->Y; //dy = enemy.Y - Tower->y
	float dx = enemy.X - this->X; //dx = enemy.x - Tower->x
	return atan2(dy,dx); // atan2 from math.h, arco tangente :D, owww trigonometria.
}

float const Point2D::SquareDistance(const Point2D &enemy)
{   
	float dx = enemy.X - this->X; //dy = enemy.Y - Tower->y 	
	float dy = enemy.Y - this->Y; //dx = enemy.x - Tower->x
	return sqrt((dy*dy)+(dx*dx)); //Pythagoras distance is D(A,B) = sqrt( (xA-xB)² + (yA-yB)²)
}