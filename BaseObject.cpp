//The header and library will use

#pragma once

#include "BaseObject.h"

#include "Common_Function.h"

using namespace std;

using namespace SDLCommonFunc;

//Initialize the property of the base object

BaseObject::BaseObject()
{
	rect_.x = 0;

	rect_.y = 0;

	p_object_ = NULL;
}

//Destroy the object

BaseObject::~BaseObject()
{
	if (p_object_ != NULL) 
	{
		SDL_FreeSurface(p_object_);
	}
}

//Load the object image

bool BaseObject::LoadImg(const string file_name)
{
	p_object_ = LoadImage(file_name);

	if (p_object_ == NULL)
	{
		return false;
	}

	return true;
}

//Show the object

void BaseObject::Show(SDL_Surface* des)
{
	if (p_object_ != NULL) 
	{
		ApplySurface(p_object_, des, rect_.x, rect_.y);
	}
}
