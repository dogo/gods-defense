//**************************************************************************
//		PSP Project: 'Gods Defense' - Adhoc.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef ADHOC_H_INCLUDED
#define ADHOC_H_INCLUDED

#include "../Include/ILib.h"
#include "MultiplayerSession.h"

class Adhoc
{
private:
	u8 mServerPeerMac[6];
	bool mHasServerPeer;
	bool mServerAccepted;
	bool mReady;
	int mSelectedPeer;
	u32 mRequestStarted;
	int mSocket;
	u32 mLastSend;
	MultiplayerSession *mSession;
	u32 mLastReceive;
	bool mDisconnected;
public:
	static Adhoc *resultConnection;
	Adhoc();
	~Adhoc();

	void printInfo(); //Prints some info

	//Ad-hoc Client
	void AdhocClient();
	bool clientWaitingConnection(u32 now);
	bool isReady() const { return mReady; }
	remotePsp *getPeer();
	MultiplayerSession *session() { return mSession; }
	bool beginSession(bool host, const char *map, u32 hash, u32 nonce);
	void updateSession(u32 now);
	bool disconnected() const { return mDisconnected; }

	//Ad-hoc Server
	void AdhocServer();
	bool serverWaitingConnection(u32 now);
};
#endif
