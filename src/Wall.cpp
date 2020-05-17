#include "Wall.h"
#include "consts.h"
#include <iostream>

Wall::Wall(float x0, float y0, float width0, float height0)
{ // Constructor
        x = x0 - WALL_W;
        z = y0 - WALL_W;
        width = width0;
        height = height0;
}
// Display the player
void Wall::display()
{
    glPushMatrix();
    glColor3f(0, 0, 1);
    // changed x by z
    glTranslatef(z+height/2, 0.25/4.0, x+width/2);
    glScalef(height, 0.25, width);
    glutWireCube(1.01);
    glPopMatrix();

    glPushMatrix();
     // changed x by z
    glColor3f(0, 0, 0);
    glTranslatef(z+height/2, 0.25/4.0, x+width/2);
    glScalef(height, 0.25, width);
    glutSolidCube(1.0);
    glPopMatrix();
}

void Wall::get(float &x0, float &y0, float &w, float &h)
{
    x0 = x;
    y0 = z;
    w = width;
    h = height;
}
