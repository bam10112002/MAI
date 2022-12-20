from cmath import pi
import imp
import numpy as np
from math import sin, cos
from Figure import Figure

class Ellipsoid(Figure):
    def __init__(self, a:int, b:int, c:int, splitting:int) -> None:
        super().__init__()

        # Задаем массивы углов
        alpha_vec  = np.linspace(0, pi, splitting)
        betta_vec = np.linspace(0, 2*pi, splitting)

        # Задаем массив вершин
        for betta in betta_vec:
            for alpha in alpha_vec:
                self.verts.append((a*sin(alpha)*cos(betta), b*sin(alpha)*sin(betta), c*cos(alpha)))
        
        # Задаем грани
        for j in range(splitting-1):
            for i in range(splitting-1):
                A = i+j*splitting
                B = i+(j+1)*splitting
                C = (i+1)+(j+1)*splitting
                D = (i+1)+j*splitting
                self.surfaces.append((A,D,B))
                self.surfaces.append((B,D,C))