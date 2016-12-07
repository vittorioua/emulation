#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T13:59:30
#
#-------------------------------------------------

QT       +=  core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = client
TEMPLATE = app

LIBS += -lglu32 -lopengl32 -lglut32


SOURCES += main.cpp\
        client.cpp \
    emulator.cpp \
    console.cpp \
    earth.cpp \
    glparams.cpp \
    place.cpp \
    plane.cpp \
    flight.cpp

HEADERS  += client.h \
    console.h \
    earth.h \
    glparams.h \
    place.h \
    plane.h \
    flight.h \
    emulator.h

FORMS    += client.ui
