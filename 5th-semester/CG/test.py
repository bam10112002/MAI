from pygame.locals import *
import numpy as np
import math

from OpenGL.GL import *
from OpenGL.GLU import *

from PyQt5 import QtGui
from PyQt5.QtOpenGL import *
from PyQt5.QtWidgets import QWidget, QCheckBox, QPushButton, QApplication, QHBoxLayout

class Figure:
    surfaces = []

    def __init__(self, base_edge, num_of_faces) -> None:
        verts = [base_edge[0],base_edge[1]]
        angle = 2*math.pi/num_of_faces
        rot_matrix = np.array([[math.cos(angle),0,math.sin(angle)],[0,1,0],[-1*math.sin(angle),0,math.cos(angle)]])

        for count in range((num_of_faces-1)*2):
            verts.append(tuple(np.dot(verts[-2],rot_matrix)))
        
        for ind in range(num_of_faces*2):
            self.surfaces.append([
                verts[ind],
                verts[(ind+1)%(num_of_faces*2)],
                verts[(ind+2)%(num_of_faces*2)]
            ])
        
        top_center = [0,0,0]
        bottom_center = [0,0,0]
        for ind in range(1,num_of_faces*2,2):
            top_center = [top_center[0] + verts[ind%num_of_faces*2][0]/num_of_faces,
                          top_center[1] + verts[ind%num_of_faces*2][1]/num_of_faces,
                          top_center[2] + verts[ind%num_of_faces*2][2]/num_of_faces]
            bottom_center = [bottom_center[0] + verts[ind-1%num_of_faces*2][0]/num_of_faces,
                             bottom_center[1] + verts[ind-1%num_of_faces*2][1]/num_of_faces,
                             bottom_center[2] + verts[ind-1%num_of_faces*2][2]/num_of_faces]

        for ind in range(1,num_of_faces*2,2):
            pass
            self.surfaces.append([
                verts[ind],
                verts[(ind+2)%(num_of_faces*2)],
                tuple(bottom_center)
            ])
            self.surfaces.append([
                verts[ind-1],
                verts[((ind+2)%(num_of_faces*2))-1],
                tuple(top_center)
            ])
    def roberts(self):
        V = []
        for surface in self.surfaces:
            X = [[surface[0][0],surface[0][1],surface[0][2]],
                        [surface[1][0],surface[1][1],surface[1][2]],
                        [surface[2][0],surface[2][1],surface[2][2]]]
            if (np.linalg.det(X) == 0):
                V.append([0,0,0,0])
            else:
                D = np.array([[-1],[-1],[-1]])
                C = np.linalg.inv(X).dot(D)
                V.append(list(np.transpose(C)))

        V = np.transpose(np.array(V))
        E = (0,0,5,0)
        return np.dot(E,V)

    def remove_no_visible_lines(self):
        for surface in self.surfaces:
            if normal(surface)[1] > 0:
                self.surfaces.remove(surface)

    def print(self):
        print("surfaces = {}".format(len(self.surfaces)))
        for surface in self.surfaces:
            print(surface)

class MainWindow(QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.widget = glWidget(self)
        self.button = QPushButton('Test', self)
        mainLayout = QHBoxLayout()
        mainLayout.addWidget(self.widget)
        mainLayout.addWidget(self.button)
        self.setLayout(mainLayout)

def surfaceToEuges(surface):
    edges = []
    edges.append((surface[0], surface[1]))
    edges.append((surface[1], surface[2]))
    edges.append((surface[2], surface[0]))
    return edges

class glWidget(QGLWidget):

    def __init__(self, parent):
        QGLWidget.__init__(self, parent)
        self.setMinimumSize(1000, 1000)

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        glTranslatef(1, 10, -6.0)
        glRotatef(22, 20, 0, 0)
        # glPolygonMode(GL_FRONT, GL_FILL)
        glBegin(GL_LINES)
        figure = Figure(((-10,-10,-10),(-0.5,0,-0.5)), 3)

        for surface in figure.surfaces:
            edges = surfaceToEuges(surface)
            for edge in edges:
                glVertex3fv(edge[0])
                glVertex3fv(edge[1])
        glEnd()
        glFlush()

    def initializeGL(self):
        # glClearDepth(1.0)              
        # glDepthFunc(GL_LESS)
        # glEnable(GL_DEPTH_TEST)
        # glShadeModel(GL_SMOOTH)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()                    
        gluPerspective(45, 1, 0.1, 50.0)
        glMatrixMode(GL_MODELVIEW)

if __name__ == '__main__':
    app = QApplication(['Yo'])
    window = MainWindow()
    window.show()
    app.exec_()