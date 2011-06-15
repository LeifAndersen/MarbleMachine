#-------------------------------------------------
#
# Project created by QtCreator 2011-06-15T11:40:08
#
#-------------------------------------------------

QT       += core gui opengl thread debug

TARGET = qt
TEMPLATE = app


SOURCES += main.cpp mainwindow.cpp ../core/*.cpp ../core/entities/*.cpp \
    os_calls.cpp

HEADERS  += mainwindow.h ../core/*.h ../core/entities/*.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../core/ ../core/entities/
