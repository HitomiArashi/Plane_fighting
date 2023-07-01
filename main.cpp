//The header and library will use

#include <windows.h>
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PlaneHp.h"
#include "TextObject.h"
#undef main

using namespace SDLCommonFunc;

//Font of the text shown

TTF_Font* g_font_text = NULL;
TTF_Font* g_font_menu = NULL;
TTF_Font* g_font_over = NULL;

//Check initialization

bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == GA_FAILED)
    {
        return false;
    }
    g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (g_screen == NULL)
    {
        return false;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == GA_FAILED)
    {
        return false;
    }

    //Read file wav adio

    g_sound_bullet[0] = Mix_LoadWAV("Laser.wav");
    g_sound_bullet[1] = Mix_LoadWAV("Fire.wav");
    g_sound_exp = Mix_LoadWAV("Explo.wav");
    if (g_sound_exp == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL)
    {
        return false;
    }
    if (TTF_Init() == GA_FAILED)
    {
        return false;
    }

    //Read file ttf text font

    g_font_text = TTF_OpenFont("PTN77F.ttf", 20);
    g_font_menu = TTF_OpenFont("PTN77F.ttf", 50);
    g_font_over = TTF_OpenFont("PTN77F.ttf", 50);
    if (g_font_text == NULL || g_font_menu == NULL || g_font_over == NULL)
    {
        return false;
    }
    return true;
}

//Clear all memory of the current game

void endgame(ThreatObject*& p_threats)
{
    delete[] p_threats;
    CleanUp();
    SDL_Quit();
}

//Game over screen

bool gameOver(Uint32& time_selected, unsigned int& mark_value, unsigned int& death_time, PlaneHp& plane_hp, MainObject*& plane, ThreatObject*& p_threats)
{
    int ret_over = ShowGameOver(g_screen, g_font_over);
    if (ret_over == 1) //Exit game
    {
        return true;
    }
    else //Reset every stuff and retry
    {
        //Reset main object
        
        plane = new MainObject;
        plane->SetRect(POS_START_MAIN_X, POS_START_MAIN_Y);
        bool ret = plane->LoadImg(MAIN_IMAGE);
        if (ret == false)
        {
            return true;
        }

        //Reset threats object

        p_threats = new ThreatObject[NUM_THREAT];
        for (int t = 0; t < NUM_THREAT; t++)
        {
            ThreatObject* p_threat = (p_threats + t);
            if (p_threat)
            {
                ret = p_threat->LoadImg(THREAT_IMAGE);
                if (ret == false)
                {
                    return true;
                }

                //Set random spawn position for the threat objects

                int rand_y = rand() % VAL_OFFSET_START_POS_THREATS;
                if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
                {
                    rand_y = SCREEN_HEIGHT * 0.3;
                }
                p_threat->SetRect(SCREEN_WIDTH + t * VAL_OFFSET_START_POS_THREATS, rand_y);
                p_threat->set_x_val(THREAT_SPEED);

                //Make threat objects shoot bullet

                BulletObject* p_bullet = new BulletObject();
                p_threat->InitBullet(p_bullet);
            }
        }

        //Reset hp

        plane_hp.Init();

        //Reset other stuff

        death_time = 0;
        mark_value = 0;
        time_selected = SDL_GetTicks();
        return false;
    }
}

/*
Using 1 single looping background
Better: Easy; can be looped infinitively; background just need to be as big as
screen.
Worse: Looped backgound, so it is not intersting, diversy and lively; use 1 code
2 times, have to calculate carefully to connect the looped pic.
*/

void Background_Moving_Type_1(int& bkgn_x)
{
    bkgn_x -= SCREEN_SPEED;
    ApplySurface(g_bkground, g_screen, bkgn_x, 0);
    ApplySurface(g_bkground, g_screen, bkgn_x + SCREEN_WIDTH, 0);
    if (bkgn_x <= -SCREEN_WIDTH)
    {
        bkgn_x = 0;
    }
}

/*
Using 1 single very long background
Better: Interesting and lively background; using code 1 time only.
Worse: Have to design the background => take time, complicated;  have to calculate
carefully the place to spawn the threat.
*/

void Background_Moving_Type_2(int& bkgn_x, bool &is_run_screen)
{
    if(is_run_screen == true)
    {
        bkgn_x -= SCREEN_SPEED;
        if (bkgn_x <= - (BACKGROUND_WIDTH_TYPE_2 - SCREEN_WIDTH))
        {
            is_run_screen = false;
        }
        else
        {
            ApplySurface(g_bkground, g_screen, bkgn_x, 0);
        }
    }
}

//Using 1 background only, no moving.

