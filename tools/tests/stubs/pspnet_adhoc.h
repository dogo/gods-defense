#pragma once
int sceNetAdhocPdpCreate(unsigned char *, unsigned short, unsigned int, int);
int sceNetAdhocPdpDelete(int, int);
int sceNetAdhocPdpSend(int, unsigned char *, unsigned short, void *, unsigned int, unsigned int, int);
int sceNetAdhocPdpRecv(int, unsigned char *, unsigned short *, void *, void *, unsigned int, int);
