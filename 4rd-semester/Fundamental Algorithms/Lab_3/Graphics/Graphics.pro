QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ViewModules/buttongroup.cpp \
    ViewModules/imageview.cpp \
    brightnessblock.cpp \
    brightnesss.cpp \
    main.cpp \
    mainwindow.cpp \
    myimage.cpp \
    myimagefilters.cpp \
    other.cpp \
    rgbblock.cpp \
    thresholdblock.cpp

HEADERS += \
    ViewModules/buttongroup.h \
    ViewModules/imageview.h \
    brightnessblock.h \
    brightnesss.h \
    mainwindow.h \
    myimage.h \
    other.h \
    rgbblock.h \
    thresholdblock.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
