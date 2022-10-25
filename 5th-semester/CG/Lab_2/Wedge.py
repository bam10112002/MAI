import numpy as np
import math
from Figure import Figure

class Wedge(Figure):
    def __init__(self, base_edge, num_of_faces) -> None:
        super().__init__()

        self.verts = [base_edge[0],base_edge[1]]
        angle = 2*math.pi/num_of_faces
        rot_matrix = np.array([[math.cos(angle),0,math.sin(angle)],[0,1,0],[-1*math.sin(angle),0,math.cos(angle)]])

        for count in range((num_of_faces-1)*2):
            self.verts.append(tuple(np.dot(self.verts[-2],rot_matrix)))
        
        for ind in range(num_of_faces*2):
            if ind % 2 == 0:
                self.surfaces.append([ind,(ind+1)%(num_of_faces*2),(ind+2)%(num_of_faces*2)])
            else:
                self.surfaces.append([(ind+2)%(num_of_faces*2),(ind+1)%(num_of_faces*2),ind])
        
        top_center = [0,0,0]
        bottom_center = [0,0,0]
        for ind in range(1,num_of_faces*2,2):
            top_center = [top_center[0] + self.verts[ind%num_of_faces*2][0]/num_of_faces,
                          top_center[1] + self.verts[ind%num_of_faces*2][1]/num_of_faces,
                          top_center[2] + self.verts[ind%num_of_faces*2][2]/num_of_faces]
            bottom_center = [bottom_center[2] + self.verts[ind-1%num_of_faces*2][0]/num_of_faces,
                             bottom_center[1] + self.verts[ind-1%num_of_faces*2][1]/num_of_faces,
                             bottom_center[0] + self.verts[ind-1%num_of_faces*2][2]/num_of_faces]

        self.verts.append(tuple(bottom_center))
        self.verts.append(tuple(top_center))

        for ind in range(1,num_of_faces*2,2):
            self.surfaces.append([len(self.verts)-2,(ind+2)%(num_of_faces*2),ind])
            self.surfaces.append([ind-1,((ind+2)%(num_of_faces*2))-1,len(self.verts)-1])