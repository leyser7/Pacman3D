#include "myfuncs.h"
#include "consts.h"
#include "Wall.h"
#include "Player.h"
#include <iostream>

int screen_w = 640, screen_h = 480;

int level;    //level
int points;   //Points
float health; //Health

Wall *walls[MAX_WALL];

Player global_MainPlayer;

Camera global_Camera;
Arrow *arrows[MAX_LANES];

Donut donut;

GameStates global_GameState = GSMenu;
GameErrors global_Error = GE_NO_ERROR;

bool played = false; // Stores if game has been played atleast once
bool won = false;
bool cancontinue = false;
float menu_sel_angle = 0.0;
float controls_angle = 0.0f;
float credits_angle = 0.0f;

void init_arrow(Arrow *arr)
{
    int n = rand() % LVL_NUM_RAND;   // Just a random number
    if (n > LVL_NUM_PROB[level - 1]) // Use some probability criterion to decide when to update the Arrow
        return;
    arr->set_pos(0, 0.2, -(BOARD_SIZE / 2)); //Just y and z co-ords matter
    arr->set_vel(0, 0, ARR_VEL_Z * (1.0f + (float)(level - 1) * 0.6f));
    arr->set_Alive(true);
}

void init_donut(Donut &dnt)
{
    int n = rand() % D_MAX_NUM;
    if (n > D_NUM_PROB)
        return;
    float x = -(BOARD_SIZE / 2) + D_OUT_RADIUS + (rand() % (int)BOARD_SIZE);
    if (x > ((BOARD_SIZE / 2) - D_OUT_RADIUS))
        x = (BOARD_SIZE / 2) - D_OUT_RADIUS;
    float z = -(BOARD_SIZE / 4) + D_OUT_RADIUS + (rand() % (int)BOARD_SIZE);
    if (z > ((BOARD_SIZE / 2) - D_OUT_RADIUS))
        z = (BOARD_SIZE / 2) - D_OUT_RADIUS;
    dnt.set_pos(x, D_OUT_RADIUS / 2, z);
    dnt.set_Alive(true);
}

void update_vars(int n)
{
    switch (global_GameState)
    {
    case GSControls:
        controls_angle += 0.07f;
        if (controls_angle >= 360.0f)
        {
            controls_angle -= 360.0f;
        }
        break;
    case GSCredits:
        credits_angle += 0.07f;
        if (credits_angle >= 360.0f)
        {
            credits_angle -= 360.0f;
        }
        break;
    case GSMenu:
        menu_sel_angle += 0.07f;
        if (menu_sel_angle >= 360.0f)
        {
            menu_sel_angle -= 360.0f;
        }
        break;
    case GSPlaying:
        played = true;
        global_MainPlayer.update();
        /*
        //Arrows
        float x,y,z;
        for(int i=0;i<MAX_LANES;++i)
        {
            if(arrows[i]->isCollided(global_MainPlayer))
            {
                arrows[i
                
                ]->set_Alive(false);
                health -= P_DEDUCT_H_ON_ONE_ARROW;
                if(health<=0.0f)
                {
                    cancontinue = false;
                    won = false;
                    key(27,0,0);
                }
            }
            arrows[i]->update();
            if(arrows[i]->get_Alive() == false)
                init_arrow(arrows[i]);
            else
            {
                arrows[i]->get_pos(x,y,z);
                if(z>(BOARD_SIZE/2))
                {
                    arrows[i]->set_Alive(false);
                    points += POINTS_ON_ONE_ARROW;
                }
            }
        }
        */
        //Donut
        if (donut.get_Alive() == false)
        {
            init_donut(donut);
        }
        else
        {
            if (donut.taken(global_MainPlayer))
            {
                points += POINTS_ON_ONE_DONUT;
            }
        }

        if (POINTS_TO_PASS[level - 1] <= points)
        {
            level++;
            if (level > MAX_LEVELS)
            {
                cancontinue = false;
                won = true;
                key(27, 0, 0);
            }
        }
        break;

    default:
        break;
    }

    glutPostRedisplay();
    glutTimerFunc((1000 / GAME_FPS), update_vars, 0);
}

void init_level()
{
    level = 1;
    points = 0;
    health = P_MAX_HEALTH;
    for (int i = 0; i < MAX_LANES; ++i)
    {
        arrows[i]->set_Alive(false);
        init_arrow(arrows[i]);
    }
    global_MainPlayer.set_pos(P_START_X, P_START_Y, P_START_Z);
}

