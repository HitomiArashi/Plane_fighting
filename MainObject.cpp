//The header and library will use

#include "MainObject.h"

//Initialize the property of the main object

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

//Destroy the object

MainObject::~MainObject()
{
	//To do
	;
}

//Creat bullet for the main object

void MainObject::MakeBullet(SDL_Surface* g_scren)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);

		//Check if the bullet is available

		if (p_bullet != NULL)
		{
			//Check if it is allowed to move

			if (p_bullet->get_is_move())
			{
				p_bullet->Show(g_scren);
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				if (p_bullet != NULL)
				{
					p_bullet_list_.erase(p_bullet_list_.begin());
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}

//Handle all action

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2])
{
	//Handle the input for movement

	if (events.type == SDL_KEYDOWN) //Moving
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: //Button up arrow
			y_val_ -= HEIGHT_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_w: //Button "w"
			y_val_ -= HEIGHT_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_DOWN: //Button down arrow
			y_val_ += HEIGHT_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_s: //Button "s"
			y_val_ += HEIGHT_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_LEFT: //Button left arrow
			x_val_ -= WIDTH_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_a: //Button "a"
			x_val_ -= WIDTH_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_RIGHT: //Button right arrow
			x_val_ += WIDTH_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_d: //Button "d"
			x_val_ += WIDTH_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		}
	}
	else if (events.type == SDL_KEYUP) //Stop moving
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: //Button up arrow
			y_val_ += HEIGHT_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_w: //Button "w"
			y_val_ += HEIGHT_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_DOWN: //Button down arrow
			y_val_ -= HEIGHT_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_s: //Button "s"
			y_val_ -= HEIGHT_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_LEFT: //Button left arrow
			x_val_ += WIDTH_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_a: //Button "a"
			x_val_ += WIDTH_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_RIGHT: //Button right arrow
			x_val_ -= WIDTH_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		case SDLK_d: //Button "d"
			x_val_ -= WIDTH_MAIN_OBJECT / MAIN_OBJECT_SPEED;
			break;
		}
	}

	//Handle the input for shooting

	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		BulletObject* p_bullet = new BulletObject();

		//Set the bullet is laser

		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_bullet->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_bullet->LoadImg(MAIN_BULLET_LASER);
			p_bullet->set_type(BulletObject::LASER);
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}

		//Set the bullet is sphere

		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_bullet->LoadImg(MAIN_BULLET_SPHERE);
			p_bullet->set_type(BulletObject::SPHERE);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}

		//Show the bullet

		p_bullet->SetRect(this->rect_.x + this->rect_.w - 20, this->rect_.y + this->rect_.h * 0.73);
		p_bullet->set_is_move(true);
		p_bullet->set_x_val(MAIN_BULLET_SPEED);
		p_bullet_list_.push_back(p_bullet);
	}

	else if (events.type == SDL_MOUSEBUTTONUP)
	{

	}

	else
	{
		;//
	}
}

//Handle the movement

void MainObject::HandleMove()
{
	rect_.x += x_val_;
	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
	{
		rect_.x -= x_val_;
	}
	rect_.y += y_val_;
	if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 0)
	{
		rect_.y -= y_val_;
	}
}

//Remove the bullet

void MainObject::RemoveBullet(const int& idx)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		if (idx < p_bullet_list_.size())
		{
			BulletObject* p_bullet = p_bullet_list_.at(idx);
			p_bullet_list_.erase(p_bullet_list_.begin() + idx);
			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}
}
