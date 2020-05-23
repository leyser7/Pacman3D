#include "Ghost.h"
#include "Player.h"
#include "consts.h"
#include <iostream>

//Just construct the player at its start position
Ghost::Ghost()
{
    isAlive = false;
    direction[0] = 'w';
    direction[1] = 's';
    direction[2] = 'a';
    direction[3] = 'd';
    n_dir = 0;
    xVel = G_X_VEL;
    yVel = G_Y_VEL_MAX;
    zVel = G_Z_VEL;
}

bool Ghost::isCollided(tagPlayer &p)
{
    if (!isAlive)
        return false;
    float x, y, z;
    p.get_pos(x, y, z);
    if ((pos_x + P_RADIUS) < (x - P_RADIUS)) //If Ghost is to left of playr
        return false;
    if ((pos_x - P_RADIUS) > (x + P_RADIUS)) // If Ghost is to right of player
        return false;
    if ((pos_y + P_RADIUS) < (y - P_RADIUS)) // If Ghost is below player
        return false;
    if ((pos_y - P_RADIUS) > (y + P_RADIUS)) // If Ghost is above player  (NOT POSSIBLE THOUGH)
        return false;
    if ((pos_z + P_RADIUS) < (z - P_RADIUS)) // If Ghost is in front of player (into screen)
        return false;
    if ((pos_z) > (z + P_RADIUS)) // If Ghost is behind player  (out of the screen)
        return false;
    //Otherwise it is a collision!!
    return true;
}

void Ghost::set_Alive(bool iA)
{
    isAlive = iA;
}

bool Ghost::get_Alive()
{
    return isAlive;
}

void Ghost::display()
{
    if (!isAlive)
        return;
    glPushMatrix();
    glColor3f(color_r, color_g, color_b);
    // mejor entendimiento z by x
    glTranslatef(pos_z, pos_y, pos_x);
    glTranslatef(0, P_RADIUS / 2, 0);
    glutSolidSphere(P_RADIUS, P_SLICES, P_STACKS);
    glPopMatrix();
}

void Ghost::update(tagPlayer &p, Wall **walls, bool attack)
{
    if (!isAlive)
        return;
    if (attack)
    {
        float x, y, z;
        p.get_pos(x, y, z);
        float temp0 = pos_x - x;
        float temp1 = pos_z - z;
        if (abs(temp0) > abs(temp1))
        {
            if (temp0 > 0 && !isObstacle('a', walls))
            {
                n_dir = 2;
            }
            else if (temp0 < 0 && !isObstacle('d', walls))
            {
                n_dir = 3;
            }
        }
        else
        {
            if (temp1 > 0 && !isObstacle('s', walls))
            {
                n_dir = 1;
            }
            else if (temp1 < 0 && !isObstacle('w', walls))
            {
                n_dir = 0;
            }
        }
    }
    if (!handle_input(direction[n_dir], walls))
    {
        if (direction[n_dir] == 'w' || direction[n_dir] == 's')
        {
            n_dir = rand() % 2 + 2;
        }
        else if (direction[n_dir] == 'a' || direction[n_dir] == 'd')
        {
            n_dir = rand() % 2;
        }
    }
}

//verify player position based on input...
bool Ghost::isObstacle(unsigned char key, Wall **walls)
{
    float w_x, w_z, w_w, w_h;
    bool isObject = false;
    float pos_x_temp = 0;
    float pos_z_temp = 0;
    switch (key)
    {
    case 'd':
        pos_x_temp = pos_x + P_X_VEL;
        if (pos_x_temp > ((BOARD_SIZE / 2.0) - (P_RADIUS)))
        {
            isObject = true;
        }
        for (int i = 0; i < MAX_WALL; ++i)
        {
            walls[i]->get(w_x, w_z, w_w, w_h);
            if (pos_x_temp > (w_x - P_RADIUS) & pos_x_temp<(w_x + w_w - P_RADIUS) & pos_z>(w_z - P_RADIUS) & pos_z < (w_z + w_h + P_RADIUS))
            {
                isObject = true;
            }
        }
        break;

    case 'a':
        pos_x_temp = pos_x - P_X_VEL;
        if ((-pos_x_temp) > ((BOARD_SIZE / 2.0) - (P_RADIUS)))
        {
            isObject = true;
        }
        for (int i = 0; i < MAX_WALL; ++i)
        {
            walls[i]->get(w_x, w_z, w_w, w_h);
            if (pos_x_temp<(w_x + w_w + P_RADIUS) & pos_x_temp>(w_x - P_RADIUS) & pos_z > (w_z - P_RADIUS) & pos_z < (w_z + w_h + P_RADIUS))
            {
                isObject = true;
            }
        }

        break;

    case 's':
        pos_z_temp = pos_z - P_Z_VEL;
        if ((-pos_z_temp) > ((BOARD_SIZE / 2.0) - (P_RADIUS)))
        {
            isObject = true;
        }
        for (int i = 0; i < MAX_WALL; ++i)
        {
            walls[i]->get(w_x, w_z, w_w, w_h);
            if (pos_z_temp<(w_z + w_h + P_RADIUS) & pos_z_temp>(w_z - P_RADIUS) & pos_x > (w_x - P_RADIUS) & pos_x < (w_x + w_w + P_RADIUS))
            {
                isObject = true;
            }
        }
        break;

    case 'w':
        pos_z_temp = pos_z + P_Z_VEL;
        if (pos_z_temp > ((BOARD_SIZE / 2.0) - (P_RADIUS)))
        {
            isObject = true;
        }
        for (int i = 0; i < MAX_WALL; ++i)
        {
            walls[i]->get(w_x, w_z, w_w, w_h);
            if (pos_z_temp > (w_z - P_RADIUS) & pos_z_temp<(w_z + w_h + P_RADIUS) & pos_x>(w_x - P_RADIUS) & pos_x < (w_x + w_w + P_RADIUS))
            {
                isObject = true;
            }
        }
        break;
    }
    return isObject;
}
