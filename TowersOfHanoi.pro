#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T14:00:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowersOfHanoi
TEMPLATE = app


SOURCES += main.cpp\
        hanoiwindow.cpp \
    disk.cpp \
    pole.cpp \
    move.cpp

HEADERS  += hanoiwindow.h \
    disk.h \
    pole.h \
    move.h

FORMS    += hanoiwindow.ui
