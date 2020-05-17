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
protected:
    float pos_x,pos_y,pos_z;
    float xVel,yVel,zVel;

}Player;

#endif // __PLAYER_H__
