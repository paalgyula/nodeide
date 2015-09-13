cmake_minimum_required(VERSION 2.8.11)

project(nodeide)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" )

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(QScintilla REQUIRED)

set(SOURCE
  src/main.cpp
  src/mainwindow.cpp
  src/highlighter/JSLexer.cpp
  src/widgets/codeeditor.cpp
  src/widgets/directorytreewidgetitem.cpp
  src/widgets/npmstatusbar.cpp
  src/widgets/projectexplorer.cpp
  src/widgets/runconfigurationswidget.cpp
  src/widgets/QuickFileOpenWidget.cpp
)

set(HEADERS
  src/mainwindow.h
  src/mimetypehelper.h
  src/highlighter/JSLexer.h
  src/widgets/codeeditor.h
  src/widgets/directorytreewidgetitem.h
  src/widgets/npmstatusbar.h
  src/widgets/projectexplorer.h
  src/widgets/runconfigurationswidget.h
  src/widgets/QuickFileOpenWidget.h
)

QT5_ADD_RESOURCES(RESOURCES resources.qrc)

# Tell CMake to create the helloworld executable
ADD_EXECUTABLE(nodeide WIN32 ${SOURCE} ${HEADERS} ${RESOURCES})

TARGET_COMPILE_FEATURES(nodeide PRIVATE cxx_range_for)

# Use the Widgets module from Qt 5.
TARGET_LINK_LIBRARIES(nodeide ${QSCINTILLA_LIBRARY} Qt5::Widgets)

INSTALL(TARGETS nodeide DESTINATION bin)

SET(CPACK_GENERATOR "RPM")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Paál Gyula") #required

INCLUDE(CPack)
