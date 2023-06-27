//The header and library will use

#include "ThreatsObject.h"

using namespace std;

//Initialize the property of the threat object

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH;

	rect_.y = SCREEN_HEIGHT * 0.5;

	rect_.w = WIDTH_THREAT;

	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;

	y_val_ = 0;
}

//Destroy the threat

ThreatObject::~ThreatObject()
{
	if (p_bullet_list_.size() > 0)
	{
		for (int i = 0; i < p_bullet_list_.size(); i++)
		{
			BulletObject* p_bullet = p_bullet_list_.at(i);

			if (p_bullet != NULL)
			{
				delete p_bullet;

				p_bullet = NULL;
			}
		}
		p_bullet_list_.clear();
	}
}

//Initialize the property of the threat bullet

void ThreatObject::InitBullet(BulletObject* p_bullet)
{
	if (p_bullet)
	{
		bool ret = p_bullet->LoadImg(THREAT_BULLET);

		if (ret)
		{
			p_bullet->set_is_move(true);

			p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);

			p_bullet->set_type(BulletObject::SPHERE);

			p_bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);

			p_bullet->set_x_val(THREAT_BULLET_SPEED);

			p_bullet_list_.push_back(p_bullet);
		}
	}
}

//Create the threat bullet

void ThreatObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);

		if (p_bullet)
		{
			if (p_bullet->get_is_move())
			{
				p_bullet->Show(des);

				p_bullet->HandleMoveRightToLeft();
			}

			else
			{
				p_bullet->set_is_move(true);

				p_bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
			}
		}
	}
}

//Handle the threat movement

void ThreatObject::HandleMove(const int& x_bordr, const int& y_bordr)
{
	rect_.x -= x_val_;

	if (rect_.x < 0) 
	{
		rect_.x = SCREEN_WIDTH;

		//Set the random spawn for the threat

		int rand_y = rand() % VAL_OFFSET_START_POS_THREATS;

		if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = SCREEN_HEIGHT * 0.3;
		}

		rect_.y = rand_y;
	}
}

//Handle other action (if it is available)

void ThreatObject::HandleInputAction(SDL_Event events)
{
	//Todo
	;
}

void ThreatObject::Reset(const int& xborder)
{
	rect_.x = xborder;

	//Set the random spawn for the threat

	int rand_y = rand() % VAL_OFFSET_START_POS_THREATS;

	if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = SCREEN_HEIGHT * 0.3;
	}

	rect_.y = rand_y;

	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			ResetBullet(p_bullet);
		}
	}
}

void ThreatObject::ResetBullet(BulletObject* p_bullet)
{
	p_bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
}
