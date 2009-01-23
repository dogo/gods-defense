//**************************************************************************
//		PSP Project: 'Gods Defense' - SaveLoad.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/SaveLoad.h"

SaveLoad::SaveLoad()
{
	cON	= "1";
	cOFF = "0";

	if(!(fd = sceIoOpen(Resource::SETTINGS_FILENAME, PSP_O_RDWR|PSP_O_CREAT, 0777))) {
		// Error if we cant open it
	} else {
		flen = sceIoRead(fd, read_buffer, sizeof(read_buffer));
		if(flen <= 0) { // if flen is 0 or lower, this means that the file is empty, it didn't read any bytes.
			sprintf(write_buffer, cOFF);
			sceIoWrite(fd, write_buffer, sizeof(write_buffer));
		}
	}
	sceIoClose(fd);
}

void SaveLoad::save(char *state)
{
	if(!(fd = sceIoOpen(Resource::SETTINGS_FILENAME, PSP_O_RDWR, 0777))) {
		// Error if we cant open it
	} else {
			sprintf(write_buffer, state);
			sceIoWrite(fd, write_buffer, sizeof(write_buffer));
		}
	sceIoClose(fd);
}

int SaveLoad::load()
{
	int state = -1;

	if(!(fd = sceIoOpen(Resource::SETTINGS_FILENAME, PSP_O_RDONLY, 0777))) {
		// Error if we cant open it
	} else {
		sceIoRead(fd, read_buffer, sizeof(read_buffer));
		if(read_buffer[0] == '1')
			state =	1;
		if(read_buffer[0] == '0')
			state = 0;
	}
	sceIoClose(fd);
	return state;
}