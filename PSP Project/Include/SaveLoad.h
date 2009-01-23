//**************************************************************************
//		PSP Project: 'Gods Defense' - SaveLoad.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef SAVELOAD_H_INCLUDED
#define SAVELOAD_H_INCLUDED

#include "../Include/ILib.h"

class SaveLoad
{
private:
	int fd;
	int flen;
	char read_buffer[128*1024];
	char write_buffer[128*1024];

public:

	char const *cON;
	char const *cOFF;
	SaveLoad();
	void save(char *state);
	int load();
};
#endif