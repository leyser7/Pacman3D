#include"mytypes.h"
#include"consts.h"

//Just construct the player at its start position
tagPlayer::tagPlayer()
{
    pos_x=P_START_X;
    pos_y=P_START_Y;
    pos_z=P_START_Z;
    xVel=0;
    yVel=0;
    zVel=0;
    isjumping = false;
}

//Update player position based on input...
void tagPlayer::handle_input(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 'd' :
        pos_x+=P_X_VEL;
        if(pos_x>((BOARD_SIZE/2.0)-(P_RADIUS)))
            pos_x = (BOARD_SIZE/2.0) - P_RADIUS;
        break;

    case 'a' :
        pos_x-=P_X_VEL;
        if((-pos_x)>((BOARD_SIZE/2.0)-(P_RADIUS)))
            pos_x = -((BOARD_SIZE/2.0) - P_RADIUS);
        break;

    case 's' :
        pos_z+=P_Z_VEL;
        if(pos_z>((BOARD_SIZE/2.0)-(P_RADIUS)))
            pos_z = (BOARD_SIZE/2.0) - P_RADIUS;
        break;

    case 'w' :
        pos_z-=P_Z_VEL;
        if((-pos_z)>((BOARD_SIZE/2.0)-(P_RADIUS)))
            pos_z = -((BOARD_SIZE/2.0) - P_RADIUS);
        break;

    case ' ':
        if(!isjumping)
        {
            yVel = P_Y_VEL_MAX;
            isjumping = true;
        }
        break;
    }

}

void tagPlayer::update()
{
  //  pos_x += xVel;
    pos_y += yVel;
  //  pos_z += zVel;

    if(isjumping)
    {
        yVel += GRAVITY;
        if(pos_y<(P_RADIUS))
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
    glColor3f(P_RGB_R,P_RGB_G,P_RGB_B);
    glTranslatef(pos_x,pos_y,pos_z);
    glTranslatef(0,P_RADIUS/2,0);
    glutSolidSphere(P_RADIUS,P_SLICES,P_STACKS);
    glPopMatrix();
}

void tagPlayer::get_pos(float& x,float& y,float& z)
{
    x = pos_x;
    y = pos_y;
    z = pos_z;
}

void tagPlayer::set_pos(float  x,float  y,float  z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;
}

tagArrow::tagArrow(int lane)
{
    pos_x =0;
    pos_y =0;
    pos_z =0;
    xVel  =0;
    yVel  =0;
    zVel  =0;
    isAlive = false;
    my_lane = lane;
}

bool tagArrow::get_Alive()
{
    return isAlive;
}

int tagArrow::get_lane()
{
    return my_lane;
}

void tagArrow::set_lane(int lane)
{
    my_lane = lane;
}

void tagArrow::set_pos(float x,float y,float z,bool bound_to_lane)
{
    pos_x = x;             //required in case of some special arrow
    pos_y = y;
    pos_z = z;

    if(bound_to_lane)
    {
        pos_x = ((float)(2*my_lane + 1)) * ((BOARD_SIZE/MAX_LANES)/2.0)  + (-BOARD_SIZE/2);
    }
}

void tagArrow::set_Alive(bool iA)
{
    isAlive = iA;
}

void tagArrow::set_vel(float xv,float yv,float zv)
{
    xVel = xv;
    yVel = yv;
    zVel = zv;
}

void tagArrow::display()
{
    if(!isAlive)
        return;
    glPushMatrix();
    glColor3f(CLR_ARR_R,CLR_ARR_G,CLR_ARR_B);
    glTranslatef(pos_x,pos_y,pos_z);
    glutSolidCone(ARR_BASE,ARR_HEIGHT,ARR_SLICES,ARR_STACKS);
    glPopMatrix();
}

void tagArrow::get_pos(float& x,float& y,float &z)
{
    x = pos_x;
    y = pos_y;
    z = pos_z;
}

void tagArrow::update()
{
    if(!isAlive)
        return;
    pos_x+=xVel;
    pos_y+=yVel;
    pos_z+=zVel;
}

bool tagArrow::isCollided(tagPlayer& p)
{
    if(!isAlive)
        return false;
    float x,y,z;
    p.get_pos(x,y,z);
    if((pos_x + ARR_BASE) < (x - P_RADIUS))        //If arro is to left of playr
        return false;
    if((pos_x - ARR_BASE) > (x + P_RADIUS))         // If arrow is to right of player
        return false;
    if((pos_y + ARR_BASE) < (y - P_RADIUS))         // If arrow is below player
        return false;
    if((pos_y - ARR_BASE) > (y + P_RADIUS))         // If Arrow is above player  (NOT POSSIBLE THOUGH)
        return false;
    if((pos_z + ARR_HEIGHT) < (z - P_RADIUS))      // If Arrow is in front of player (into screen)
        return false;
    if((pos_z) > (z + P_RADIUS))       // If arrow is behind player  (out of the screen)
        return false;
    //Otherwise it is a collision!!
    return true;

}

//Set camera at start
tagCamera::tagCamera()
{
    x=CAM_START_X;
    y=CAM_START_Y;
    z=CAM_START_Z;
    angle = CAM_ANGLE;
    a_x = 1.0f;
    a_y = 0.0f;
    a_z = 0.0f;
}

tagDonut::tagDonut()
{
    isAlive = false;
    pos_x = 0;
    pos_y = 0;
    pos_z = 0;
}

bool tagDonut::get_Alive()
{
    return isAlive;
}

void tagDonut::get_pos(float& x,float& y,float& z)
{
    x = pos_x;
    y = pos_y;
    z = pos_z;
}

void tagDonut::set_Alive(bool alive)
{
    isAlive = alive;
}

void tagDonut::set_pos(float x,float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;
}

bool tagDonut::taken(Player player)
{
    if(!isAlive)
        return false;
    float x,y,z;
    player.get_pos(x,y,z);
    float d = dist(pos_x,pos_y,pos_z,x,y,z);
    if(d<=(P_RADIUS + D_OUT_RADIUS))
    {
        isAlive = false;
        return true;
    }
    return false;
}

void tagDonut::display()
{
    if(!isAlive)
        return;
    glPushMatrix();
    glColor3f(D_RGB_R,D_RGB_G,D_RGB_B);
    glTranslatef(pos_x,pos_y,pos_z);
    glRotatef(90,1,0,0);
    glutSolidTorus(D_IN_RADIUS,D_OUT_RADIUS,D_SIDES,D_RINGS);
    glPopMatrix();
}
