#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T12:56:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = knodeide
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    src/highlighter/JSLexer.cpp \
    src/widgets/projectexplorer.cpp \
    src/widgets/directorytreewidgetitem.cpp \
    src/widgets/codeeditor.cpp \
    src/widgets/runconfigurationswidget.cpp

HEADERS  += mainwindow.h \
    src/highlighter/JSLexer.h \
    src/widgets/projectexplorer.h \
    src/widgets/directorytreewidgetitem.h \
    src/widgets/codeeditor.h \
    src/mimetypehelper.h \
    src/widgets/runconfigurationswidget.h

RESOURCES += \
    resources.qrc

LIBS += -lqscintilla2
