#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T12:56:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nodeide
TEMPLATE = app
LANGUAGE = C++

PRECOMPILED_HEADER = src/StdAfx.h

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/widgets/directorytreewidgetitem.cpp \
    src/widgets/codeeditor.cpp \
    src/widgets/runconfigurationswidget.cpp \
    src/widgets/npmstatusbar.cpp \
    src/widgets/QuickFileOpenWidget.cpp \
    src/widgets/ProjectExplorer.cpp \
    src/widgets/lists/QuickSearchItem.cpp \
    src/widgets/lists/FileTreeWidgetItem.cpp \
    src/QCodeEditor.cpp

HEADERS  += src/StdAfx.h \
    src/mainwindow.h \
    src/widgets/directorytreewidgetitem.h \
    src/widgets/codeeditor.h \
    src/mimetypehelper.h \
    src/widgets/runconfigurationswidget.h \
    src/widgets/npmstatusbar.h \
    src/widgets/QuickFileOpenWidget.h \
    src/widgets/ProjectExplorer.h \
    src/widgets/lists/QuickSearchItem.h \
    src/widgets/lists/FileTreeWidgetItem.h \
    src/highlighter.h \
    src/linenumberwidget.h \
    src/caretpositionwidget.h \
    src/QCodeEditor.h \
    src/StdAfx.h

RESOURCES += \
    resources.qrc

#QCodeEditor config
#INCLUDEPATH += ../qcodeeditor
#LIBS += -L../qcodeeditor/ -lqcodeeditor

CONFIG += c++11 static precompile_header

win32:RC_ICONS = icons/logo.ico

target.path = /usr/local/bin

desktop_file.path = /usr/share/applications
desktop_file.files = nodeide.desktop

desktop_icon.path = /usr/share/icons
desktop_icon.files = icons/nodeide.png

INSTALLS += target desktop_file
