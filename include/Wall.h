/**
 * @file Wall.h
 * @author Cristian Camilo Alzate Anzola
 * @brief 
 * @version 0.1
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __WALL_H__
#define __WALL_H__

class Wall // The wall
{ 
    float x, z, width, height;
public: // Access specifier
    Wall(float x, float y, float width, float height);
    void display();
    void get(float &x0, float &y0, float &w, float &h);
};

#endif // __WALL_H__
