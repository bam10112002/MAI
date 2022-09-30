from regex import D
import pygame
from pygame.locals import *
import numpy as np
import math

from OpenGL.GL import *
from OpenGL.GLU import *

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
                # D = np.transpose(D)
                
                C = np.linalg.inv(X).dot(D)
                # print(D)
                # print("/n/n/n")
                # print(X)
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





def surfaceToEuges(surface):
    edges = []
    edges.append((surface[0], surface[1]))
    edges.append((surface[1], surface[2]))
    edges.append((surface[2], surface[0]))
    return edges

def getVector(v_1, v_2):
	return (v_1[0]-v_2[0],v_1[1]-v_2[1],v_1[2]-v_2[2])

def normal(surface):
	vector_1 = getVector(surface[0],surface[1])
	vector_2 = getVector(surface[1],surface[2])
	return tuple(np.cross(vector_1, vector_2))


def draw(surfaces:list):
    glBegin(GL_LINES)    # GL_QUADS
    # print(len(surfaces))
    for surface in surfaces:
        # print(normal(surface))
        if normal(surface)[1] <= 0:
            edges = surfaceToEuges(surface)
            for edge in edges:
                glVertex3fv(edge[0])
                glVertex3fv(edge[1])
        else:
            surfaces.remove(surface)
            print("no visible")
    # print("\n\n")
    glEnd()

def showFigure():
    pygame.init()
    pygame.display.set_caption('3d Cube Example')
    display = (1000, 600)
    pygame.display.set_mode(display,DOUBLEBUF|OPENGL)

    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)
    glTranslatef(0.0,0.0,-5)
    glRotatef(22, 20, 0, 0)

    figure = Figure(((-1,-1,-1),(-0.5,0,-0.5)), 3)
    # figure = Figure(((-1,-1,-1),(-1.5,0,-1.5)), 10)
    figure.remove_no_visible_lines()
    figure.print()
    # figure.roberts()
    i = 0
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
                
        glRotatef(1, 0, 1, 0)
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        draw(figure.surfaces)
        pygame.display.flip()
        pygame.time.wait(20)

def main():
    showFigure()

main()