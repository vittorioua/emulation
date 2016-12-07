#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T14:12:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        server.cpp \
    service.cpp \
    console.cpp \
    tabledlg.cpp

HEADERS  += server.h \
    service.h \
    console.h \
    tabledlg.h

FORMS    += server.ui \
    tabledlg.ui
