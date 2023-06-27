#pragma once

#ifndef TEXT_OBJECT_H_

#include "BaseObject.h"

#include <SDL_ttf.h>

#include <string>

using namespace std;

#define TEXT_OBJECT_H_

class TextObject : public BaseObject
{
public:

	enum TextColor
	{
		RED_TEXT = 0,

		WHITE_TEXT = 1,

		BLACK_TEXT = 2,
	};

	TextObject();
	
	~TextObject();

	void SetText(const string& text)
	{
		str_val_ = text;
	}

	void SetColor(const int& type);

	void CreateGameText(TTF_Font* font, SDL_Surface* des);

private:

	string str_val_;
	SDL_Color text_color_;
};

#endif // !TEXT_OBJECT_H_
