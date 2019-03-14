from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys

x = 0.0
y = 0.0
rsize = 25

xstep = 1.0
ystep = 1.0

windowWidth = 125.0
windowHeight = 100.0


def RenderScene():
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(1.0, 0.0, 0.0)
    glRectf(x, y, x + rsize, y - rsize)
    glutSwapBuffers()

def Timer(value):
    global x, y, xstep, ystep, windowWidth, windowHeight

    if x > windowWidth - rsize or x < -windowWidth:
        xstep = -xstep
    if y > windowHeight or y < -windowHeight + rsize:
        ystep = -ystep

    x += xstep
    y += ystep

    if x > (windowWidth - rsize + xstep):
        x = windowWidth - rsize - 1
    elif x < -(windowWidth + xstep):
        x = -windowWidth - 1

    if y > (windowHeight + ystep):
        y = windowHeight - 1
    elif y < -(windowHeight - rsize + ystep):
        y = -windowHeight + rsize - 1

    glutPostRedisplay()
    glutTimerFunc(33, Timer, 1)

def SetupRC():
    glClearColor(0.0, 0.0, 1.0, 1.0)

def ChangeSize(w, h):
    aspectRatio = 0.0

    if h == 0:
        h = 1

    glViewport(0, 0, w, h)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    aspectRatio = float(w / h)
    if w <= h:
        windowWidth = 100.0
        windowHeight = 100.0 / aspectRatio
        glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0)
    else:
        windowWidth = 100.0 * aspectRatio
        windowHeight = 100.0
        glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

def main(argc, argv):
    glutInit(argc, argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB)
    glutInitWindowSize(800,600)
    
    glutCreateWindow("Bounce")
    
    glutDisplayFunc(RenderScene)

    glutReshapeFunc(ChangeSize)

    glutTimerFunc(33, Timer, 1)

    SetupRC()

    glutMainLoop();

if __name__ == '__main__':
    main(len(sys.argv), sys.argv)