//Initializes 3D rendering
void init_Rendering()
{
    try
    {
        t3dInit();
    }
    catch (T3DLoadException e)
    {
        // If font could not be initialised
        ofstream out;
        out.open("ERROR_LOG.txt");
        out << "EXCEPTION!!" << endl;
        out << e.message();
        out.close();
        global_Error = GE_CHARSET_ERROR;
        exit((int)global_Error);
    }

    for (int i = 0; i < MAX_LANES; ++i)
    {
        arrows[i] = new Arrow(i);
    }
    //for (int i = 0; i < MAX_WALL; ++i)
    // {
    float diametro = WALL_W*2.0f;
    //left down
    walls[0] = new Wall(diametro*-7.0f, diametro*-7.0f, diametro*6.0f, diametro);
    walls[1] = new Wall(diametro*-4.0f, diametro*-6.0f, diametro,  diametro*2.0f);

    walls[2] = new Wall(diametro*-6.0f, diametro*-5.0f, diametro, diametro*3.0f);
    walls[3] = new Wall(diametro*-7.0f, diametro*-3.0f, diametro, diametro);

    walls[4] = new Wall(diametro*-8.0f, diametro*-5.0f, diametro, diametro);

    walls[5] = new Wall(diametro*-4.0f, diametro*-3.0f, diametro*3.0f,  diametro);

    //rigth down
    
    walls[6] = new Wall(diametro*2.0f, diametro*-7.0f, diametro*6.0f, diametro);
    walls[7] = new Wall(diametro*4.0f, diametro*-6.0f, diametro,  diametro*2.0f);

    walls[8] = new Wall(diametro*6.0f, diametro*-5.0f, diametro, diametro*3.0f);
    walls[9] = new Wall(diametro*7.0f, diametro*-3.0f, diametro, diametro);

    walls[10] = new Wall(diametro*8.0f, diametro*-5.0f, diametro, diametro);

    walls[11] = new Wall(diametro*2.0f, diametro*-3.0f, diametro*3.0f,  diametro);

    // center 
    walls[12] = new Wall(diametro*-2.0f, diametro*-5.0f, diametro*5.0f, diametro);
    walls[13] = new Wall(0, diametro*-7.0f, diametro,  diametro*2.0f);

    walls[14] = new Wall(diametro*-2.0f, diametro*-1.0f, diametro*5.0f, diametro);
    walls[15] = new Wall(0, diametro*-3.0f, diametro,  diametro*2.0f);

    walls[16] = new Wall(diametro*-2.0f, diametro*5.0f, diametro*5.0f, diametro);
    walls[17] = new Wall(0, diametro*3.0f, diametro,  diametro*2.0f);

    walls[18] = new Wall(0, diametro*7.0f, diametro,  diametro*2.0f);

    walls[19] = new Wall(diametro*-4.0f, diametro*-1.0f, diametro,  diametro*2.0f);
    walls[20] = new Wall(diametro*4.0f, diametro*-1.0f, diametro,  diametro*2.0f);

    walls[21] = new Wall(diametro*-4.0f, diametro*2.0f, diametro,  diametro*4.0f);
    walls[22] = new Wall(diametro*-3.0f, diametro*3.0f, diametro*2.0f,  diametro);

    walls[23] = new Wall(diametro*4.0f, diametro*2.0f, diametro,  diametro*4.0f);
    walls[24] = new Wall(diametro*2.0f, diametro*3.0f, diametro*2.0f,  diametro);

    walls[25] = new Wall(diametro*-7.0f, diametro*5.0f, diametro*2.0f, diametro);
    walls[26] = new Wall(diametro*6.0f, diametro*5.0f, diametro*2.0f, diametro);

    walls[27] = new Wall(diametro*-7.0f, diametro*7.0f, diametro*2.0f, diametro);
    walls[28] = new Wall(diametro*6.0f, diametro*7.0f, diametro*2.0f, diametro);

    walls[29] = new Wall(diametro*-4.0f, diametro*7.0f, diametro*3.0f, diametro);
    walls[30] = new Wall(diametro*2.0f, diametro*7.0f, diametro*3.0f, diametro);
    // laterales
    walls[31] = new Wall(diametro*-8.0f, diametro*-1.0f, diametro*3.0f, diametro/2.0f);
    walls[32] = new Wall(diametro*6.0f, diametro*-1.0f, diametro*3.0f, diametro/2.0f);

    walls[33] = new Wall(diametro*-8.0f, diametro*1.0f/2.0f, diametro*3.0f, diametro/2.0f);
    walls[34] = new Wall(diametro*6.0f, diametro*1.0f/2.0f, diametro*3.0f, diametro/2.0f);

    walls[35] = new Wall(diametro*-8.0f, diametro*2.0f, diametro*3.0f, diametro/2.0f);
    walls[36] = new Wall(diametro*6.0f, diametro*2.0f, diametro*3.0f, diametro/2.0f);

    walls[37] = new Wall(diametro*-8.0f, diametro*3.0f+diametro/2.0f,diametro*3.0f, diametro/2.0f);
    walls[38] = new Wall(diametro*6.0f, diametro*3.0f+diametro/2.0f, diametro*3.0f, diametro/2.0f);

    walls[39] = new Wall(diametro*-6.0f+diametro/2.0f, diametro*2.0f, diametro/2.0f, diametro*2.0f);
    walls[40] = new Wall(diametro*6.0f, diametro*2.0f, diametro/2.0f, diametro*2.0f);

    walls[41] = new Wall(diametro*-6.0f+diametro/2.0f, diametro*-1.0f,diametro/2.0f, diametro*2.0f);
    walls[42] = new Wall(diametro*6.0f, diametro*-1.0f, diametro/2.0f, diametro*2.0f);

    srand(time(NULL)); // seed the random number generator

    glClearColor(CLR_CLR_R, CLR_CLR_G, CLR_CLR_B, CLR_CLR_A);
    //  glEnable(GL_CULL_FACE);
    //  glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutTimerFunc((1000 / GAME_FPS), update_vars, 0);
}

