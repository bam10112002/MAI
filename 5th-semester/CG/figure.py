import math
import numpy as np

class Figure:
    surfaces = []

    def __init__(self, base_edge, num_of_faces) -> None:
        verts = [base_edge[0],base_edge[1]]
        angle = 2*math.pi/num_of_faces
        rot_matrix = np.array([[math.cos(angle),0,math.sin(angle)],[0,1,0],[-1*math.sin(angle),0,math.cos(angle)]])

        for count in range((num_of_faces-1)*2):
            verts.append(np.dot(verts[-2],rot_matrix))
        
        for ind in range(num_of_faces*2):
            self.surfaces.append([
                verts[ind],
                verts[(ind+1)%(num_of_faces*2)],
                verts[(ind+2)%(num_of_faces*2)]
            ])
        
        top_center = [0,0,0]
        bottom_center = [0,0,0]
        for ind in range(1,num_of_faces*2,2):
            top_center = [top_center[0] + verts[ind%num_of_faces][0]/num_of_faces,
                          top_center[1] + verts[ind%num_of_faces][1]/num_of_faces,
                          top_center[2] + verts[ind%num_of_faces][2]/num_of_faces]
            bottom_center = [bottom_center[0] + verts[ind%num_of_faces][0]/num_of_faces,
                             bottom_center[1] + verts[ind%num_of_faces][1]/num_of_faces,
                             bottom_center[2] + verts[ind%num_of_faces][2]/num_of_faces]

        for ind in range(1,num_of_faces*2,2):
            self.surfaces.append([
                verts[ind],
                verts[(ind+2)%(num_of_faces*2)],
                verts[top_center]
            ])
            self.surfaces.append([
                verts[ind-1],
                verts[((ind+2)%(num_of_faces*2))-1],
                verts[bottom_center]
            ])