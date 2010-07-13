//**************************************************************************
//		PSP Project: 'Gods Defense' - Coordinates2D.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/Coordinates2D.h"

Coordinates2D::Coordinates2D()
{
	X = 0;
	Y = 0;
}

Coordinates2D::Coordinates2D(float x, float y)
{
	X = x;
	Y = y;
}

float const Coordinates2D::AimTo(const Coordinates2D &enemy)
{
	float dy = enemy.Y - this->Y; //dy = enemy.Y - Tower->y
	float dx = enemy.X - this->X; //dx = enemy.x - Tower->x
	return atan2(dy,dx); // atan2 from math.h, arco tangente :D, owww trigonometria.
}

float const Coordinates2D::SquareDistance(const Coordinates2D &enemy)
{   
	float dx = enemy.X - this->X; //dy = enemy.Y - Tower->y 	
	float dy = enemy.Y - this->Y; //dx = enemy.x - Tower->x
	return (dy*dy)+(dx*dx); //Pythagoras distance is D(A,B) = sqrt( (xA-xB)² + (yA-yB)²), but we use without the sqrt
}