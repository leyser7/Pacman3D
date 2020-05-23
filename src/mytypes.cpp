#include "mytypes.h"
#include "consts.h"
#include <iostream>

//Set camera at start
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