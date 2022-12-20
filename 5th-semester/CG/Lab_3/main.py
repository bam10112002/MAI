from PyQt5.QtOpenGL import *
from PyQt5.QtWidgets import QWidget, QApplication, QHBoxLayout, QSlider
from PyQt5 import QtCore
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from Ellipsoid import Ellipsoid
from Wedge import Wedge
import numpy as np

class MainWindow(QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.widget = glWidget(self)
        mainLayout = QHBoxLayout()

        mainLayout.addWidget(self.widget)
        slider = QSlider(QtCore.Qt.Vertical)
        slider.valueChanged.connect(lambda val: self.widget.setReflection(val))
        slider.setMinimum(0)
        slider.setTickInterval(1)
        slider.setValue(100)
        slider.setMaximum(200)

        mainLayout.addWidget(slider)

        self.setLayout(mainLayout)

        self.oldWidth = self.width()
        self.oldHeight = self.height()

        timer = QtCore.QTimer(self)
        timer.setInterval(40)   # period, in milliseconds
        timer.timeout.connect(self.widget.updateGL)
        timer.start()
    def resizeEvent(self,ev):
        self.resize(self.width(), int(self.oldHeight * self.width()/self.oldWidth))

        self.widget.resizeOpenGL(int(self.width()), int(self.height()))
        self.widget.resizeObjects(self.width()/self.oldWidth)
        self.oldWidth = self.width()
        self.oldHeight = self.height()

class glWidget(QGLWidget):

    def __init__(self, parent):
        QGLWidget.__init__(self, parent)
        self.setMinimumSize(640, 480)

        # self.planet = Ellipsoid(1, 1.5, 1.1, 10)
        self.planet = Wedge(((-1,-0.5,-1),(-0.5,0.5,-0.5)), 20)
        self.planet.resize(1)
        self.reflection = 1
        self.rotX = 0.0
        self.rotY = 0.0
        self.rotZ = 0.0

    def paint_edges(self, figure):
        glBegin(GL_LINES)
        for edge in figure.edges():
            glVertex3fv(figure.verts[edge[0]])
            glVertex3fv(figure.verts[edge[1]])
        glEnd()
        glFlush()

    def paint_surfaces(self, figure):
        glBegin(GL_TRIANGLES)
        for surface in figure.surfaces:
            normal_vec = figure.normal(surface) / np.linalg.norm(figure.normal(surface))
            if normal_vec[2] >= 0:
                color = np.dot(normal_vec, (-0.5, 0.75, 0.2)) * (self.reflection/100)
                if color > 0:
                    glColor3f(color, color, color)

                    glVertex3fv(figure.verts[surface[0]])
                    glVertex3fv(figure.verts[surface[1]])
                    glVertex3fv(figure.verts[surface[2]])
        glEnd()

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        glTranslatef(0, 0.5, -8.0)

        self.planet.rotateY(1)
        self.planet.rotateZ(1)
        # self.planet.rotateX(1)

        self.paint_edges(self.planet)
        # self.paint_surfaces(self.figure)

    def resizeObjects(self, k):
        self.planet.resize(k)

    def resizeOpenGL(self,w,h):
        glViewport(0, 0, w, h)

    def initializeGL(self):
        glClearDepth(5.0)
        glDepthFunc(GL_LESS)
        glEnable(GL_DEPTH_TEST)
        glShadeModel(GL_FLAT)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(45.0, 1.33, 0.1, 50.0)
        glMatrixMode(GL_MODELVIEW)
        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        glViewport(0, 0, 640, 480)

    def setRotX(self, val):
        self.rotX = val - self.rotX
    def setRotY(self, val):
        self.rotY = val - self.rotY
    def setRotZ(self, val):
        self.rotZ = val - self.rotZ
    def setReflection(self,val):
        self.reflection = val

if __name__ == '__main__':
    app = QApplication(['Yo'])
    window = MainWindow()
    window.show()
    app.exec_()