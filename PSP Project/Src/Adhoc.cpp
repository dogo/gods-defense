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
	int skip = 0;
	int quit = 0;
	int i = 0;
	int current = 0;

	int init = oslAdhocInit("ULUS99999");
	if (init)
	{
		char message[100] = "";
		sprintf(message, "adhocInit error: %i", init);
		oslMessageBox(message, "Debug",  oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK , 0, 0, 0, 0));
		return;
	}

	while(!quit)
	{
		if (!skip)
		{
			oslStartDrawing();

			if (oslAdhocGetRemotePspCount())
			{
				oslIntraFontSetStyle(gFont, 1.3f,RGBA(255,255,255,255), RGBA(0,0,0,0),INTRAFONT_ALIGN_LEFT);
				oslDrawString(10, 40, "Press X to request a connection");
			}

			for (i=0; i < oslAdhocGetRemotePspCount(); i++)
			{
				if (i == current)
					oslIntraFontSetStyle(gFont, 1.3, RGBA(100,100,100,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
				else
					oslIntraFontSetStyle(gFont, 1.3, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
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
	
void Adhoc::clientConnected(struct remotePsp *aPsp)
{
	int skip = 0;
	char mess[100] = "Hello distant World !!!";

	while(!osl_quit){
		if (!skip){
			oslStartDrawing();

			printInfo();
			oslDrawStringf(10, 40, "Press O to send a message to %s", aPsp->name);
			oslDrawString(150, 250, "Press X to quit");

			oslEndDrawing();
		}
		oslEndFrame();
		skip = oslSyncFrame();

		oslReadKeys();
		if (osl_keys->released.cross)
		{
			oslQuit();
		}
		else if (osl_keys->released.circle)
		{
			oslAdhocSendData(aPsp, mess, strlen(mess));
		}
	}
}

void Adhoc::clientUpdate(char *finalScore)
{	
	if (oslAdhocGetRemotePspCount())
	{
		//Request a connection:
		oslAdhocRequestConnection(oslAdhocGetPspByIndex(0), 30, NULL);
		clientConnected(oslAdhocGetPspByIndex(0));
	}
}


void Adhoc::AdhocServer()
{
	int init = oslAdhocInit("ULUS99999");
	if (init)
	{
		char message[100] = "";
		snprintf(message, sizeof(message), "adhocInit error: %i", init);
		oslMessageBox(message, "Debug",  oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK , 0, 0, 0, 0));
		return;
	}
}

bool Adhoc::serverWaitingConnection()
{
	struct remotePsp *reqPsp = oslAdhocGetConnectionRequest();
	char message[100] = "";
	int dialog = OSL_DIALOG_NONE;

	if (reqPsp == NULL)
	{
		oslIntraFontSetStyle(gFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
		oslDrawStringf(10, 100, "Waiting for a connection request...");
		return true;
	}
	else
	{
		snprintf(message, sizeof(message), "Accept request from psp : %s", reqPsp->name);
		if (oslGetDialogType() == OSL_DIALOG_NONE)
			oslInitMessageDialog(message, 1);
	}

	dialog = oslGetDialogType();
	if (dialog)
	{
		oslDrawDialog();
		if (oslGetDialogStatus() == PSP_UTILITY_DIALOG_NONE)
		{
			if (dialog == OSL_DIALOG_MESSAGE)
			{
				int button = oslGetDialogButtonPressed();
				if (button == PSP_UTILITY_MSGDIALOG_RESULT_YES)
				{
					oslAdhocAcceptConnection(reqPsp);
				}
				else if (button == PSP_UTILITY_MSGDIALOG_RESULT_NO)
				{
					oslAdhocRejectConnection(reqPsp);
				}
			}
		oslEndDialog();
		}
	}
	return false;
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
	oslIntraFontSetStyle(gFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(10, 25, "Current state: %s", oslAdhocGetState() == ADHOC_INIT ? "OK" : "KO");
	oslDrawStringf(10, 40, "Your MAC address: %02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}