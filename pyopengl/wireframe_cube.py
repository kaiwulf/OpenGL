from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys

class WireFrame:

    def __init__(self):
        self.xRot = 0.0
        self.yRot = 0.0

    def RenderScene(self):
        x=.25
        y=.25
        z=.25
        side=.25
        # /////////////////////////////

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
        glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0)
        # /////////////////////////////

        # glPushMatrix()
        glTranslatef(0.0, 0.0, 0.0)
        glRotatef(self.xRot, 1.0, 0.0, 0.0)
        glRotatef(self.yRot, 0.0, 1.0, 0.0)

        glBegin(GL_LINES)
        self.square(x, y, z, side)
        x2 = x + .25/2
        y2 = y + .25/2
        self.square(x2, y2, z, side)
        self.squareConnect(x, x2, y, y2, z, side)

        glEnd()

        glFlush()

    def specialKeys(self, key, x, y):
        step = 5.01
        if key == GLUT_KEY_UP:
            self.xRot -= step
        if key == GLUT_KEY_DOWN:
            self.xRot += step
        if key == GLUT_KEY_LEFT:
            self.yRot -= step
        if key == GLUT_KEY_RIGHT:
            self.yRot += step

        self.xRot = float(int(self.xRot) % 360)
        self.yRot = float(int(self.yRot) % 360)

        print("xRot: {}, yRot {}".format(self.xRot, self.yRot))

        glutPostRedisplay()

    def square(self, x, y, z, side):
        # first square
        glVertex3f(x, y, z)
        glVertex3f(x + side, y, z)

        glVertex3f(x, y, z)
        glVertex3f(x, y + side, z)

        glVertex3f(x, y + side, z)
        glVertex3f(x + side, y + side, z)

        glVertex3f(x + side, y, z)
        glVertex3f(x + side, y + side, z)
        
    def squareConnect(self, x, x2, y, y2, z, side):
        #connect the two squares
        glVertex3f(x, y, z)
        glVertex3f(x2, y2, z + side)

        glVertex3f(x + side, y, z)
        glVertex3f(x2 + side, y2, z + side)

        glVertex3f(x, y + side, z)
        glVertex3f(x2, y2 + side, z + side)

        glVertex3f(x + side, y + side, z)
        glVertex3f(x2 + side, y2 + side, z + side)

    def SetupRC(self):
        # Black background color
        glClearColor(0.0,0.0,0.0,1.0)

        # Set drawing color
        glColor3f(1.0, 1.0, 1.0)

        # Set color shading model to flat
        glShadeModel(GL_FLAT)

        # Set clockwise wound polygons front
        glFrontFace(GL_CW)

    def changeSize(self, w, h):
        fAspect = float()

        if h == 0:
            h = 1

        glViewport(0, 0, w, h)

        fAspect = float(w)/float(h)

        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()

        gluPerspective(1.0, fAspect, 1.0, 1.0)

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

def main(argc, argv):
    glutInit(argc, argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(800,600)
    glutCreateWindow("Rotate Cube")

    cube = WireFrame()

    glutReshapeFunc(cube.changeSize)
    glutSpecialFunc(cube.specialKeys)
    glutDisplayFunc(cube.RenderScene)

    cube.SetupRC()

    glutMainLoop()

if __name__ == '__main__':
    main(len(sys.argv), sys.argv)