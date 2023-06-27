#pragma once

#ifndef PLANE_HP_H_

#define PLANE_HP_H_

#include "BaseObject.h"

#include <vector>

using namespace std;

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

	vector <int>  pos_list_;
};

#endif // !PLANE_HP_H_
