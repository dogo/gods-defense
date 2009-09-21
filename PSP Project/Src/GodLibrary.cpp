//**************************************************************************
//		PSP Project: 'Gods Defense' - GodLibrary.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GodLibrary.h"

short gState = 0;
int gFade = 255;

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

void GodLibrary::drawPixel(float x, float y, OSL_COLOR color)
{
	oslDrawFillRect(x, y , x+1, y+1, color);
}

void GodLibrary::drawCircle(int x, int y, int radius, OSL_COLOR color)
{
	for(float i=0;i<360.0;i+=0.40)
	{
		float tx = x + radius * sinf(i * M_PI/180.0);
		float ty = y - radius * cosf(i * M_PI/180.0);
		drawPixel(tx, ty, color);
	}
}

void GodLibrary::GetMemoryInfo()
{
    struct mallinfo minfo = mallinfo();

    int mem_total   = minfo.arena * 10 / 1024 / 1024;
    int mem_used    = minfo.uordblks * 10 / 1024 / 1024;
    int mem_free    = minfo.fordblks * 10 / 1024 / 1024;

    oslPrintf_xy(0, 10, "Arena: %u.%01uMB\n", mem_total/10, mem_total%10); //current total non-mmapped bytes allocated from system
    oslPrintf_xy(0, 20, "Used:  %u.%01uMB\n", mem_used/10, mem_used%10); //current used memory
    oslPrintf_xy(0, 30, "Free:  %u.%01uMB\n", mem_free/10, mem_free%10); //current free memory
}

OSL_IMAGE  *GodLibrary::LoadSpriteFilePNG(char *filename, int location, int pixelFormat, int frameWidth, int frameHeight)
{
	OSL_IMAGE *img = oslLoadImageFilePNG(filename, location, pixelFormat);
	if (img)
		oslSetImageFrameSize(img, frameWidth, frameHeight);
	return img;
}

Coordinates2D::Coordinates2D()
{
	X = 0;
	Y = 0;
}

Coordinates2D::Coordinates2D(float x, float y)
{
	X = x;
	Y = y;
}

float const Coordinates2D::AimTo(const Coordinates2D &enemy)
{
	float dy = enemy.Y - this->Y; //dy = enemy.Y - Tower->y
	float dx = enemy.X - this->X; //dx = enemy.x - Tower->x
	return atan2(dy,dx); // atan2 from math.h, arco tangente :D, owww trigonometria.
}

float const Coordinates2D::SquareDistance(const Coordinates2D &enemy)
{   
	float dx = enemy.X - this->X; //dy = enemy.Y - Tower->y 	
	float dy = enemy.Y - this->Y; //dx = enemy.x - Tower->x
	return (dy*dy)+(dx*dx); //Pythagoras distance is D(A,B) = sqrt( (xA-xB)² + (yA-yB)²), but we use without the sqrt
}

void lowerCase(string &str)
{
	for (unsigned int i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);
}