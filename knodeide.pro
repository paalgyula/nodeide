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
    src/widgets/directorytreewidgetitem.cpp \
    src/widgets/codeeditor.cpp \
    src/widgets/runconfigurationswidget.cpp \
    src/widgets/npmstatusbar.cpp \
    src/widgets/QuickFileOpenWidget.cpp \
    src/widgets/ProjectExplorer.cpp \
    src/widgets/lists/QuickSearchItem.cpp \
    src/widgets/lists/FileTreeWidgetItem.cpp

HEADERS  += src/mainwindow.h \
    src/highlighter/JSLexer.h \
    src/widgets/directorytreewidgetitem.h \
    src/widgets/codeeditor.h \
    src/mimetypehelper.h \
    src/widgets/runconfigurationswidget.h \
    src/widgets/npmstatusbar.h \
    src/widgets/QuickFileOpenWidget.h \
    src/widgets/ProjectExplorer.h \
    src/widgets/lists/QuickSearchItem.h \
    src/widgets/lists/FileTreeWidgetItem.h

RESOURCES += \
    resources.qrc

unix:LIBS += -lqscintilla2

win32:LIBS += -LC:/releases/qscintilla/release/ -lqscintilla2
win32:INCLUDEPATH += C:/wspace/QScintilla-gpl-2.9/Qt4Qt5

CONFIG += c++11 static

win32:RC_ICONS = icons/logo.ico
