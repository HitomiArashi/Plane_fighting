#pragma once

#ifndef PLANE_HP_H_

#define PLANE_HP_H_

//The header and library will use

#include "BaseObject.h"
#include <vector>

class PlaneHp : public BaseObject
{
public:

	PlaneHp();
	~PlaneHp();
	void SetNumber(const int& num)
	{
		number_ = num;
	}
	void Init();
	void AddPos(const int& xpos);
	void Render(SDL_Surface* des);
	void Decrease();

private:

	int number_;
	std::vector <int>  pos_list_;
};

#endif // !PLANE_HP_H_
