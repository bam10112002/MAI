from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np
from PyQt5.QtOpenGL import *
from PyQt5.QtWidgets import QWidget, QApplication, QHBoxLayout, QSlider
from PyQt5 import QtCore
from Ellipsoid import Ellipsoid
import Wedge
import copy

class MainWindow(QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.widget = glWidget(self)
        mainLayout = QHBoxLayout()
        
        mainLayout.addWidget(self.widget)
        
        sliderX = QSlider(QtCore.Qt.Vertical)
        sliderX.valueChanged.connect(lambda val: self.widget.setRotX(val))

        sliderY = QSlider(QtCore.Qt.Vertical)
        sliderY.valueChanged.connect(lambda val: self.widget.setRotY(val))

        sliderZ = QSlider(QtCore.Qt.Vertical)
        sliderZ.valueChanged.connect(lambda val: self.widget.setRotZ(val))
        
        mainLayout.addWidget(sliderX)
        mainLayout.addWidget(sliderY)
        mainLayout.addWidget(sliderZ)

        self.setLayout(mainLayout)

        timer = QtCore.QTimer(self)
        timer.setInterval(100)   # period, in milliseconds
        timer.timeout.connect(self.widget.updateGL)
        timer.start()

class glWidget(QGLWidget):

    def __init__(self, parent):
        QGLWidget.__init__(self, parent)
        self.setMinimumSize(640, 480)
        # self.wedge = Wedge.Wedge(((-1,-1,-1),(-0.5,0,-0.5)), 40)
        # self.Ellipsoid
        self.figure = Ellipsoid(1,1,1,20)
        self.figure.rotateX(-10)
        print(len(self.figure.surfaces))
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
            color = np.dot(normal_vec, (-0.5, 0.75, 0.2))
            if color < 0:
                color = 0
            glColor3f(color, color, color)

            glVertex3fv(figure.verts[surface[0]])
            glVertex3fv(figure.verts[surface[1]])
            glVertex3fv(figure.verts[surface[2]])
        glEnd()

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        glTranslatef(0, 0.5, -6.0)
        # _figure = copy.deepcopy(self.figure)
        # _figure.rotateX(self.rotX)
        self.figure.rotateY(1)
        # _figure.rotateZ(self.rotZ)
        self.paint_surfaces(self.figure)
        # self.paint_edges()

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

if __name__ == '__main__':
    app = QApplication(['Yo'])
    window = MainWindow()
    window.show()
    app.exec_()