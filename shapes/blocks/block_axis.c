#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <sys/time.h>   // System and OpenGL Stuff
#include <math.h>
#include <stdio.h>

void axis();
void block();

static GLfloat xRot = 45.0f;
static GLfloat yRot = 0.0f;

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glOrtho(-10.0f,10.0f,-10.0f,10.0f,-10.0f,10.0f);

    axis();

    glColor3f(1.0f, 1.0f, 1.0f);
    block();

   glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {

    float step = 5.01;
    if (key == GLUT_KEY_UP)
        xRot -= step;
    if (key == GLUT_KEY_DOWN)
        xRot += step;
    if (key == GLUT_KEY_LEFT)
        yRot -= step;
    if (key == GLUT_KEY_RIGHT)
        yRot += step;

    xRot = (GLfloat) ((GLint) xRot % 360);
    yRot = (GLfloat) ((GLint) yRot % 360);

    printf("xRot: %f, yRot %f", xRot, yRot);

    glutPostRedisplay();
}

void SetupRC() {
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
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3i(0, 0, 0);
    glVertex3i(10, 0, 0);

    // y-axis
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 10, 0);

    // z-axis
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 10);

    glEnd();

    printf("exiting axis()\n");
}

void block() {
    /* A box starting at (3, 3, 3) */

    

    glBegin(GL_QUADS);

    /* front face */
    glColor3f(0.3f, 0.3f, 0.0f);
    


    glEnd();

}

void Reshape(int w, int h) {
    GLfloat fAspect;

    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat) w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluLookAt(20, 5, 5, -20, 5, 5, 0, 1, 0)

    gluPerspective(45.0f, fAspect, 1.0f, 1.0f);

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
    glutDisplayFunc(RenderScene);
        // glutTimerFunc(250, TimerFunc, 1);
    SetupRC();
    glutMainLoop();

    return 0;
}