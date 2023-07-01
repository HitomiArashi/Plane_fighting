#pragma once

#ifndef EXPLOSION_H_

#define EXPLOSION_H_

//The header and library will use

#include "BulletObject.h"
#include "Common_Function.h"

//Info of each frame

const int EXP_WIDTH = 165;

const int EXP_HEIGHT = 165;

class Explosion : public BaseObject
{
public:

	Explosion();
	~Explosion();

	//Set the clip of explosion will be shown

	void set_clip();

	//Set the frame for the clip

	void set_frame(const int& fr)
	{
		frame_ = fr;
	}

	//Show the clip of explosion

	void ShowEx(SDL_Surface* des);

private:

	int frame_;
	SDL_Rect clip_[4];
};
#endif
