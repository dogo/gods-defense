//**************************************************************************
//		PSP Project: 'Gods Defense' - Adhoc.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Adhoc.h"

Adhoc::Adhoc()
{
}

Adhoc::~Adhoc()
{
}

void Adhoc::AdhocClient()
{
	int i = 0;
	current = 0;

	int init = oslAdhocInit("ULUS99999");
	if (init)
	{
		char message[100] = "";
		sprintf(message, "adhocInit error: %i", init);
		oslMessageBox(message, "Debug",  oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK , 0, 0, 0, 0));
		return;
	}
}
	
void Adhoc::clientConnected(struct remotePsp *aPsp, char *finalScore)
{
	oslAdhocSendData(aPsp, finalScore, strlen(finalScore));
}

void Adhoc::clientUpdate(char *finalScore)
{	
	if (oslAdhocGetRemotePspCount())
	{
		//Request a connection:
		int mConnectionState = oslAdhocRequestConnection(oslAdhocGetPspByIndex(0), 30, NULL);
		clientConnected(oslAdhocGetPspByIndex(0), finalScore);
	}
}


void Adhoc::AdhocServer()
{
}

void Adhoc::serverConnected(remotePsp *aPsp)
{
}

void Adhoc::printInfo() //Prints some info
{
	u8 *macAddress = oslAdhocGetMacAddress();
	oslIntraFontSetStyle(gFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(10, 25, "Current state: %s", oslAdhocGetState() == ADHOC_INIT ? "OK" : "KO");
	oslDrawStringf(10, 40, "Your MAC address: %02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}