from OpenGL.GL import *
from OpenGL.GLU import *
from PyQt5.QtOpenGL import *
from PyQt5.QtWidgets import QWidget, QApplication, QHBoxLayout,QVBoxLayout
from PyQt5 import QtCore

from Ellipsoid import Ellipsoid
from Wedge import Wedge 
import numpy as np

class MainWindow(QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        mainLayout = QHBoxLayout()
        self.leftLayout = QVBoxLayout()
        self.rightLayout = QVBoxLayout()

        self.resize(600,600)
        
        self.widget1 = glWidget(self)
        self.widget2 = glWidget(self)
        self.widget3 = glWidget(self)
        self.widget4 = glWidget(self)

        self.widget1.resize(300,300)
        self.widget2.resize(300,300)
        self.widget3.resize(300,300)
        self.widget4.resize(300,300)

        self.widget1.resizeOpenGL(300,300)
        self.widget2.resizeOpenGL(300,300)
        self.widget3.resizeOpenGL(300,300)
        self.widget4.resizeOpenGL(300,300)

        self.widget1.setRotX(-10)
        self.widget2.setRotX(90)
        self.widget3.setRotZ(-15)
        self.widget3.setRotY(90)
        self.widget4.setRotZ(90)
        self.widget4.setRotY(-15)

        self.widget2.figure.move(0,-2,0)
        self.widget3.figure.move(-3,1,0)
        self.widget3.figure.resize(2)
        self.widget4.figure.move(0,-5,0)
        self.widget4.figure.resize(1.8)

        self.leftLayout.addWidget(self.widget1)
        self.leftLayout.addWidget(self.widget2)
        self.rightLayout.addWidget(self.widget3)
        self.rightLayout.addWidget(self.widget4)

        mainLayout.addLayout(self.leftLayout)
        mainLayout.addLayout(self.rightLayout)
        self.setLayout(mainLayout)

        self.oldWidth = self.width()
        self.oldHeight = self.height()


        timer = QtCore.QTimer(self)
        timer.setInterval(10)   # period, in milliseconds
        timer.timeout.connect(self.widget1.updateGL)
        timer.timeout.connect(self.widget2.updateGL)
        timer.timeout.connect(self.widget3.updateGL)
        timer.timeout.connect(self.widget4.updateGL)
        timer.start()

    def resizeEvent(self,ev):
        print("s")
        self.resize(self.width(), int(self.oldHeight * self.width()/self.oldWidth))

        self.widget1.resizeOpenGL(int(self.width()/2), int(self.height()/2))
        self.widget1.resizeObjects(self.width()/self.oldWidth)
        
        self.widget2.resizeOpenGL(int(self.width()/2), int(self.height()/2))
        self.widget2.resizeObjects(self.width()/self.oldWidth)
        
        self.widget3.resizeOpenGL(int(self.width()/2), int(self.height()/2))
        self.widget3.resizeObjects(self.width()/self.oldWidth)

        self.widget4.resizeOpenGL(int(self.width()/2), int(self.height()/2))
        self.widget4.resizeObjects(self.width()/self.oldWidth)

        self.oldWidth = self.width()
        self.oldHeight = self.height()

class glWidget(QGLWidget):

    def __init__(self, parent):
        QGLWidget.__init__(self, parent)
        self.setMinimumSize(300, 300)

        # self.figure = Ellipsoid(1,1.5,1,20)
        self.figure = Wedge(((-1,-0.5,-1),(-0.5,0.5,-0.5)), 20)
        self.figure.resize(1)
        self.figure.move(-4,-2,0)
        self.oldW = self.width

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
                color = np.dot(normal_vec, (-0.5, 0.75, 0.2))
                if color > 0:
                    glColor3f(color, color, color)

                    glVertex3fv(figure.verts[surface[0]])
                    glVertex3fv(figure.verts[surface[1]])
                    glVertex3fv(figure.verts[surface[2]])
        glEnd()

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        glTranslatef(0, 0.5, -15.0)
        # self.figure.rotateY(1)
        self.paint_edges(self.figure)

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
        self.figure.rotateX(val)
        # self.rotX = val - self.rotX

    def setRotY(self, val):
        self.figure.rotateY(val)
        # self.rotY = val - self.rotY

    def setRotZ(self, val):
        self.figure.rotateZ(val)
        # self.rotZ = val - self.rotZ

    def resizeObjects(self, k):
        self.figure.resize(k)
    def resizeOpenGL(self,w,h):
        glViewport(0, 0, w, h)

if __name__ == '__main__':
    app = QApplication(['Yo'])
    window = MainWindow()
    window.show()
    app.exec_()