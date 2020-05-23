/**
 * @file Feed.cpp
 * @author Cristian Camilo Alzate Anzola
 * @brief clase depuntos
 * @version 0.1
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
*/

#include "Feed.h"
#include "consts.h"
#include <iostream>

/**
 * @brief Construct a new Feed:: Feed object
 * 
 */
Feed::Feed()
{
    isAlive = false;
    color_r = CLR_FEED_R;
    color_g = CLR_FEED_G;
    color_b = CLR_FEED_B;
}
/**
 * @brief funcion para asignar la variable isAlive
 * 
 * @param alive 
 */
void Feed::set_Alive(bool alive)
{
    isAlive = alive;
}
/**
 * @brief regresa booleana si el feed esta tocando el jugador
 * 
 * @param player 
 * @return true 
 * @return false 
 */
bool Feed::taken(Player player)
{
    if (!isAlive)
        return false;
    float x, y, z;
    player.get_pos(x, y, z);
    float d = dist(pos_x, pos_y, pos_z, x, y, z);
    if (d <= (P_RADIUS + FEED_RADIUS))
    {
        isAlive = false;
        return true;
    }
    return false;
}
/**
 * @brief mostrar objecto
 * 
 */
void Feed::display()
{
    if (!isAlive)
        return;
    glPushMatrix();
    glColor3f(color_r, color_g, color_b);
    // mejor endendimiento
    glTranslatef(pos_z, pos_y, pos_x);
    glTranslatef(0, FEED_RADIUS / 2, 0);
    glutSolidSphere(FEED_RADIUS, P_SLICES, P_STACKS);
    glPopMatrix();
}
/**
 * @brief regresa verdadero si hay un muro en esa posicion
 * 
 * @param x 
 * @param z 
 * @param walls 
 * @return true 
 * @return false 
 */
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