QT += core gui

CONFIG += c++11

TARGET = LaneDetect
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    application.cpp \
    barcodescanner.cpp \
    lanedetect.cpp \
    imagepublisher.cpp \
    config.cpp \
    timer.cpp \
    motorcontrol.cpp \
    cameracontrol.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

LIBS += `pkg-config opencv --cflags --libs` -lzbar -lpigpio -lwiringPi

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    application.h \
    barcodescanner.h \
    lanedetect.h \
    types.h \
    imagepublisher.h \
    config.h \
    timer.h \
    motorcontrol.h \
    cameracontrol.h
