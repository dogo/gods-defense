//**************************************************************************
//		PSP Project: 'Gods Defense' - Adhoc.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Adhoc.h"
#include <pspnet_adhoc.h>

char productID[] = "ULUS99999";
Adhoc *Adhoc::resultConnection = NULL;

Adhoc::Adhoc()
{
	mHasServerPeer = false;
	mServerAccepted = false;
	mReady = false;
	mSelectedPeer = 0;
	mRequestStarted = 0;
	mSocket = -1;
	mLastSend = 0;
	mSession = NULL;
}

Adhoc::~Adhoc()
{
	if (mSocket >= 0) sceNetAdhocPdpDelete(mSocket, 0);
	delete mSession;
	if (mReady) oslAdhocTerm();
}

bool Adhoc::beginSession(bool host, const char *map, u32 hash, u32 nonce)
{
	if (mSession) return true;
	// OSLib's receive wrapper returns queued bytes and overwrites the peer MAC.
	mSocket = sceNetAdhocPdpCreate(oslAdhocGetMacAddress(), 778, 2048, 0);
	if (mSocket < 0) return false;
	mSession = new MultiplayerSession(host, map, hash, nonce);
	return true;
}

void Adhoc::updateSession(u32 now)
{
	if (!mSession || mSocket < 0) return;
	for (int i = 0; i < 8; ++i)
	{
		unsigned char buffer[sizeof(MultiplayerPacket) + 1], source[6];
		unsigned short port = 0;
		unsigned int size = sizeof(buffer);
		if (sceNetAdhocPdpRecv(mSocket, source, &port, buffer, &size, 0, 1) < 0) break;
		if (port == 778 && !memcmp(source, mServerPeerMac, 6)) mSession->receive(buffer, size);
	}
	if (now - mLastSend >= 250)
	{
		MultiplayerPacket packet = mSession->outgoing();
		if (mSession->phase() != MultiplayerSession::WaitingMap && mSession->phase() != MultiplayerSession::LoadingMap)
			sceNetAdhocPdpSend(mSocket, mServerPeerMac, 778, &packet, sizeof(packet), 0, 1);
		mLastSend = now;
	}
}

void Adhoc::AdhocClient()
{
	mReady = oslAdhocInit(productID) == 0;
}

remotePsp *Adhoc::getPeer()
{
	return mHasServerPeer ? oslAdhocGetPspByMacAddress(mServerPeerMac) : NULL;
}

bool Adhoc::clientWaitingConnection(u32 now)
{
	remotePsp *peer = getPeer();
	if (mHasServerPeer)
	{
		if (peer && peer->connectionState == OSL_ADHOC_ESTABLISHED)
			return false;
		if (!peer || peer->connectionState == OSL_ADHOC_REJECTED ||
			peer->connectionState == OSL_ADHOC_CANCELED || now - mRequestStarted >= 30000)
		{
			if (peer) oslAdhocRejectConnection(peer);
			mHasServerPeer = false;
		}
		else
		{
			oslDrawString(240, 120, "Waiting for host acceptance...");
			return true;
		}
	}
	const int count = oslAdhocGetRemotePspCount();
	if (count <= 0)
	{
		mSelectedPeer = 0;
		oslDrawString(240, 120, "Searching for a host...");
		return true;
	}
	if (mSelectedPeer >= count) mSelectedPeer = 0;
	if (osl_keys->pressed.down) mSelectedPeer = (mSelectedPeer + 1) % count;
	if (osl_keys->pressed.up) mSelectedPeer = (mSelectedPeer + count - 1) % count;
	peer = oslAdhocGetPspByIndex(mSelectedPeer);
	if (!peer) return true;
	oslDrawStringf(240, 120, "Cross: connect to %.24s", peer->name);
	if (osl_keys->pressed.cross)
	{
		memcpy(mServerPeerMac, peer->macAddress, 6);
		mHasServerPeer = true;
		mRequestStarted = now;
		// This OSLib call selects the matching target without its blocking wait loop.
		oslAdhocAcceptConnection(peer);
		oslFlushKey();
	}
	return true;
}

void Adhoc::AdhocServer()
{
	mReady = oslAdhocInit(productID) == 0;
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

void Adhoc::printInfo() //Prints some info
{
	u8 *macAddress = oslAdhocGetMacAddress();
	oslIntraFontSetStyle(gFont, 0.6, RGBA(255,255,255,255), RGBA(0,0,0,0), 0.f, INTRAFONT_ALIGN_LEFT);
	oslDrawStringf(10, 25, "Current state: %s", oslAdhocGetState() == ADHOC_INIT ? "OK" : "KO");
	oslDrawStringf(10, 40, "Your MAC address: %02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}
