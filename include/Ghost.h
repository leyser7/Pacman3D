/**
 * @file Ghost.h
 * @author Cristian Camilo Alzate Anzola
 * @brief 
 * @version 0.1
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __GHOST_H__
#define __GHOST_H__
#include <Player.h>

class Ghost: public Player             //Ball
{
    bool  isAlive;
    unsigned char direction[4]; 
    int n_dir;

public :
    Ghost();        //Constructor
    bool isCollided(tagPlayer &p);
    void set_Alive(bool iA);
    bool get_Alive();
    void display();
    void update(tagPlayer &p, Wall **walls, bool attack);
    bool isObstacle(unsigned char key, Wall **walls);
};

#endif //__GHOST_H__
