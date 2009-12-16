//**************************************************************************
//		PSP Project: 'Gods Defense' - Fps.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef FPS_H_
#define FPS_H_

class Fps
{

public:
	void static initFps();
	void static updateFps();
	void static renderInfo();
	float static getFps();
	unsigned int static getUpf();
};
#endif