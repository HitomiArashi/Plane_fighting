#include "PlaneHp.h"

using namespace std;

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

void PlaneHp::AddPos(const int& xpos)
{
	pos_list_.push_back(xpos);
}

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

void PlaneHp::Decrease()
{
	number_ --;
	pos_list_.pop_back();
}