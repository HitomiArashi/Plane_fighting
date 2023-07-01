//The header and library will use

#include "TextObject.h"

TextObject::TextObject()
{
	//Todo
	rect_.x = 500;
	rect_.y = 10;
	text_color_.r = 0;
	text_color_.g = 0;
	text_color_.b = 0;
}

TextObject::~TextObject()
{
	//Todo
	;
}

//Set color for the text

void TextObject::SetColor(const int& type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0, 0 };
		text_color_ = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255, 255, 255 };
		text_color_ = color;
	}
	else
	{
		SDL_Color color = { 0, 0, 0 };
		text_color_ = color;
	}
}

//Show the text on the screen

void TextObject::CreateGameText(TTF_Font* font, SDL_Surface* des)
{
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	Show(des);
}