#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T17:56:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    deck.cpp \
    gamemanager.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    tile.h \
    deck.h \
    gamemanager.h \
    player.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
