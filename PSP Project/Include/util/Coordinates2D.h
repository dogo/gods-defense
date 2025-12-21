//**************************************************************************
//		PSP Project: 'Gods Defense' - Coordinates2D.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef COORDINATES2D_H_
#define COORDINATES2D_H_

#include "../../Include/ILib.h"

//coordinates in pixels
class Coordinates2D
{
public:
	Coordinates2D(); //x=0,y=0 
	Coordinates2D(float x, float y);
	float const AimTo(const Coordinates2D &enemy);
	/** Calculates the distance between two coordinates

	\code
	http://en.wikipedia.org/wiki/Pythagorean_theorem -> Distance between two points
	SquareDistance(const Coordinates2D &enemy);
	\endcode */
	float const SquareDistance(const Coordinates2D &enemy);

	float X;
	float Y;
};

#endif