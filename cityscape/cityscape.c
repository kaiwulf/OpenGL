// SphereWorld.c
// OpenGL SuperBible
// Demonstrates an immersive 3D environment using actors
// and a camera.
// Program by Richard S. Wright Jr.

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <sys/time.h>   // System and OpenGL Stuff

#include "../glTools/gltools.h"	// OpenGL toolkit
#include <math.h>
#include <string.h>
#include <stdio.h>

    
#define NUM_SQUARES     50
#define A_LEFT          97
#define D_RIGHT         100
#define W_FORWARD       119
#define S_BACK          115
GLTFrame    squares[NUM_SQUARES];
GLTFrame    frameCamera;
        
//////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering
// context. 
void SetupRC()
    {
    int iSquares;
    float pos, i;
    
    // Bluish background
    glClearColor(0.0f, 0.0f, .50f, 1.0f );
         
    // Draw everything as wire frame
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    gltInitFrame(&frameCamera);  // Initialize the camera
    
    // Randomly place the sphere inhabitants
    i = -20.0f;
    pos = 1.0f;
    for(iSquares = 0; iSquares < NUM_SQUARES; iSquares++)
        {
        gltInitFrame(&squares[iSquares]);    // Initialize the frame
        
        // Pick a random location between -20 and 20 at .1 increments

        if(iSquares == NUM_SQUARES / 2) {
                pos = -5.5f;
                i = -20;
            }

        squares[iSquares].vLocation[0] = i + 0.5;
        squares[iSquares].vLocation[1] = 0.5f; 
        squares[iSquares].vLocation[2] = pos;
        i++;
    }
    printf("value of i %f\n", i);
}


///////////////////////////////////////////////////////////
// Draw a gridded ground
void DrawGround(void)
    {
    GLfloat fExtent = 20.0f;
    GLfloat fStep = 1.0f;
    GLfloat y = -0.4f;
    GLint iLine;
    
    glBegin(GL_LINES);
       for(iLine = -fExtent; iLine <= fExtent; iLine += fStep)
          {
          glVertex3f(iLine, y, fExtent);    // Draw Z lines
          glVertex3f(iLine, y, -fExtent);
    
          glVertex3f(fExtent, y, iLine);
          glVertex3f(-fExtent, y, iLine);
          }
    
    glEnd();
    }

        
// Called to draw scene
void RenderScene(void)
    {
    int i;
     static GLfloat yRot = 0.0f;         // Rotation angle for animation
    yRot += 0.5f;
        
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    glPushMatrix();
        gltApplyCameraTransform(&frameCamera);
        
        // Draw the ground
        DrawGround();
        
        // Draw the randomly located squares
        for(i = 0; i < NUM_SQUARES; i++)
            {
            glPushMatrix();
            gltApplyActorTransform(&squares[i]);
            glutSolidCube(0.5f);
            glPopMatrix();
            }

        glPushMatrix();
            glTranslatef(0.0f, 0.0f, -2.5f);
    
            glPushMatrix();
                glRotatef(-yRot * 2.0f, 0.0f, 1.0f, 0.0f);
                glTranslatef(1.0f, 0.0f, 0.0f);
                glutSolidCube(0.5f);
            glPopMatrix();
    
            glRotatef(yRot, 0.0f, 1.0f, 0.0f);
            gltDrawTorus(0.35, 0.15, 40, 20);
        glPopMatrix();
    glPopMatrix();
        
    // Do the buffer Swap
    glutSwapBuffers();
    }

void processNormalKeys(unsigned char key, int x, int y) {

    if(key == W_FORWARD)
        gltMoveFrameForward(&frameCamera, 1.0f);

    if(key == S_BACK)
        gltMoveFrameForward(&frameCamera, -1.0f);

    if(key == A_LEFT)
        gltRotateFrameLocalY(&frameCamera, 1.0);
      
    if(key == D_RIGHT)
        gltRotateFrameLocalY(&frameCamera, -1.0);
                        
    // Refresh the Window
    glutPostRedisplay();
}

// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
    {
    if(key == GLUT_KEY_UP)
        gltMoveFrameForward(&frameCamera, 0.1f);

    if(key == GLUT_KEY_DOWN)
        gltMoveFrameForward(&frameCamera, -0.1f);

    if(key == GLUT_KEY_LEFT)
        gltRotateFrameLocalY(&frameCamera, 0.1);
      
    if(key == GLUT_KEY_RIGHT)
        gltRotateFrameLocalY(&frameCamera, -0.1);

                        
    // Refresh the Window
    glutPostRedisplay();
    }


///////////////////////////////////////////////////////////
// Called by GLUT library when idle (window not being
// resized or moved)
void TimerFunction(int value)
    {
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(3,TimerFunction, 1);
    }

void ChangeSize(int w, int h)
    {
    GLfloat fAspect;

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);
        
    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    // Set the clipping volume
    gluPerspective(35.0f, fAspect, 1.0f, 50.0f);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }

int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Cityscape Experimentation");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(processNormalKeys);

    SetupRC();
    glutTimerFunc(33, TimerFunction, 1);

    glutMainLoop();

    return 0;
    }
