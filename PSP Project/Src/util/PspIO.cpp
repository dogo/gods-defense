//**************************************************************************
//		PSP Project: 'Gods Defense' - PspIO.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/PspIO.h"


void PspIO::lowerCase(string &str)
{
	for (unsigned int i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);
}

string PspIO::getCurrentDirectory()
{
	char buffer[601];
	getcwd(buffer, 600);

	return buffer;
}