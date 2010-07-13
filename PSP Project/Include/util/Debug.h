//**************************************************************************
//		PSP Project: 'Gods Defense' - Debug.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include "../../Include/ILib.h"

class Debug
{
private:
	
public:
	/** Get real time info about memory.

\code
GetMemoryInfo();
    Arena:	Current total non-mapped bytes allocated from system.
    Used:	Current used memory.
    Free:	Current free memory.
\endcode */
	void static GetMemoryInfo();
};

#endif