void Background_Standing(int& bkgn_x, bool& is_run_screen)
{
    is_run_screen = false;
    ApplySurface(g_bkground, g_screen, bkgn_x, 0);
}

int main(int arc, char* argv[])
{
    int bkgn_x = 0;
    bool is_run_screen = true;

    //Initialize the property
    
    bool is_quite = false;
        if (Init() == false)
    {
        return GA_FAILED;
    }

    //Make plane HP

    PlaneHp plane_hp;
    plane_hp.Init();

    //Set the timer color

    TextObject game_time;
    game_time.SetColor(TextObject::BLACK_TEXT);

    //Set the text color

    TextObject mark_game;
    mark_game.SetColor(TextObject::BLACK_TEXT);

    //Load background

    g_bkground = LoadImage(BACKGROUND_FOR_TYPE_2);
    if (g_bkground == NULL)
    {
        return GA_FAILED;
    }
    ApplySurface(g_bkground, g_screen, 0, 0);

    //Make main object

    MainObject* plane = new MainObject;
    plane->SetRect(POS_START_MAIN_X, POS_START_MAIN_Y);
    bool ret = plane->LoadImg(MAIN_IMAGE);
    if (ret == false)
    {
        return GA_FAILED;
    }

    //Init explosion

    Explosion exp_main;
    ret = exp_main.LoadImg("exp_main.png");
    exp_main.set_clip();
    if (ret == NULL)
    {
        return GA_FAILED;
    }

    //Make threat objects

    ThreatObject* p_threats = new ThreatObject[NUM_THREAT];
    for (int t = 0; t < NUM_THREAT; t++)
    {
        ThreatObject* p_threat = (p_threats + t);
        if (p_threat)
        {
            ret = p_threat->LoadImg(THREAT_IMAGE);
            if (ret == false)
            {
                return GA_FAILED;
            }

            //Set random spawn position for the threat objects

            int rand_y = rand() % VAL_OFFSET_START_POS_THREATS;
            if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
            {
                rand_y = SCREEN_HEIGHT * 0.3;
            }
            p_threat->SetRect(SCREEN_WIDTH + t * VAL_OFFSET_START_POS_THREATS, rand_y);
            p_threat->set_x_val(THREAT_SPEED);

            //Make threat objects shoot bullet

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet);
        }
    }

    //Run game

    unsigned int death_time = 0;
    unsigned int mark_value = 0;
    Uint32 time_selected = 0;
    int ret_menu = ShowMenu(g_screen, g_font_menu);
    if (ret_menu == 1)
    {
        is_quite = true;
    }
    else
    {
        time_selected = SDL_GetTicks(); //Get the time start game
    }
    while (is_quite == false)
    {
        //Quit action
        
        while (SDL_PollEvent(&g_even))
        {
            if (g_even.type == SDL_QUIT)
            {
                is_quite = true;
                break;
            }
            else if (g_even.type == SDL_KEYDOWN)
            {
                if (g_even.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_quite = true;
                    break;
                }
            }
            plane->HandleInputAction(g_even, g_sound_bullet);
        }

        //Apply Background: Choosing style to move the background or keep the
        //background standing.

        Background_Moving_Type_1(bkgn_x);

        //Show plane HP

        plane_hp.Render(g_screen);

        //Implement Main Object

        plane->HandleMove();
        plane->Show(g_screen);
        plane->MakeBullet(g_screen);

        //Implement Threats Object

        for (int tt = 0; tt < NUM_THREAT; tt++)
        {
            ThreatObject* p_threat = (p_threats + tt);
            if (p_threat)
            {
                p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

                //Check collision between main and threats

                bool is_col = CheckCollision(plane->GetRect(), p_threat->GetRect());
                if (is_col)
                {
                    Mix_PlayChannel(-1, g_sound_exp, 0); //Display the sound
                    death_time++;
                    for (int ex = 0; ex < 4; ex++)
                    {
                        //Take the cord

                        int x_pos = (plane->GetRect().x + plane->GetRect().w * 0.5) - EXP_WIDTH * 0.5;
                        int y_pos = (plane->GetRect().y + plane->GetRect().h * 0.5) - EXP_HEIGHT * 0.5;

                        //Show the explosion

                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.ShowEx(g_screen);
                        SDL_Delay(100);

                        //Update screen

                        if (SDL_Flip(g_screen) == -1)
                        {
                            return GA_FAILED;
                        }
                    }

                    //Run while hp is still higher than 0

                    if (death_time < HEALTH_POINT)
                    {
                        SDL_Delay(1000);
                        plane->SetRect(POS_START_MAIN_X, POS_START_MAIN_Y); //Reset the plane
                        plane_hp.Decrease();
                        plane_hp.Render(g_screen);
                        if (SDL_Flip(g_screen) == -1)
                        {
                            endgame(p_threats);
                            return GA_FAILED;
                        }
                    }
                    else
                    {
                        //Run the game over screen

                        if (gameOver(time_selected, mark_value, death_time, plane_hp, plane, p_threats) == true)
                        {
                            endgame(p_threats);
                            return GA_FAILED;
                        }
                    }
                }

                //Check the collision between main bullet and threat

                std::vector<BulletObject*> p_bullet_list = plane->GetBulletList();
                for (int im = 0; im < p_bullet_list.size(); im++)
                {
                    BulletObject* p_bullet = p_bullet_list.at(im);
                    if (p_bullet != NULL)
                    {
                        bool ret_col = CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
                        if (ret_col)
                        {
                            Mix_PlayChannel(-1, g_sound_exp, 0); //Display the sound
                            mark_value++;                            
                            for (int ex = 0; ex < 4; ex++)
                            {
                                //Take the cord

                                int x_pos = p_bullet->GetRect().x - EXP_WIDTH * 0.5;
                                int y_pos = p_bullet->GetRect().y - EXP_HEIGHT * 0.5;

                                //Show the explosion

                                exp_main.set_frame(ex);
                                exp_main.SetRect(x_pos, y_pos);
                                exp_main.ShowEx(g_screen);
                                SDL_Delay(100);

                                //Update screen

                                if (SDL_Flip(g_screen) == -1)
                                {
                                    return GA_FAILED;
                                }
                            }
                            //Reset the threat

                            p_threat->Reset(SCREEN_WIDTH + tt * VAL_OFFSET_START_POS_THREATS);
                            plane->RemoveBullet(im);
                        }
                    }
                }

                //Check the collision between main and threat bullet

                std::vector<BulletObject*> bullet_list = p_threat->GetBulletList();
                for (int im = 0; im < bullet_list.size(); im++)
                {
                    BulletObject* threat_bullet = bullet_list.at(im);
                    if (threat_bullet != NULL)
                    {
                        bool ret_col = CheckCollision(plane->GetRect(), threat_bullet->GetRect());
                        if (ret_col)
                        {
                            Mix_PlayChannel(-1, g_sound_exp, 0); //Display the sound
                            death_time++;
                            for (int ex = 0; ex < 4; ex++)
                            {
                                //Take the cord

                                int x_pos = (plane->GetRect().x + plane->GetRect().w * 0.5) - EXP_WIDTH * 0.5;
                                int y_pos = (plane->GetRect().y + plane->GetRect().h * 0.5) - EXP_HEIGHT * 0.5;

                                //Show the explosion

                                exp_main.set_frame(ex);
                                exp_main.SetRect(x_pos, y_pos);
                                exp_main.ShowEx(g_screen);
                                SDL_Delay(100);

                                //Update screen

                                if (SDL_Flip(g_screen) == -1)
                                {
                                    return GA_FAILED;
                                }
                            }

                            //Run while hp is still higher than 0

                            if (death_time < HEALTH_POINT)
                            {
                                SDL_Delay(1000);
                                plane->SetRect(POS_START_MAIN_X, POS_START_MAIN_Y); //Reset the plane
                                plane_hp.Decrease();
                                plane_hp.Render(g_screen);
                                if (SDL_Flip(g_screen) == -1)
                                {
                                    endgame(p_threats);
                                    return GA_FAILED;
                                }
                            }
                            else
                            {
                                //Run the game over screen

                                if (gameOver(time_selected, mark_value, death_time, plane_hp, plane, p_threats) == true)
                                {
                                    endgame(p_threats);
                                    return GA_FAILED;
                                }
                            }
                        }
                    }
                }
            }
        }

        //Show time for game

        std::string str_time = "Time: ";
        Uint32 time_val = (SDL_GetTicks() - time_selected) / 1000;
        std::string str_val = std::to_string(time_val);
        str_time += str_val;
        game_time.SetText(str_time);
        game_time.SetRect(SCREEN_WIDTH - 200, 10);
        game_time.CreateGameText(g_font_text, g_screen);

        //Show mark value to screen

        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Mark: ");
        strMark += val_str_mark;
        mark_game.SetText(strMark);
        mark_game.SetRect(500, 10);
        mark_game.CreateGameText(g_font_text, g_screen);

        //Update screen
        
        if (SDL_Flip(g_screen) == -1)
        {
            return GA_FAILED;
        }
    }

    //Delete all memory

    endgame(p_threats);
    return GA_FAILED;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
