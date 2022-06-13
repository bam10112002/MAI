QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Filters/filters.cpp \
    Filters/myimage.cpp \
    Filters/pixel.cpp \
    VisualBLocks/brightnessblock.cpp \
    VisualBLocks/buttongroup.cpp \
    VisualBLocks/imageview.cpp \
    VisualBLocks/otherblock.cpp \
    VisualBLocks/rightblock.cpp \
    main.cpp \
    mainwindow.cpp \
    VisualBLocks/rgbblock.cpp

HEADERS += \
    Filters/filters.h \
    Filters/myimage.h \
    Filters/pixel.h \
    VisualBLocks/brightnessblock.h \
    VisualBLocks/buttongroup.h \
    VisualBLocks/imageview.h \
    VisualBLocks/otherblock.h \
    VisualBLocks/rightblock.h \
    mainwindow.h \
    VisualBLocks/rgbblock.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Datasets/11.png \
    Datasets/bike.jpg \
    Datasets/img1.jpg \
    Datasets/img2.jpg \
    Datasets/img6.jpg

RESOURCES += \
    resourse.qrc
