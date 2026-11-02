//**************************************************************************
//		PSP Project: 'Gods Defense' - Adhoc.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Adhoc.h"

char productID[] = "ULUS99999";

Adhoc::Adhoc()
{
	mHasServerPeer = false;
	mServerAccepted = false;
}

Adhoc::~Adhoc()
{
}

void Adhoc::AdhocClient()
{
	int skip = 0;
	int quit = 0;
	int i = 0;
	int current = 0;

	int init = oslAdhocInit(productID);
	if (init)
	{
		char message[100] = "";
		sprintf(message, "adhocInit error: %i", init);
		Drawing::showMessage(message, "Debug");
		return;
	}

	while(!quit)
	{
		if (!skip)
		{
			oslStartDrawing();

			if (oslAdhocGetRemotePspCount())
			{
				oslIntraFontSetStyle(gFont, 1.1f,RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_LEFT);
				oslDrawString(10, 40, "Press X to request a connection");
			}

			for (i=0; i < oslAdhocGetRemotePspCount(); i++)
			{
				if (i == current)
					oslIntraFontSetStyle(gFont, 1.3, RGBA(100,100,100,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_LEFT);
				else
					oslIntraFontSetStyle(gFont, 1.3, RGBA(175,137,62,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_LEFT);
				oslDrawString(10, 100 + 15 * i, oslAdhocGetPspByIndex(i)->name);
			}
			oslEndDrawing();
		}
		oslReadKeys();
		oslEndFrame();
		skip = oslSyncFrame();

		if (osl_keys->pressed.down)
		{
			if (++current >= oslAdhocGetRemotePspCount())
				current = 0;
		}
		else if (osl_keys->pressed.up)
		{
			if (--current < 0)
				current = oslAdhocGetRemotePspCount() - 1;
		}
		else if (osl_keys->pressed.cross && oslAdhocGetRemotePspCount())
		{
			//Request a connection:
			oslAdhocRequestConnection(oslAdhocGetPspByIndex(current), 30, NULL);
			quit = 1;
		}
	}
}

void Adhoc::clientConnected(struct remotePsp *aPsp, char *finalScore)
{
	oslAdhocSendData(aPsp, finalScore, strlen(finalScore));
}

void Adhoc::clientSendScore(char *finalScore)
{
	if (oslAdhocGetRemotePspCount())
	{
		oslAdhocRequestConnection(oslAdhocGetPspByIndex(0), 30, NULL);
		clientConnected(oslAdhocGetPspByIndex(0), finalScore);
	}
}


void Adhoc::AdhocServer()
{
	int init = oslAdhocInit(productID);
	if (init)
	{
		char message[100] = "";
		snprintf(message, sizeof(message), "adhocInit error: %i", init);
		Drawing::showMessage(message, "Debug");
		return;
	}
}

bool Adhoc::serverWaitingConnection()
{
	if (!mHasServerPeer)
	{
		remotePsp *request = oslAdhocGetConnectionRequest();
		if (request)
		{
			memcpy(mServerPeerMac, request->macAddress, 6);
			mHasServerPeer = true;
			mServerAccepted = false;
		}
	}
	// OSLib compacts its peer array when someone leaves; never retain its pointers.
	remotePsp *peer = mHasServerPeer ? oslAdhocGetPspByMacAddress(mServerPeerMac) : NULL;
	if (!peer || peer->connectionState == OSL_ADHOC_CANCELED || peer->connectionState == OSL_ADHOC_REJECTED)
	{
		mHasServerPeer = false;
		mServerAccepted = false;
		return true;
	}
	if (mServerAccepted)
		return peer->connectionState != OSL_ADHOC_ESTABLISHED;
	oslIntraFontSetStyle(gFont, 0.6f, RGBA(255,232,163,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawStringf(240, 110, "Accept %.24s?", peer->name);
	oslDrawString(240, 135, "Cross: accept    Circle: reject");
	if (osl_keys->pressed.cross)
	{
		oslAdhocAcceptConnection(peer);
		mServerAccepted = true;
		oslFlushKey();
	}
	else if (osl_keys->pressed.circle)
	{
		oslAdhocRejectConnection(peer);
		mHasServerPeer = false;
		oslFlushKey();
	}
	return true;
}

void Adhoc::serverConnected(remotePsp *aPsp, char *remotePspScore, char *finalScore)
{
}

void Adhoc::serverUpdate(char *remotePspScore)
{
}

void Adhoc::printInfo() //Prints some info
{
	u8 *macAddress = oslAdhocGetMacAddress();
	oslIntraFontSetStyle(gFont, 0.6, RGBA(255,255,255,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(10, 25, "Current state: %s", oslAdhocGetState() == ADHOC_INIT ? "OK" : "KO");
	oslDrawStringf(10, 40, "Your MAC address: %02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}
