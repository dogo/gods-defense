//**************************************************************************
//		PSP Project: 'Gods Defense' - ReferenceCounted.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef REFERENCECOUNTED_H_
#define REFERENCECOUNTED_H_

#include "../../Include/ILib.h"

class ReferenceCounted
{
public:
	ReferenceCounted();

	void AddReference();
	void RemoveReference();
private:
	int mReferenceCount;
};

#endif