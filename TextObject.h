#pragma once

#ifndef TEXT_OBJECT_H_

//The header and library will use

#include "BaseObject.h"
#include <SDL_ttf.h>
#include <string>

#define TEXT_OBJECT_H_

class TextObject : public BaseObject
{
public:

	//Color of the text

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};
	TextObject();
	~TextObject();

	//Set the text wil be show

	void SetText(const std::string& text)
	{
		str_val_ = text;
	}

	//Set the color of the text

	void SetColor(const int& type);

	//Show the text

	void CreateGameText(TTF_Font* font, SDL_Surface* des);

private:

	std::string str_val_;
	SDL_Color text_color_;
};

#endif // !TEXT_OBJECT_H_
