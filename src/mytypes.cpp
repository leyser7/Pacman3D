/**
 * @file mytypes.cpp
 * @author Cristian Camilo Alzate Anzola
 * @brief 
 * @version 0.1
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "mytypes.h"
#include "consts.h"
#include <iostream>

/**
 * @brief Construct a new tag Camera::tag Camera object
 * 
 */
tagCamera::tagCamera()
{
    x = CAM_START_X;
    y = CAM_START_Y;
    z = CAM_START_Z;
    angle = CAM_ANGLE;
    a_x = 1.0f;
    a_y = 0.0f;
    a_z = 0.0f;
}