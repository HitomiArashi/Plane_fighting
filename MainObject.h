#ifndef MAIN_OBJECT_H_

//Define for the main object

#define MAIN_OBJECT_H_

//The header and library will use

#include "Common_Function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

//Start the define

class MainObject : public BaseObject
{
public:

	//Initialize

	MainObject();

	//Destroy

	~MainObject();

	//Creat the bullet

	void MakeBullet(SDL_Surface* g_scren);

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

	//Handle all action

	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);

	//Handle the movement of the object

	void HandleMove();
	void RemoveBullet(const int& idx);

private:

	int x_val_;
	int y_val_;
	std::vector <BulletObject*> p_bullet_list_;

};
#endif