//Called when the window is resized
void handle_resize(int w, int h)
{
    screen_w = w;
    screen_h = h;
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

    //Set the camera perspective
    glLoadIdentity();                     //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void draw_ground()
{
    glPushMatrix();
    glColor3f(0, 0.8, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(-(BOARD_SIZE / 2), 0, -(BOARD_SIZE / 2));
    glVertex3f((BOARD_SIZE / 2), 0, -(BOARD_SIZE / 2));
    glVertex3f((BOARD_SIZE / 2), 0, (BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2), 0, (BOARD_SIZE / 2));
    glEnd();
    glColor3f(0, 0, 1);
    /*
    glBegin(GL_LINES);
    glVertex3f(-(BOARD_SIZE / 2) + (BOARD_SIZE / 8), 0.001, -(BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + (BOARD_SIZE / 8), 0.001, (BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 2 * (BOARD_SIZE / 8), 0.001, -(BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 2 * (BOARD_SIZE / 8), 0.001, (BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 3 * (BOARD_SIZE / 8), 0.001, -(BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 3 * (BOARD_SIZE / 8), 0.001, (BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 4 * (BOARD_SIZE / 8), 0.001, -(BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 4 * (BOARD_SIZE / 8), 0.001, (BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 5 * (BOARD_SIZE / 8), 0.001, -(BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 5 * (BOARD_SIZE / 8), 0.001, (BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 6 * (BOARD_SIZE / 8), 0.001, -(BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 6 * (BOARD_SIZE / 8), 0.001, (BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 7 * (BOARD_SIZE / 8), 0.001, -(BOARD_SIZE / 2));
    glVertex3f(-(BOARD_SIZE / 2) + 7 * (BOARD_SIZE / 8), 0.001, (BOARD_SIZE / 2));
    glEnd();
    */
    glPopMatrix();
}

void draw_texts()
{
    //Points
    ostringstream oss;
    oss << "Points : " << points;
    string str;
    str = oss.str();
    float w = t3dDrawWidth(str);
    float sx = (3.5 / w);

    glPushMatrix();
    glColor3f(0, 0, 1);
    glRotatef(-45, 0, 1, 0);
    glTranslatef(0, 0.7, -(BOARD_SIZE / 2) - 1.5);
    glScalef(sx, 0.5, 1.0);
    t3dDraw3D(str, 0, 0, 0.2);
    glPopMatrix();

    //Level
    ostringstream oss2;
    oss2 << "Level: " << level;
    string str2;
    str2 = oss2.str();

    glPushMatrix();
    glColor3f(0.8, 0, 0.4);
    glRotatef(45, 0, 1, 0);
    glTranslatef(0, 0.7, -(BOARD_SIZE / 2) - 1.5);
    glScalef(0.7, 0.5, 1.0);
    t3dDraw3D(str2, 0, 0, 0.2);
    glPopMatrix();
}

void draw_health()
{
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(0, 0, 0);
    glScalef(2.0, 1.0, 2.0);
    glutWireCube(1.01);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1, 1, 0.1);
    glTranslatef(0, 0, 0);
    glScalef(2.0, 1.0, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();
    /*
    glBegin(GL_QUADS);
    glShadeModel(GL_SMOOTH);
    */
    /* Floor /
glVertex3f(-1,-1,-1);
glVertex3f(1,-1,-1);
glVertex3f(1,-1,1);
glVertex3f(-1,-1,1);
/ Ceiling /
glVertex3f(-1,1,-1);
glVertex3f(1,1,-1);
glVertex3f(1,1,1);
glVertex3f(-1,1,1);
/ Walls */
    /*
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);

    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glEnd();
    */
}

void playing_display()
{
    // glTranslatef(0.5f, -0.3f, -1.8f);
    //glRotatef(45, 1.0, 0, 0);
    glTranslated(global_Camera.x, global_Camera.y, global_Camera.z);
    glRotatef(45, 1.0, 0, 0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    // glTranslatef(0.5f, -0.3f, -1.8f);
    //glRotatef(global_Camera.angle, global_Camera.a_x, global_Camera.a_y, global_Camera.a_z);

    //draw_texts();
    draw_ground();
    //draw_health();
    for (int i = 0; i < MAX_WALL; ++i)
    {
        walls[i]->display();
    }

    global_MainPlayer.display();
    /*
    float x, y, z;
    global_MainPlayer.get_pos(x, y ,z);
    std::cout<<"x: "<<x<<" ";
    std::cout<<"y: "<<y<<" ";
    std::cout<<"z: "<<z<<std::endl;
    */
    for (int i = 0; i < MAX_LANES; ++i)
    {
        arrows[i]->display();
    }
    donut.display();

    cancontinue = true;
}

char controls_text[10] = "CONTROLS";
void controls_display()
{
    glTranslatef(0, 0, -9);
    glTranslatef(-3.8, 0, 0);
    char str[2] = {' ', '\0'};
    for (int i = 0; i < 8; ++i)
    {
        str[0] = controls_text[i];
        glPushMatrix();
        glColor3f(0.9, 0.1, 0.2);
        glTranslatef(i * 1.1, 2.4, sin(controls_angle + (float)(i * 90)));
        glRotatef(10 * sin(controls_angle), 0, 1, 0);
        glScalef(0.8, 0.7, 0.7);
        t3dDraw3D(str, 0, 0, 0.5, 0.7);
        glPopMatrix();
    }
    glPushMatrix();
    glColor3f(0.9, 0.8, 0.1);
    glPushMatrix();
    glTranslatef(-1.1, 1.0, 0);
    glScalef(0.5, 0.3, 0.8);
    t3dDraw3D("Use W/A/S/D to move the ball.", -1, 0, 0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.1, 0, 0);
    glScalef(0.6, 0.3, 0.8);
    t3dDraw3D("Use Spacebar to jump.", -1, 0, 0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.1, -1.5, 0);
    glScalef(0.5, 0.3, 0.8);
    t3dDraw3D("Anytime in game press Esc\nto go to menu.", -1, 0, 0.2);
    glPopMatrix();
    glPopMatrix();
}

char credits_text[10] = "CREDITS";
void credits_display()
{
    glTranslatef(0, 0, -9);
    glTranslatef(-3.5, 0, 0);
    char str[2] = {' ', '\0'};
    for (int i = 0; i < 8; ++i)
    {
        str[0] = credits_text[i];
        glPushMatrix();
        glColor3f(0.9, 0.1, 0.2);
        glTranslatef(i * 1.1, 2.4, sin(credits_angle + (float)(i * 5)));
        glRotatef(10 * sin(credits_angle), 0, 1, 0);
        glScalef(0.8, 0.7, 0.7);
        t3dDraw3D(str, 0, 0, 0.5, 0.7);
        glPopMatrix();
    }

    glPushMatrix();
    glColor3f(0.9, 0.8, 0.1);
    glTranslatef(-1.1, 0.5, 0);
    glRotatef(8 * sin(credits_angle), 0.1, 0.1, 1.0);
    glScalef(0.5, 0.6, 0.6);
    t3dDraw3D("CONCEPT", -1, 0, 0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.1, -1.5, 0);
    glRotatef(-8 * sin(credits_angle), 0.1, 0.1, 1.0);
    glScalef(0.4, 0.6, 0.6);
    t3dDraw3D("PROGRAMMER", -1, 0, 0.2);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1, 0.2, 0.9);
    glTranslatef(8.0, 0.5, 0);
    glRotatef(8 * sin(credits_angle), -0.1, -0.1, -1.0);
    glScalef(0.6, 0.5, 0.6);
    t3dDraw3D("Abhijeet Patil", 1, 0, 0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(8.0, -1.5, 0);
    glRotatef(-8 * sin(credits_angle), -0.1, -0.1, -1.0);
    glScalef(0.50, 0.5, 0.6);
    t3dDraw3D("Abhinav Tripathi", 1, 0, 0.2);
    glPopMatrix();
    glPopMatrix();
}

void display_lastmsg()
{
    glPushMatrix();
    glTranslatef(-2.7, 0.1, 0);
    glColor3f(0.7, 0.8, 0.1);
    glScalef(0.25, 0.2, 0.4);
    if (won)
        t3dDraw3D("Congrats! You won the last game!!", -1, 0, 0.2);
    else
        t3dDraw3D("OOPS! You lost the last game!\nBetter luck next time...", -1, 0, 0.2);
    glPopMatrix();
}

int menu_sel = 0;
char menu_items[NUM_MENU_ITEMS][10] = {"Continue", "New Game", "Controls", "Credits", "Exit"};

void menu_display()
{
    glTranslatef(0, 0, -5);
    glPushMatrix();
    glColor3f(0.2, 0.8, 0.2);
    glTranslatef(0, 1.7, 0);
    glScalef(0.7, 0.5, 0.5);
    t3dDraw3D("Pacman 3D", 0, 0, 0.2, 0.5);
    glPopMatrix();
    glTranslatef(0, 1.0, 0);
    if (played && !cancontinue)
    {
        display_lastmsg();
    }
    for (int i = 0; i < NUM_MENU_ITEMS; ++i)
    {
        if (i == 0 && !cancontinue)
        {
            continue;
        }
        glPushMatrix();
        glTranslatef(0, -2.5 * ((float)i * (MENU_TEXT_HEIGHT + MENU_LINE_SPACING)), 0);
        if (i == menu_sel)
        {
            glColor3f(MENU_SEL_RGB_R, MENU_SEL_RGB_G, MENU_SEL_RGB_B);
            glRotatef(45 * sin(menu_sel_angle), 0, 1, 0);
        }
        else
            glColor3f(MENU_RGB_R, MENU_RGB_G, MENU_RGB_B);
        glScalef(0.5, MENU_TEXT_HEIGHT / t3dDrawHeight(menu_items[i]), 1);
        t3dDraw3D(menu_items[i], 0, 0, 0.2);
        glPopMatrix();
    }
}
int mousex, mousey;
void mouse_click(int x1, int y1, int x2, int y2)
{
    switch (global_GameState)
    {
    case GSMenu:
        switch (menu_sel)
        {
        case 0:
            global_GameState = GSPlaying;
            break;
        case 1:
            init_level();
            global_GameState = GSPlaying;
            break;
        case 2:
            global_GameState = GSControls;
            break;
        case 3:
            global_GameState = GSCredits;
            break;
        case (NUM_MENU_ITEMS - 1):
            key(27, 0, 0);
            break;
        }
        break;
    default:
        break;
    }
}

void mouse_motion(int x, int y)
{
    mousex = x;
    mousey = y;
    int sel;
    switch (global_GameState)
    {
    case GSMenu:
        sel = (y - (screen_h / 6)) / (screen_h / 6);
        if (sel < 0)
            sel = 0;
        else if (sel >= NUM_MENU_ITEMS)
            sel = NUM_MENU_ITEMS - 1;
        if (sel == 0 && !cancontinue)
        {
            sel = 1;
        }
        if (sel != menu_sel)
        {
            menu_sel = sel;
            menu_sel_angle = 0.0f;
        }
        break;
    default:
        break;
    }
}

void display(void)
{
    //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity();           //Reset the drawing perspective

    switch (global_GameState)
    {
    case GSMenu:
        menu_display();
        break;
    case GSPlaying:
        playing_display();
        break;
    case GSControls:
        controls_display();
        break;
    case GSCredits:
        credits_display();
        break;
    default:
        break;
    }

    glutSwapBuffers();
}

void key(unsigned char key, int x, int y)
{
    switch (global_GameState)
    {
    case GSMenu:
        switch (key)
        {
        case 27:
            t3dCleanup();
            //glutLeaveGameMode();
            exit((int)global_Error);
            break;
        }
        break;
    case GSPlaying:
        switch (key)
        {
        case 27:
            global_GameState = GSMenu;
            break;
        default:
            global_MainPlayer.handle_input(key, x, y, walls);
        }
        break;
    case GSControls:
        switch (key)
        {
        case 27:
            global_GameState = GSMenu;
            break;
        default:
            break;
        }
        break;
    case GSCredits:
        switch (key)
        {
        case 27:
            global_GameState = GSMenu;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

//Called when glut is idle
void idle()
{
    glutPostRedisplay();
}
