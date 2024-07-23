//**************************************************************************
//		PSP Project: 'Gods Defense' - Fps.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************
#include <pspkernel.h>
#include <string.h>
#include <oslib/oslib.h>
#include "../../Include/ILib.h"
#include "../../Include/util/Fps.h"

static struct FpsInfo
{
    unsigned int samples[8];
    int sampleposition;
    int samplesvalid;
    unsigned int timestamp;
    unsigned int averagetime;
} fps;

void Fps::initFps()
{
    memset(&fps, 0, sizeof(fps));
}

void Fps::updateFps()
{
    unsigned int now = sceKernelGetSystemTimeLow();
    int i;

    fps.samples[fps.sampleposition] = now - fps.timestamp;
    fps.timestamp = now;
    fps.sampleposition = (fps.sampleposition + 1) % 8;

    if (fps.samplesvalid < 8)
    {
        fps.samplesvalid++;
    }

    fps.averagetime = 0;
    for (i = 0; i < 8; i++)
    {
        fps.averagetime += fps.samples[i];
    }
    fps.averagetime /= fps.samplesvalid;
}

float Fps::getFps()
{
    if (fps.averagetime != 0)
    {
        float x = 1.0f / fps.averagetime;
        float y = x * 1000000.0f;
        return (y + 0.5f);
    }
    return 0.0f;
}

unsigned int Fps::getUpf()
{
    return fps.averagetime;
}

void Fps::renderInfo()
{
	//dogo : oslPrintf_xy(0,25,"FPS : %0.1f %d\n", getFps(), getUpf());
	char fps[256];
	sprintf(fps, "FPS : %0.1f", getFps());
	oslIntraFontSetStyle(gFont, 1.0f,RGBA(192,192,192,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_LEFT);
	oslDrawString(0,23, fps);
}