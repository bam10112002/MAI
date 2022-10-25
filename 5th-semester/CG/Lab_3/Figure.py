import numpy as np
import math

class Figure:

    def __init__(self) -> None:
        self.surfaces = []
        self.verts = []

    def edges(self):
        edges = []
        for surface in self.surfaces:
            if self.normal(surface)[2] >= 0:
                edges.append((surface[0], surface[1]))
                edges.append((surface[1], surface[2]))
                edges.append((surface[2], surface[0]))
        return edges


    def rotateX(self, angle):
        angle = angle*math.pi/180
        rot_matrix = np.array([[1, 0,0],[0, math.cos(angle), -1*math.sin(angle)],[0, math.sin(angle), math.cos(angle)]])
        for i in range(len(self.verts)):
            self.verts[i] = tuple(np.dot(self.verts[i],rot_matrix))

    def rotateY(self, angle):
        angle = angle*math.pi/180
        rot_matrix = np.array([[math.cos(angle), 0, math.sin(angle)],[0, 1, 0],[-math.sin(angle),0,math.cos(angle)]])
        for i in range(len(self.verts)):
            self.verts[i] = tuple(np.dot(self.verts[i],rot_matrix))
            
    def rotateZ(self, angle):
        angle = angle*math.pi/180
        rot_matrix = np.array([[math.cos(angle), -1*math.sin(angle), 0], [math.sin(angle), math.cos(angle), 0], [0,0,1]])
        for i in range(len(self.verts)):
            self.verts[i] = tuple(np.dot(self.verts[i],rot_matrix))

    def move(self, x, y, z):
        for i in range(len(self.verts)):
            self.verts[i] = (self.verts[i][0]+x, self.verts[i][1]+y, self.verts[i][2]+z) 
            

    def getVector(v_1, v_2):
        return (v_1[0]-v_2[0],v_1[1]-v_2[1],v_1[2]-v_2[2])

    def normal(self,surface):
        vector_1 = Figure.getVector(self.verts[surface[0]],self.verts[surface[1]])
        vector_2 = Figure.getVector(self.verts[surface[1]],self.verts[surface[2]])
        return tuple(np.cross(vector_1, vector_2))
        
    def resize(self, k):
        for i in range(len(self.verts)):
            self.verts[i] = tuple(np.array(self.verts[i]) * k)
            
