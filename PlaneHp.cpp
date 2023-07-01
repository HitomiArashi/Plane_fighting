//The header and library will use

#include "PlaneHp.h"

PlaneHp::PlaneHp()
{
	//Todo
	;
}

PlaneHp :: ~PlaneHp()
{
	//Todo
	;
}

//Initialize the heart shown

void PlaneHp::Init()
{
	LoadImg("heart.png");
	number_ = HEALTH_POINT;
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	for (int i = 0; i < number_; i++)
	{
		AddPos(20 + i * 25);
	}
}

//Add the position for each heart

void PlaneHp::AddPos(const int& xpos)
{
	pos_list_.push_back(xpos);
}

//Show the heart

void PlaneHp::Render(SDL_Surface* des)
{
	if (number_ == pos_list_.size())
	{
		for (int li = 0; li < pos_list_.size(); li++)
		{
			rect_.x = pos_list_.at(li);
			Show(des);
		}
	}
}

//Decrease the heart when attacked

void PlaneHp::Decrease()
{
	number_ --;
	pos_list_.pop_back();
}