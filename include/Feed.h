/**
 * @file Feed.h
 * @author Cristian Camilo Alzate Anzola
 * @brief 
 * @version 0.1
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __FEED_H__
#define __FEED_H__
#include <Player.h>

class Feed : public Player //Ball
{

    bool isAlive;

public:
    Feed(); //Constructor
    void display();
    bool taken(Player player);
    void set_Alive(bool alive);
    bool isWall(float x, float z, Wall **walls);
};

#endif //__FEED_H__
