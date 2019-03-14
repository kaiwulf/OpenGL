from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys

class CubeTransform:

    def __init__(self):
        self.xRot = 0.0
        self.yRot = 45.0

    def RenderScene(self):

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        glPushMatrix()
        glTranslatef(0.0, 0.0, 0.0)
        glRotatef(self.xRot, 1.0, 0.0, 0.0)
        glRotatef(self.yRot, 1.0, 1.0, 0.0)

        # glRotatef(yRot, 0.0, 1.0, 0.0)

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        # glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
        glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0)

        # Set color red
        # glColor3f(1.0, 0.0, 0.0)

        glutWireCube(1.0)

        glFlush()

    def SetupRC(self):
        # Black background color
        glClearColor(0.0,0.0,0.0,1.0)

        # Set drawing color
        glColor3f(1.0, 1.0, 1.0)

        # Set color shading model to flat
        glShadeModel(GL_FLAT)

        # Set clockwise wound polygons front
        glFrontFace(GL_CW)

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

        xRot = float(int(self.xRot) % 360)
        yRot = float(int(self.yRot) % 360)

        print("xRot: {}, yRot {}".format(self.xRot, self.yRot))

        glutPostRedisplay()

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

    cube = CubeTransform()

    glutCreateWindow("Rotate Cube")
    glutReshapeFunc(cube.changeSize)
    glutSpecialFunc(cube.specialKeys)
    glutDisplayFunc(cube.RenderScene)

    cube.SetupRC()

    glutMainLoop()

if __name__ == '__main__':
    main(len(sys.argv), sys.argv)