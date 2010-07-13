//**************************************************************************
//		PSP Project: 'Gods Defense' - Debug.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/Debug.h"

void Debug::GetMemoryInfo()
{
	struct mallinfo minfo = mallinfo();

	int mem_total   = minfo.arena * 10 / 1024 / 1024;
	int mem_used    = minfo.uordblks * 10 / 1024 / 1024;
	int mem_free    = minfo.fordblks * 10 / 1024 / 1024;

	oslPrintf_xy(0, 10, "Arena: %u.%01uMB\n", mem_total/10, mem_total%10); //current total non-mapped bytes allocated from system
	oslPrintf_xy(0, 20, "Used:  %u.%01uMB\n", mem_used/10, mem_used%10); //current used memory
	oslPrintf_xy(0, 30, "Free:  %u.%01uMB\n", mem_free/10, mem_free%10); //current free memory
}