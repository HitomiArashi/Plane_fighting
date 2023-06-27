//The header and library will use

#include "BulletObject.h"

using namespace std;

//Initialize the property of the bullet

BulletObject::BulletObject()
{
	rect_.x = 0;

	rect_.y = 0;

	x_val_ = 0;

	y_val_ = 0;

	is_move_ = false;

	bullet_type_ = NONE;
}

//Destroy the bullet

BulletObject::~BulletObject()
{
	//Todo
	;
}

//Handle the movement for the main bullet

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x += x_val_;

	if (rect_.x > x_border) 
	{
		is_move_ = false;
	}
}

//Handle the movement for the threats bullet

void BulletObject::HandleMoveRightToLeft()
{
	rect_.x -= x_val_;

	if (rect_.x < 0)
	{
		is_move_ = false;
	}
}

//Handle other action (if it is available)

void BulletObject::HandleInputAction(SDL_Event events)
{
	//Todo
	;
}
