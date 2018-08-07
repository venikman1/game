// The OpenGL libraries, make sure to include the GLUT and OpenGL frameworks
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <iostream>
#include "geometry.h"

// This is just an example using basic glut functionality.
// If you want specific Apple functionality, look up AGL

void init() // Called before main loop to set up the program
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

// Called at the start of the program, after a glutPostRedisplay() and during idle
// to display a frame
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0, 0.0, -10.0);
        glVertex3f(100.0, 0.0, -10.0);
        glVertex3f(0.0, 100.0, -10.0);
    glEnd();

    glColor3f(0.0f, 1.0f, 1.0f); 
    glBegin(GL_QUADS);
        glVertex3f(25.f, 25.f, -20.0);
        glVertex3f(200.0f, 50.0f, -20.0);
        glVertex3f(200.0f, 150.0f, -20.0);
        glVertex3f(50.0f, 150.0f, -20.0);
    glEnd();

    glColor3f(0.3f, 0.5f, 1.0f); 
    glBegin(GL_QUADS);
        glVertex3f(50.f, 50.f, 50.0);
        glVertex3f(200.0f, 50.0f, 50.0);
        glVertex3f(200.0f, 150.0f, 50.0);
        glVertex3f(50.0f, 150.0f, 50.0);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); 
    glBegin(GL_LINES);
        glVertex3f(40.0f, 40.0f, 0.0f);
        glVertex3f(140.0f, 40.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_LINES);
        glVertex3f(40.0f, 40.0f, 0.0f);
        glVertex3f(40.0f, 140.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); 
    glBegin(GL_LINES);
        glVertex3f(40.0f, 40.0f, 0.0f);
        glVertex3f(40.0f, 40.0f, 100.0f);
    glEnd();
    glutSwapBuffers();
}

// Called every time a window is resized to resize the projection matrix
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, float(w), 0.0f, float(h), 200.0f, -200.0f);
    GLfloat matrixf[16] = {  // Matrix for our projection
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 1,
    };
    glMultMatrixf(matrixf);

    
    //glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    //glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)), 0.5, 1000.0);

    // glGetFloatv(GL_PROJECTION_MATRIX, matrixf);
    // for (int i = 0; i < 4; ++i) {
    //     std::cout << matrixf[i * 4] << " "
    //         << matrixf[i * 4 + 1] << " "
    //         << matrixf[i * 4 + 2] << " "
    //         << matrixf[i * 4 + 3] << "\n";
    // }

    // std::cout << "\n";
    // glGetFloatv(GL_MODELVIEW_MATRIX, matrixf);
    // for (int i = 0; i < 4; ++i) {
    //     std::cout << matrixf[i * 4] << " "
    //         << matrixf[i * 4 + 1] << " "
    //         << matrixf[i * 4 + 2] << " "
    //         << matrixf[i * 4 + 3] << "\n";
    // }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initializes glut

    // Sets up a double buffer with RGBA components and a depth component
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    // Sets the window size to 512*512 square pixels
    glutInitWindowSize(800, 600);

    // Sets the window position to the upper left
    glutInitWindowPosition(0, 0);

    // Creates a window using internal glut functionality
    glutCreateWindow("Hello!");

    // passes reshape and display functions to the OpenGL machine for callback
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);

    init();

    // Starts the program.
    glutMainLoop();

   
    return 0;
}
