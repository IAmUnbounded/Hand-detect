#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T21:58:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = hand
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += `pkg-config opencv --libs`

