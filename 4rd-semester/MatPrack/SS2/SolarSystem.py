from PyQt5.QtCore import QTimer

from SpaceObjects import Sun, Earth, Moon


class SolarSystem:
    def __init__(self, openglViewWidget):
        self._sun = Sun()
        self._earth = Earth(openglViewWidget)
        self._moon = Moon(openglViewWidget)

        self._timer = QTimer()
        self._timer.timeout.connect(self.animate)
        self._timer.start(20)

        self._time = 0

        self._sun.draw(openglViewWidget)
        self._earth.draw(openglViewWidget)
        self._moon.draw(openglViewWidget)

    def animate(self):

        coordinate_vector = self._earth.animate(self._time)
        self._moon.animate(self._time, coordinate_vector[0][0], coordinate_vector[0][1], coordinate_vector[0][2] - self._earth.radius)
        self._time += 1
