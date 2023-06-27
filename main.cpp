//The header and library will use

#include <windows.h>

#include "Common_Function.h"

#include "MainObject.h"

#include "ThreatsObject.h"

#include "ExplosionObject.h"

#include "PlaneHp.h"

#undef main

using namespace std;

//Check initialization

bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }

    g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if (g_screen == NULL)
    {
        return false;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }

    //Read file wav adio

    if (g_sound_exp == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL)
    {
        return false;
    }

    return true;
}

//Using 1 single looping background
//Better: Easy; can be looped infinitively; background just need to be as big as
//screen.
//Worse: Looped backgound, so it is not intersting, diversy and lively; use 1 code
//2 times, have to calculate carefully to connect the looped pic.

void Background_Moving_Type_1(int& bkgn_x)
{
    bkgn_x -= SCREEN_SPEED;

    SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);

    SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x + SCREEN_WIDTH, 0);

    if (bkgn_x <= -SCREEN_WIDTH)
    {
        bkgn_x = 0;
    }
}

//Using 1 single very long background
//Better: Interesting and lively background; using code 1 time only.
//Worse: Have to design the background => take time, complicated;  have to calculate
//carefully the place to spawn the threat.

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
            SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
        }
    }
}

int main(int arc, char* argv[])
{
    int bkgn_x = 0;

    bool is_run_screen = true;

    //Initialize the property
    
    bool is_quite = false;
    
    if (Init() == false)
    {
        return 0;
    }

    //Make plane HP

    PlaneHp plane_hp;

    plane_hp.Init();

    //Load background

    g_bkground = SDLCommonFunc::LoadImage(BACKGROUND_FOR_TYPE_2);

    if (g_bkground == NULL)
    {
        return 0;
    }

    SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);

    //Make main object

    MainObject* plane = new MainObject;

    plane->SetRect(POS_START_MAIN_X, POS_START_MAIN_Y);

    bool ret = plane->LoadImg(MAIN_IMAGE);

    if (ret == false)
    {
        return 0;
    }

    //Init explosion

    Explosion exp_main;

    ret = exp_main.LoadImg("exp_main.png");

    exp_main.set_clip();

    if (ret == NULL)
    {
        return 0;
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
                return 0;
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

                bool is_col = SDLCommonFunc::CheckCollision(plane->GetRect(), p_threat->GetRect());

                if (is_col)
                {
                    Mix_PlayChannel(-1, g_sound_exp, 0); //Display the sound

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
                            return 0;
                        }
                    }
                    //Delete all memory
                    
                    delete[] p_threats;

                    SDLCommonFunc::CleanUp();

                    SDL_Quit();

                    return 1;
                }

                //Check the collision between main bullet and threat

                vector<BulletObject*> p_bullet_list = plane->GetBulletList();

                for (int im = 0; im < p_bullet_list.size(); im++)
                {
                    BulletObject* p_bullet = p_bullet_list.at(im);

                    if (p_bullet != NULL)
                    {
                        bool ret_col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());

                        if (ret_col)
                        {
                            Mix_PlayChannel(-1, g_sound_exp, 0); //Display the sound

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
                                    return 0;
                                }
                            }
                            //Reset the threat

                            p_threat->Reset(SCREEN_WIDTH + tt * VAL_OFFSET_START_POS_THREATS);

                            plane->RemoveBullet(im);
                        }
                    }
                }

                //Check the collision between main and threat bullet

                vector<BulletObject*> bullet_list = p_threat->GetBulletList();

                for (int im = 0; im < bullet_list.size(); im++)
                {
                    BulletObject* threat_bullet = bullet_list.at(im);

                    if (threat_bullet != NULL)
                    {
                        bool ret_col = SDLCommonFunc::CheckCollision(plane->GetRect(), threat_bullet->GetRect());

                        if (ret_col)
                        {
                            Mix_PlayChannel(-1, g_sound_exp, 0); //Display the sound

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
                                    return 0;
                                }
                            }
                            //Delete all memory

                            delete[] p_threats;

                            SDLCommonFunc::CleanUp();

                            SDL_Quit();

                            return 1;
                        }
                    }
                }
            }
        }

        //Update screen
        
        if (SDL_Flip(g_screen) == -1)
        {
            return 0;
        }
    }

    //Delete all memory

    delete[] p_threats;

    SDLCommonFunc::CleanUp();

    SDL_Quit();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
