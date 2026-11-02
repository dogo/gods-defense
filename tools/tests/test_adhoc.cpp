#include "adhoc_stubs.h"
#include "../../PSP Project/Include/Adhoc.h"
#include <cassert>
Keys keys = {};
Keys *osl_keys = &keys;
bool osl_quit = false;
void *gFont = NULL;
remotePsp peer = {{1,2,3,4,5,6}, "Player", OSL_ADHOC_SELECTED};
bool present = true;
int accepts = 0, rejects = 0;
int oslAdhocInit(char *) { return 0; }
int oslAdhocGetRemotePspCount() { return present ? 1 : 0; }
remotePsp *oslAdhocGetPspByIndex(int i) { return present && i == 0 ? &peer : NULL; }
remotePsp *oslAdhocGetPspByMacAddress(const u8 *mac) { return present && !memcmp(mac, peer.macAddress, 6) ? &peer : NULL; }
remotePsp *oslAdhocGetConnectionRequest() { return present && peer.connectionState == OSL_ADHOC_SELECTED ? &peer : NULL; }
int oslAdhocRequestConnection(remotePsp *, int, int (*)(int)) { return 0; }
int oslAdhocSendData(remotePsp *, void *, int) { return 0; }
void oslAdhocAcceptConnection(remotePsp *) { ++accepts; }
void oslAdhocRejectConnection(remotePsp *p) { ++rejects; p->connectionState = OSL_ADHOC_JOINED; }
u8 *oslAdhocGetMacAddress() { return peer.macAddress; }
bool oslIsWlanPowerOn() { return true; }
int oslAdhocGetState() { return ADHOC_INIT; }
void oslAdhocTerm() {}
int sceNetAdhocPdpCreate(unsigned char *, unsigned short, unsigned int, int) { return 1; }
int sceNetAdhocPdpDelete(int, int) { return 0; }
int sceNetAdhocPdpSend(int, unsigned char *, unsigned short, void *, unsigned int, unsigned int, int) { return 0; }
int sceNetAdhocPdpRecv(int, unsigned char *, unsigned short *, void *, void *, unsigned int, int) { return -1; }
int main()
{
    Adhoc server;
    assert(server.serverWaitingConnection(100)); // A request alone cannot start the game.
    keys.pressed.cross = true;
    assert(server.serverWaitingConnection(100) && accepts == 1);
    peer.connectionState = OSL_ADHOC_ACCEPTED;
    assert(server.serverWaitingConnection(100)); // Wait for matching to finish too.
    peer.connectionState = OSL_ADHOC_ESTABLISHED;
    assert(!server.serverWaitingConnection(100));
    present = false;
    assert(server.serverWaitingConnection(100));
    present = true;
    peer.connectionState = OSL_ADHOC_SELECTED;
    keys.pressed.circle = true;
    assert(server.serverWaitingConnection(100) && rejects == 1);
    assert(server.serverWaitingConnection(100));
    Adhoc client;
    client.AdhocClient();
    assert(client.isReady());
    present = false;
    keys.pressed.up = true;
    assert(client.clientWaitingConnection(0)); // Empty discovery never indexes -1.
    oslFlushKey();
    present = true;
    peer.connectionState = OSL_ADHOC_JOINED;
    keys.pressed.cross = true;
    assert(client.clientWaitingConnection(100) && accepts == 1); // Too soon after the host appeared.
    assert(client.clientWaitingConnection(4099) && accepts == 1);
    assert(client.clientWaitingConnection(4100) && accepts == 2);
    assert(client.clientWaitingConnection(34100) && rejects == 2); // Request timeout.
    keys.pressed.cross = true;
    assert(client.clientWaitingConnection(34200) && accepts == 3); // Same host, already waited.
    peer.connectionState = OSL_ADHOC_ESTABLISHED;
    assert(!client.clientWaitingConnection(34300));
    assert(client.beginSession(false, "olympus", 123, 34300));
    client.updateSession(49299);
    assert(!client.disconnected());
    client.updateSession(49300);
    assert(client.disconnected()); // A silent peer cannot leave the game stuck forever.
}
