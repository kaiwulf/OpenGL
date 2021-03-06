#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <sys/time.h>	// System and OpenGL Stuff
#include <math.h>
#include <stdio.h>
// #include <string.h>

#include "../../../glTools/gltools.h"

void gltInitFrame(GLTFrame *pFrame);

void axis();

static GLfloat xRot = 45.0f;
static GLfloat yRot = 0.0f;
static GLfloat zaxis = -1.0f;

GLTFrame frameCamera;

void RenderScene() {
    float frame = -1.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

	glTranslatef(0.5f, 0.5f, 0.5f);

    // glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    // glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, zaxis);
    glPopMatrix();
    
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(-frame,frame,-frame,frame,-frame,frame);

    axis();

        //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(1.0f);

   glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

    float step_trans = 0.1;

    switch(key) {
        case 'z':
            printf("pressed z\n");
            zaxis += step_trans;
            break;
        case 'x':
            printf("pressed x\n");
            zaxis -= step_trans;
            break;
        default:
            printf("unknown command\n");
            break;
    }

}

// Initialize a frame of reference. 
// Uses default OpenGL viewing position and orientation
// void gltInitFrame(GLTFrame *pFrame)
//     {
//     pFrame->vLocation[0] = 0.0f;
//     pFrame->vLocation[1] = 0.0f;
//     pFrame->vLocation[2] = 0.0f;
    
//     pFrame->vUp[0] = 0.0f;
//     pFrame->vUp[1] = 1.0f;
//     pFrame->vUp[2] = 0.0f;
    
//     pFrame->vForward[0] = 0.0f;
//     pFrame->vForward[1] = 0.0f;
//     pFrame->vForward[2] = -1.0f;
//     }

void specialKeys(int key, int x, int y) {

    float step_rot = 5.01;
    

    if (key == GLUT_KEY_UP)
        xRot -= step_rot;
    else if (key == GLUT_KEY_DOWN)
        xRot += step_rot;
    else if (key == GLUT_KEY_LEFT)
        yRot -= step_rot;
    else if (key == GLUT_KEY_RIGHT)
        yRot += step_rot;

    xRot = (GLfloat) ((GLint) xRot % 360);
    yRot = (GLfloat) ((GLint) yRot % 360);

    // printf("xRot: %f, yRot %f", xRot, yRot);

    glutPostRedisplay();
}

void SetupRC() {
    // Initialize the camera
    // gltInitFrame(&frameCamera);

    // Black background color
    glClearColor(0.0f,0.0f,0.0f,1.0f);

    // Set drawing color
    glColor3f(1.0f, 1.0f, 1.0f);

    // Set color shading model to flat
    glShadeModel(GL_FLAT);

    // Set clockwise wound polygons front
    glFrontFace(GL_CW);
}

void axis() {
    // (0,0,0) to (10,0,0), (0,10,0) and (0,10,0)
    glBegin(GL_LINES);

    // x-axis
    glColor3f(1.0f, 0.0f, 0.0f);  //red
    glVertex3i(0, 0, 0);
    glVertex3i(10, 0, 0);

    // y-axis
    glColor3f(0.0f, 1.0f, 0.0f);  //green
    glVertex3i(0, 0, 0);
    glVertex3i(0, 10, 0);

    // z-axis
    glColor3f(0.0f, 0.0f, 1.0f);  //blue
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 10);

    glEnd();
}

// void TimerFunc() {

// }

void Reshape(int w, int h) {
    GLfloat fAspect;

    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat) w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluLookAt(20, 5, 5, -20, 5, 5, 0, 1, 0)

    // gluPerspective(45.0f, fAspect, 1.0f, 1.0f);
    gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 600);
	glutCreateWindow("sphere");
	glutReshapeFunc(Reshape);

    glutSpecialFunc(specialKeys);
	glutKeyboardFunc(processNormalKeys);

    glutDisplayFunc(RenderScene);
        // glutTimerFunc(250, TimerFunc, 1);
	SetupRC();
	glutMainLoop();

	return 0;
}