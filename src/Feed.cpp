#include "Feed.h"
#include "consts.h"
#include <iostream>

Feed::Feed()
{
    isAlive = false;
}
/*
bool Feed::get_Alive()
{
    return isAlive;
}
x
void Feed::get_pos(float &x, float &y, float &z)
{
    x = pos_x;
    y = pos_y;
    z = pos_z;
}


void Feed::set_pos(float x, float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;
}
*/
void Feed::set_Alive(bool alive)
{
    isAlive = alive;
}

bool Feed::taken(Player player)
{
    if (!isAlive)
        return false;
    float x, y, z;
    player.get_pos(x, y, z);
    float d = dist(pos_x, pos_y, pos_z, x, y, z);
    if (d <= (P_RADIUS + D_OUT_RADIUS))
    {
        isAlive = false;
        return true;
    }
    return false;
}

void Feed::display()
{
    if (!isAlive)
        return;
    glPushMatrix();
    glColor3f(CLR_FEED_R, CLR_FEED_G, CLR_FEED_B);
    // mejor endendimiento
    glTranslatef(pos_z, pos_y, pos_x);
    glTranslatef(0, FEED_RADIUS / 2, 0);
    glutSolidSphere(FEED_RADIUS, P_SLICES, P_STACKS);
    glPopMatrix();
}

bool Feed::isWall(float x, float z, Wall **walls)
{
    float pos_x = x;
    float pos_z = z;
    bool isObject = false;
    float w_x, w_z, w_w, w_h;
    for (size_t i = 0; i < MAX_WALL; i++)
    {
        walls[i]->get(w_x, w_z, w_w, w_h);
        if (pos_z<(w_z + w_h + P_RADIUS) & pos_z>(w_z - P_RADIUS) & pos_x > (w_x - P_RADIUS) & pos_x < (w_x + w_w + P_RADIUS))
        {
            isObject = true;
        }

        if (pos_x > (w_x - P_RADIUS) & pos_x<(w_x + w_w - P_RADIUS) & pos_z>(w_z - P_RADIUS) & pos_z < (w_z + w_h + P_RADIUS))
        {
            isObject = true;
        }
    }
    if (pos_x > -WALL_W*5*2 &pos_x< WALL_W*4*2 & pos_z> -WALL_W*2*2  & pos_z <  WALL_W*3*2 )
    {
        isObject = true;
    }
    if (pos_x > WALL_W*5*2 & pos_z> -WALL_W*2*2  & pos_z <  WALL_W*3*2 )
    {
        isObject = true;
    }
      if (pos_x < -WALL_W*6*2 & pos_z> -WALL_W*2*2  & pos_z <  WALL_W*3*2 )
    {
        isObject = true;
    }
    return isObject;
}