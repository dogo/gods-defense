//**************************************************************************
//		PSP Project: 'Gods Defense' - Map.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

//Class Declarations
class Wave;
class Path;
class Map;

#include "../Include/GameScreen.h"
#include "../Include/Tower.h"
#include "../Include/GodLibrary.h"
#include "tinyxml/tinyxml.h"

using namespace std;

class Wave
{
public:
	Wave();
	Wave(TiXmlElement *waveNode);
	~Wave();
};

class Path
{
public:
	Path();
	Path(TiXmlElement *pathNode);
};

class Map
{
public:
	void LoadMap(const string &mapName);
};

#endif