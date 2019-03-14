// Simple.c
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <sys/time.h>

///////////////////////////////////////////////////////////


// Called to draw scene
void RenderScene(void) {
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

    glBegin(GL_LINES);
        glVertex3f(0.25f, 0.25f, 0.0f);
        glVertex3f(0.50f, 0.25f, 0.0f);
     
        glVertex3f(0.50f, 0.50f, 0.0f);
        glVertex3f(0.25f, 0.50f, 0.0f);

        glVertex3f(0.25f, 0.50f, 0.0f);
        glVertex3f(0.25f, 0.25f, 0.0f);

        glVertex3f(0.50f, 0.50f, 0.0f);
        glVertex3f(0.50f, 0.25f, 0.0f);
    glEnd();

    // Flush drawing commands
    glFlush();
}

///////////////////////////////////////////////////////////
// Setup the rendering state
void SetupRC(void) {


    /* Black background color */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /* Set drawing color */
    glColor3f(1.0f, 1.0f, 1.0f);

    /* Set color shading model to flat */
    glShadeModel(GL_FLAT);

    /* Set clockwise wound polygons front */
    // glFrontFace(GL_CW);
}

///////////////////////////////////////////////////////////
// Main program entry point
void main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(800,600);
    glutCreateWindow("Simple");
    glutDisplayFunc(RenderScene);

    SetupRC();

    glutMainLoop();
    }