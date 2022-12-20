import pygame as pg
from pygame.locals import *

from OpenGL.GL import *
from OpenGL.GLU import *
from Ellipsoid import *

def solid(figure):
    glBegin(GL_TRIANGLES)
    glColor(0.5,0.5,0.5)
    for surface in figure.surfaces:
        glVertex3fv(figure.verts[surface[0]])
        glVertex3fv(figure.verts[surface[1]])
        glVertex3fv(figure.verts[surface[2]])
    glEnd()

def main():
    planet = Ellipsoid(1, 1.5, 1.1, 10)
    pg.init()
    display = (1680, 1050)
    pg.display.set_mode(display, DOUBLEBUF|OPENGL)

    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)

    light2_diffuse = [.4, 0.7, 0.2]
    light2_position = [50, 50, 25, 1.0]
    glEnable(GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_AMBIENT, light2_diffuse)
    glLightfv(GL_LIGHT0, GL_POSITION, light2_position)
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0)
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2)
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4)

    glEnable(GL_DEPTH_TEST)
    glTranslatef(0.0, 0.0, -6)

    run = True
    z = 10
    tr = -6
    while run:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                pg.quit()
                quit()
            elif event.type == pg.KEYDOWN:
                if event.key == pg.K_q:
                    run = False
                elif event.key == pg.K_z:
                    z += 2
                    planet = Ellipsoid(1, 1.5, 1.1, z)
                elif event.key == pg.K_x:
                    z -= 2
                    planet = Ellipsoid(1, 1.5, 1.1, z)
                elif event.key == pg.K_r:
                    tr += 1
                    glTranslatef(0.0, 0.0, 1)
                elif event.key == pg.K_f:
                    tr -= 1
                    glTranslatef(0.0, 0.0, -1)


        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        glEnable(GL_LIGHTING)
        glEnable(GL_LIGHT0)
        glEnable(GL_DEPTH_TEST)
        planet.rotateX(1)
        planet.rotateY(1)
        planet.rotateZ(1)
        solid(planet)
        glDisable(GL_LIGHT0)
        glDisable(GL_LIGHTING)
        glDisable(GL_DEPTH_TEST)
        pg.display.flip()
        pg.time.wait(5)

if __name__ == "__main__":
    main()
