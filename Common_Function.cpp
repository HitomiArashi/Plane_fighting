//The header and library will use

#pragma once

#include<iostream>

#include<Windows.h>

#include<string>

#include<SDL_image.h>

#include<SDL.h>

#include "Common_Function.h"

using namespace std;

namespace SDLCommonFunc
{
    //Get the image of the object

    SDL_Surface* LoadImage(string file_path)
    {
        SDL_Surface* load_image = NULL;

        SDL_Surface* optimize_image = NULL;

        load_image = IMG_Load(file_path.c_str());

        if (load_image != NULL)
        {
            optimize_image = SDL_DisplayFormat(load_image);

            SDL_FreeSurface(load_image);

            //Clear the image background color

            if (optimize_image != NULL)
            {
                UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);

                SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
            }
        }

        return optimize_image;
    }

    //Show the object

    void ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y)
    {
        SDL_Rect ofset;

        ofset.x = x;

        ofset.y = y;

        SDL_BlitSurface(scr, NULL, des, &ofset);
    }

    void ApplySurfaceClip(SDL_Surface* scr, SDL_Surface* des, SDL_Rect* clip, int x, int y)
    {
        SDL_Rect ofset;
        ofset.x = x;
        ofset.y = y; SDL_BlitSurface(scr, clip, des, &ofset);
    }

    //Check the collide

    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
    {
        int left_a = object1.x;
        int right_a = object1.x + object1.w;
        int top_a = object1.y;
        int bottom_a = object1.y + object1.h;

        int left_b = object2.x;
        int right_b = object2.x + object2.w;
        int top_b = object2.y;
        int bottom_b = object2.y + object2.h;

        // Case 1: size object 1 < size object 2
        if (left_a > left_b && left_a < right_b)
        {
            if (top_a > top_b && top_a < bottom_b)
            {
                return true;
            }
        }

        if (left_a > left_b && left_a < right_b)
        {
            if (bottom_a > top_b && bottom_a < bottom_b)
            {
                return true;
            }
        }

        if (right_a > left_b && right_a < right_b)
        {
            if (top_a > top_b && top_a < bottom_b)
            {
                return true;
            }
        }

        if (right_a > left_b && right_a < right_b)
        {
            if (bottom_a > top_b && bottom_a < bottom_b)
            {
                return true;
            }
        }

        // Case 2: size object 1 < size object 2
        if (left_b > left_a && left_b < right_a)
        {
            if (top_b > top_a && top_b < bottom_a)
            {
                return true;
            }
        }

        if (left_b > left_a && left_b < right_a)
        {
            if (bottom_b > top_a && bottom_b < bottom_a)
            {
                return true;
            }
        }

        if (right_b > left_a && right_b < right_a)
        {
            if (top_b > top_a && top_b < bottom_a)
            {
                return true;
            }
        }

        if (right_b > left_a && right_b < right_a)
        {
            if (bottom_b > top_a && bottom_b < bottom_a)
            {
                return true;
            }
        }

        // Case 3: size object 1 = size object 2
        if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
        {
            return true;
        }

        return false;
    }

    //int ShowMenu(SDL_Surface* des, TTF_Font* font)
    //{
    //
    //}

    //Clean up the memory

    void CleanUp()
    {
        SDL_FreeSurface(g_screen);

        SDL_FreeSurface(g_bkground);
    }
}
