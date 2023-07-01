#ifndef BASE_OBJECT_H_

//Define for the base

#define BASE_OBJECT_H_

//The header and library will use

#include <SDL.h>
#include "Common_Function.h"

//Start the define

class BaseObject
{
public:

	//Initialize

	BaseObject();

	//Destroy

	~BaseObject();

	//Get the object

	SDL_Surface* GetObject()
	{
		return p_object_;
	}

	//Load the object image

	bool LoadImg(const std::string file_name);

	//Set the cord to spawn

	void SetRect(const int& x, const int& y)
	{
		rect_.x = x, rect_.y = y;
	}

	//Get the cord

	SDL_Rect GetRect() const
	{
		return rect_;
	}

	//Show the object

	void Show(SDL_Surface* des);

protected:

	SDL_Rect rect_;
	SDL_Surface* p_object_;

};
#endif
