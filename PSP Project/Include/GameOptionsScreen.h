//**************************************************************************
//		PSP Project: 'Gods Defense' - GameOptionsScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GAMEOPTIONSSCREEN_H_INCLUDED
#define GAMEOPTIONSSCREEN_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/GameScreen.h"
#include <vector>
#include <string>

class GameOptionsScreen : public IScreen
{
private:
	void ChooseMap(); //Set selected map to load

public:
	GameOptionsScreen();
	~GameOptionsScreen();
	virtual void draw();
	virtual void update(u64 timePassed);

	int mSelectedMap; //Index of current map
	vector<string> mMap; // vector of map names

};
#endif
