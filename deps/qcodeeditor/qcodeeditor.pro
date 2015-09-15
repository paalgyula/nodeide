#-------------------------------------------------
#
# Project created by QtCreator 2015-09-15T19:10:32
#
#-------------------------------------------------

QT       += widgets

TARGET = qcodeeditor
TEMPLATE = lib
CONFIG += staticlib

SOURCES += QCodeEditor.cpp

HEADERS += QCodeEditor.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
