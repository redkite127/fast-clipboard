TEMPLATE = app
QT = gui core xml
CONFIG += qt release warn_on resources
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui ui/edit.ui
HEADERS = src/mainwindowimpl.h src/editimpl.h src/FCxml.h
SOURCES = src/mainwindowimpl.cpp src/main.cpp src/editimpl.cpp src/FCxml.cpp
RESOURCES += res.qrc
