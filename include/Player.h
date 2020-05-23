/**
 * @file Player.h
 * @author Cristian Camilo Alzate Anzola
 * @brief 
 * @version 0.1
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <Wall.h>

typedef class tagPlayer             //Ball
{
    //float pos_x,pos_y,pos_z;
    //float xVel,yVel,zVel;
    bool isjumping;

public :
    tagPlayer();        //Constructor
    bool handle_input(unsigned char key, Wall **walls);      //Update player pos and do other checkings
    void display();     //Display player on the required position
    void update();      //Update some required variables

    void get_pos(float& x,float& y,float& z);
    void set_pos(float  x,float  y,float  z);
    void set_color(float r, float g, float b);
protected:
    float pos_x,pos_y,pos_z;
    float xVel,yVel,zVel;
    float color_r, color_g, color_b;
}Player;

#endif // __PLAYER_H__
