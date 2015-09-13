#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T12:56:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nodeide
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/highlighter/JSLexer.cpp \
    src/widgets/projectexplorer.cpp \
    src/widgets/directorytreewidgetitem.cpp \
    src/widgets/codeeditor.cpp \
    src/widgets/runconfigurationswidget.cpp \
    src/widgets/npmstatusbar.cpp \
    src/widgets/QuickFileOpenWidget.cpp

HEADERS  += src/mainwindow.h \
    src/highlighter/JSLexer.h \
    src/widgets/projectexplorer.h \
    src/widgets/directorytreewidgetitem.h \
    src/widgets/codeeditor.h \
    src/mimetypehelper.h \
    src/widgets/runconfigurationswidget.h \
    src/widgets/npmstatusbar.h \
    src/widgets/QuickFileOpenWidget.h

RESOURCES += \
    resources.qrc

unix:LIBS += -lqscintilla2


LIBS += -LC:/releases/qscintilla/release/ -lqscintilla2

INCLUDEPATH += $$PWD/../../../Desktop/QScintilla-gpl-2.9/Qt4Qt5
DEPENDPATH += $$PWD/../../../Desktop/QScintilla-gpl-2.9/Qt4Qt5

#win32-g++: PRE_TARGETDEPS += $$PWD/../../../Desktop/QScintilla-gpl-2.9/build-qscintilla-Desktop_Qt_5_4_2_MinGW_32bit2-Debug/release/libqscintilla2.a

CONFIG += c++11 static

win32:RC_ICONS = icons/logo.ico
