import sys

from pyqtgraph.Qt import QtCore, QtGui, QtWidgets
import pyqtgraph.opengl as opengl

from SolarSystem import SolarSystem


if __name__ == '__main__':
    QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_UseDesktopOpenGL)
    application = QtWidgets.QApplication(sys.argv)
    openglViewWidget = opengl.GLViewWidget()
    openglViewWidget.showMaximized()

    solarSystem = SolarSystem(openglViewWidget)
    solarSystem.animate()

    sys.exit(application.exec_())
