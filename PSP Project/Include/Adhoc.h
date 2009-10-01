//**************************************************************************
//		PSP Project: 'Gods Defense' - Adhoc.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef ADHOC_H_INCLUDED
#define ADHOC_H_INCLUDED

#include "../Include/ILib.h"

class Adhoc
{
public:
	Adhoc();
	~Adhoc();

	void printInfo(); //Prints some info

	//Ad-hoc Client
	void AdhocClient();
	void clientConnected(struct remotePsp *aPsp, char *finalScore);	//The client is connected and can send data.
	void clientSendScore(char *finalScore);

	//Ad-hoc Server
	void AdhocServer();
	void serverConnected(struct remotePsp *aPsp, char *remotePspScore, char *finalScore);
	void serverUpdate(char *remotePspScore);
	bool serverWaitingConnection();
};
#endif