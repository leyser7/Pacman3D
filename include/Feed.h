#ifndef __FEED_H__
#define __FEED_H__
#include <Player.h>

class Feed: public Player             //Ball
{
    bool isAlive;

public :
    Feed();        //Constructor
    void display();
    bool taken(Player player);
    void set_Alive(bool alive);
    bool isWall(float x , float z, Wall **walls);
};

#endif //__FEED_H__
