#ifndef __MYTYPES_H__
#define __MYTYPES_H__
#include "Player.h"
/** All the States the game can be in.. */
typedef enum tagGameStates
{
   GSMenu           = 1,
   GSPlaying        = 2,
   GSControls       = 3,
   GSCredits        = 4,
   GSSplashWelcome  = 5,
   GSSplashEnd      = 6,
   GSQuit           = 7

}GameStates;

/* Some error Codes used in our game.. */
typedef enum tagGameErrors
{
    GE_NO_ERROR =0,
    GE_CHARSET_ERROR =1,
 /*   GE_SDL_NOT_SETUP =20,
    GE_VIDEO_NOT_INIT =21,
    GE_IMAGES_NOT_FOUND =31,
    GE_MAP_NOT_FOUND  = 40,
    GE_MIXER_NOT_INIT = 50,
    GE_MUSIC_NOT_FOUND = 23,
    GE_TTF_NOT_INIT = 60,
    GE_FONT_NOT_FOUND =61
    */
}GameErrors;



typedef class tagArrow
{
    float pos_x,pos_y,pos_z;
    float xVel,yVel,zVel;
    int   my_lane;
    bool  isAlive;
public:
    tagArrow(int lane);

    //Some getters and setters
    bool get_Alive();
    void get_pos(float& x,float& y,float& z);
    int  get_lane();
    void set_pos(float x,float y,float z,bool bound_to_lane = true);
    void set_vel(float xv,float yv,float zv);
    void set_Alive(bool iA);
    void set_lane(int lane);

    void display();
    void update();

    // return true if arrow collided with player
    bool isCollided(tagPlayer& p);

}Arrow;


typedef struct tagCamera
{
    float x,y,z;
    float angle;
    float a_x,a_y,a_z;                // angle around which axis
    tagCamera();
}Camera;

typedef class tagDonut
{
    float pos_x,pos_y,pos_z;
    bool isAlive;
public:
    tagDonut();
    bool taken(Player player);
    void display();

    // Some getters and setters
    void set_pos(float x,float y,float z);
    void set_Alive(bool alive);
    bool get_Alive();
    void get_pos(float& x,float& y,float& z);
}Donut;

#endif // __MYTYPES_H__
