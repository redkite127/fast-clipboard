TEMPLATE = app
QT = gui core xml network
CONFIG += qt warn_on resources debug
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui ui/edit.ui
HEADERS = src/mainwindowimpl.h src/editimpl.h src/FCxml.h src/NetworksXml.h
SOURCES = src/mainwindowimpl.cpp \
 src/main.cpp \
 src/editimpl.cpp \
 src/FCxml.cpp \
 src/NetworksXml.cpp
RESOURCES += res.qrc
RC_FILES =  myapp.rc
