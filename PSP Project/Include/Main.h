//**************************************************************************
//		PSP Project: 'Gods Defense' - Main.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <oslib/oslib.h>
#include <psprtc.h>

#ifdef MEMORY_DEBUG
#include "../Include/GodLibrary.h"
#endif

#ifdef SHOW_FPS
#include "../Include/Fps.h"
#endif

#include "../Include/ScreenManager.h"

	int main();

	int initOSLib();

	int endOSLib();

	u32 GetTicks();

#endif