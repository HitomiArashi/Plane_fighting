#ifndef THREATES_OBJECT_H_

//Define for threat object

#define THREATES_OBJECT_H_

//The header and library will use

#include "Common_Function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

//Start the define

class ThreatObject : public BaseObject
{
public:

	//Initialize

	ThreatObject();

	//Destroy

	~ThreatObject();

	//Initialize the bullet

	void InitBullet(BulletObject* p_bullet);

	//Create the bullet

	void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit);

	//Set the list of the bullet

	void SetBulletList(std::vector <BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}

	//List of the bullet

	std::vector <BulletObject*> GetBulletList() const
	{
		return p_bullet_list_;
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

	//Handle the movement of the threat

	void HandleMove(const int& x_bordr, const int& y_bordr);

	//Handle other action

	void HandleInputAction(SDL_Event events);
	void Reset(const int& xborder);
	void ResetBullet(BulletObject* p_bullet);

private:

	int x_val_;
	int y_val_;
	std::vector <BulletObject*> p_bullet_list_;
};
#endif