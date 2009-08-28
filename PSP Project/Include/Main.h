//**************************************************************************
//		PSP Project: 'Gods Defense' - Main.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <oslib/oslib.h>

#ifdef MEMORY_DEBUG
#include "../Include/GodLibrary.h"
#endif

#include "../Include/ScreenManager.h"

	int main();

	int initOSLib();

	int endOSLib();

#endif