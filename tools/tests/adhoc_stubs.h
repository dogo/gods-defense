#ifndef ADHOC_TEST_STUBS_H
#define ADHOC_TEST_STUBS_H
#define ILIB_H_INCLUDED
#include <cstring>
#include <cstdio>
typedef unsigned char u8;
typedef unsigned int u32;
struct remotePsp { u8 macAddress[8]; char name[257]; int connectionState; };
enum { OSL_ADHOC_DISCONNECTED, OSL_ADHOC_JOINED, OSL_ADHOC_SELECTED,
       OSL_ADHOC_REJECTED, OSL_ADHOC_CANCELED, OSL_ADHOC_ACCEPTED, OSL_ADHOC_ESTABLISHED };
enum { ADHOC_INIT, INTRAFONT_ALIGN_LEFT, INTRAFONT_ALIGN_CENTER };
struct Keys { struct { bool cross, circle, up, down; } pressed; };
extern Keys *osl_keys;
extern bool osl_quit;
extern void *gFont;
inline unsigned int RGBA(int, int, int, int) { return 0; }
inline void oslIntraFontSetStyle(void *, float, unsigned int, unsigned int, float, int) {}
inline void oslDrawString(int, int, const char *) {}
inline void oslDrawStringf(int, int, const char *, ...) {}
inline void oslStartDrawing() {}
inline void oslEndDrawing() {}
inline void oslEndFrame() {}
inline int oslSyncFrame() { return 0; }
inline void oslReadKeys() {}
inline void oslFlushKey() { memset(osl_keys, 0, sizeof(*osl_keys)); }
struct Drawing { static void showMessage(const char *, const char *) {} };
int oslAdhocInit(char *);
int oslAdhocGetRemotePspCount();
remotePsp *oslAdhocGetPspByIndex(int);
remotePsp *oslAdhocGetPspByMacAddress(const u8 *);
remotePsp *oslAdhocGetConnectionRequest();
int oslAdhocRequestConnection(remotePsp *, int, int (*)(int));
int oslAdhocSendData(remotePsp *, void *, int);
void oslAdhocAcceptConnection(remotePsp *);
void oslAdhocRejectConnection(remotePsp *);
u8 *oslAdhocGetMacAddress();
int oslAdhocGetState();
void oslAdhocTerm();
#endif
