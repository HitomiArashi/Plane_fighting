#ifndef COMMON_FUNCTION_H

//All the command that will be used commonly in project

#define COMMON_FUNCTION_H

//The header and library will use

#include<iostream>
#include<Windows.h>
#include<string>
#include<SDL_image.h>
#include<SDL.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

//Infomation of the input and output stuff

#define GA_FAILED -1

//Screen

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Surface* g_menu = NULL;
static SDL_Surface* g_over = NULL;
static SDL_Event g_even;
const std::string BACKGROUND_FOR_TYPE_1 = "bg1200.png";
const int BACKGROUND_WIDTH_TYPE_1 = 1200;
const int BACKGROUND_HEIGHT_TYPE_1 = 600;
const std::string BACKGROUND_FOR_TYPE_2 = "bg4800.png";
const int BACKGROUND_WIDTH_TYPE_2 = 4800;
const int BACKGROUND_HEIGHT_TYPE_2 = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int SCREEN_SPEED = 2;

//Main

const std::string MAIN_IMAGE = "plane_fly.png";
const int WIDTH_MAIN_OBJECT = 77;
const int HEIGHT_MAIN_OBJECT = 52;
const int POS_START_MAIN_X = 100;
const int POS_START_MAIN_Y = 200;
const int MAIN_OBJECT_SPEED = 10;
const int HEALTH_POINT = 3;

//Threat

const std::string THREAT_IMAGE = "af1.png";
const int WIDTH_THREAT = 80;
const int HEIGHT_THREAT = 33;
const int THREAT_SPEED = 5;
const int NUM_THREAT = 3;
const int VAL_OFFSET_START_POS_THREATS = 400;
const int UNDER_LIMIT_THREAT = 200;

//Bullet

const int MAIN_BULLET_SPEED = 20;
const std::string MAIN_BULLET_SPHERE = "sphere.png";
const int WIDTH_SPHERE = 10;
const int HEIGHT_SPHERE = 10;
const std::string MAIN_BULLET_LASER = "laser.png";
const int WIDTH_LASER = 35;
const int HEIGHT_LASER = 5;
const int THREAT_BULLET_SPEED = 10;
const std::string THREAT_BULLET = "sphere2.png";

//Sound

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp;
static Mix_Chunk* g_sound_ex_main = NULL;

//Command will be used

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* scr, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void CleanUp();
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	int ShowGameOver(SDL_Surface* des, TTF_Font* font);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}

#endif
