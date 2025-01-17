/**
 * @file main.cpp
 * @author Cristian Camilo Alzate Anzola
 * @brief 
 * @version 0.1
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include"myfuncs.h"
#include"consts.h"
#include <iostream>

/**
 * @brief function principal
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("GLUT Shapes");
    //glutFullScreen();

    //glutGameModeString("640x480:32@60");
    //glutEnterGameMode();

    init_Rendering();

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutPassiveMotionFunc(mouse_motion);
    glutMouseFunc(mouse_click);
    glutReshapeFunc(handle_resize);
    glutIdleFunc(idle);



    glutMainLoop();

    return EXIT_SUCCESS;
}
