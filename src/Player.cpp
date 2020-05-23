
#include "Player.h"
#include "consts.h"
#include <iostream>

//Just construct the player at its start position
tagPlayer::tagPlayer()
{
    pos_x = P_START_Z;
    pos_y = P_START_Y;
    pos_z = P_START_X;
    color_r = P_RGB_R;
    color_g = P_RGB_G;
    color_b = P_RGB_B;
    xVel = P_X_VEL;
    yVel = 0;
    zVel = P_Z_VEL;
    isjumping = false;
}

//Update player position based on input...
bool tagPlayer::handle_input(unsigned char key, Wall **walls)
{
    float w_x, w_z, w_w, w_h;
    bool isMoving = true;
    switch (key)
    {
    case 'd':
        pos_x += xVel;
        if (pos_x > ((BOARD_SIZE / 2.0) - (P_RADIUS)))
        {
            isMoving = false;
            pos_x = (BOARD_SIZE / 2.0) - P_RADIUS;
        }
        for (int i = 0; i < MAX_WALL; ++i)
        {
            walls[i]->get(w_x, w_z, w_w, w_h);
            if (pos_x > (w_x - P_RADIUS) & pos_x<(w_x + w_w - P_RADIUS) & pos_z>(w_z - P_RADIUS) & pos_z < (w_z + w_h + P_RADIUS))
            {
                pos_x = w_x - P_RADIUS;
                isMoving = false;
            }
        }
        break;

    case 'a':
        pos_x -= xVel;
        if ((-pos_x) > ((BOARD_SIZE / 2.0) - (P_RADIUS)))
        {
            isMoving = false;
            pos_x = -((BOARD_SIZE / 2.0) - P_RADIUS);
        }
        for (int i = 0; i < MAX_WALL; ++i)
        {
            walls[i]->get(w_x, w_z, w_w, w_h);
            if (pos_x<(w_x + w_w + P_RADIUS) & pos_x>(w_x - P_RADIUS) & pos_z > (w_z - P_RADIUS) & pos_z < (w_z + w_h + P_RADIUS))
            {
                pos_x = w_x + w_w + P_RADIUS;
                isMoving = false;
            }
        }
        break;

    case 's':
        pos_z -= zVel;
        if ((-pos_z) > ((BOARD_SIZE / 2.0) - (P_RADIUS)))
        {
            isMoving = false;
            pos_z = -((BOARD_SIZE / 2.0) - P_RADIUS);
        }

        for (int i = 0; i < MAX_WALL; ++i)
        {
            walls[i]->get(w_x, w_z, w_w, w_h);
            if (pos_z<(w_z + w_h + P_RADIUS) & pos_z>(w_z - P_RADIUS) & pos_x > (w_x - P_RADIUS) & pos_x < (w_x + w_w + P_RADIUS))
            {
                pos_z = w_z + w_h + P_RADIUS;
                isMoving = false;
            }
        }
        break;

    case 'w':
        pos_z += zVel;
        if (pos_z > ((BOARD_SIZE / 2.0) - (P_RADIUS)))
        {
            isMoving = false;
            pos_z = (BOARD_SIZE / 2.0) - P_RADIUS;
        }
        for (int i = 0; i < MAX_WALL; ++i)
        {
            walls[i]->get(w_x, w_z, w_w, w_h);
            if (pos_z > (w_z - P_RADIUS) & pos_z<(w_z + w_h + P_RADIUS) & pos_x>(w_x - P_RADIUS) & pos_x < (w_x + w_w + P_RADIUS))
            {
                pos_z = w_z - (P_RADIUS);
                isMoving = false;
            }
        }
        break;

    case ' ':
        if (!isjumping)
        {
            yVel = P_Y_VEL_MAX;
            isjumping = true;
        }
        break;
    }
    return isMoving;
}

void tagPlayer::update()
{
    //pos_x += xVel;
    pos_y += yVel;
    //pos_z += zVel;

    if (isjumping)
    {
        yVel += GRAVITY;
        if (pos_y < (P_RADIUS))
        {
            isjumping = false;
            yVel = 0;
            pos_y = P_RADIUS;
        }
    }
}

// Display the player
void tagPlayer::display()
{
    glPushMatrix();
    glColor3f(color_r, color_g, color_b);
    // mejor endendimiento
    glTranslatef(pos_z, pos_y, pos_x);
    glTranslatef(0, P_RADIUS / 2, 0);
    glutSolidSphere(P_RADIUS, P_SLICES, P_STACKS);
    glPopMatrix();
}

void tagPlayer::get_pos(float &x, float &y, float &z)
{
    x = pos_x;
    y = pos_y;
    z = pos_z;
}

void tagPlayer::set_pos(float x, float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;
}

void tagPlayer::set_color(float r, float g, float b)
{
    color_r = r;
    color_g = g;
    color_b = b;
}