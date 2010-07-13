//**************************************************************************
//		PSP Project: 'Gods Defense' - ReferenceCounted.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/ReferenceCounted.h"


//ReferenceCounted
ReferenceCounted::ReferenceCounted()
{
	mReferenceCount = 0;
}

void ReferenceCounted::AddReference()
{
	mReferenceCount++;
}

void ReferenceCounted::RemoveReference()
{
	mReferenceCount--;
	if (mReferenceCount == 0)
		delete this;
}