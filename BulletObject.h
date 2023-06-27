#ifndef BULLET_OBJECT_H_

//Define for the bullet object

#define BULLET_OBJECT_H_

//The header and library will use

#include "BaseObject.h"

using namespace std;

//Start the define

class BulletObject : public BaseObject
{
public:

	//Tag the type of bullet

	enum BulletType
	{
		NONE = 0,

		LASER = 1,

		SPHERE = 2
	};

	//Initialize

	BulletObject();

	//Destroy

	~BulletObject();

	//Set the type of the bullet

	void set_type(const int& type)
	{
		bullet_type_ = type;
	}

	//Get the type of the bullet

	int get_type() const
	{
		return bullet_type_;
	}

	//Set the size

	void SetWidthHeight(const int& widht, const int& height)
	{
		rect_.w = widht;

		rect_.h = height;
	}

	//Set the cord

	void set_x_val(const int& val)
	{
		x_val_ = val;
	}

	void set_y_val(const int& val)
	{
		y_val_ = val;
	}

	//Get the cord

	int get_x_val() const
	{
		return x_val_;
	}

	int get_y_val() const
	{
		return y_val_;
	}

	//Set the allowance to move

	void set_is_move(bool is_move)
	{
		is_move_ = is_move;
	}

	//Check the allowance to movement

	bool get_is_move() const
	{
		return is_move_;
	}

	//Handle the movement for main object

	void HandleMove(const int& x_border, const int& y_border);

	//Handle the movement for threat object

	void HandleMoveRightToLeft();

	//Handle the action

	void HandleInputAction(SDL_Event events);

private:

	int x_val_;

	int y_val_;

	bool is_move_;

	int bullet_type_;
};
#endif