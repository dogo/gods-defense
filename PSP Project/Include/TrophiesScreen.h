//**************************************************************************
//		PSP Project: 'Gods Defense' - TrophiesScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef TROPHIESSCREEN_H_INCLUDED
#define TROPHIESSCREEN_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/util/MemoryStick.h"
#include "../Include/TrophyManager.h"

class TrophiesScreen : public IScreen
{
private:
	OSL_IMAGE *back;
	int mSelectedTrophy;
	void DrawTrophyRow(const int &index, const int &yPosition);

public:
	TrophiesScreen();

	~TrophiesScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

};
#endif
