TEMPLATE = app
QT = gui core xml network
CONFIG += qt warn_on resources debug_and_release
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui ui/edit.ui ui/aboutFC.ui ui/QChooseGUIStyle.ui
HEADERS = src/mainwindowimpl.h \
 src/editimpl.h \
 src/FCxml.h \
 src/NetworksXml.h \
 src/aboutFCimpl.h \
 qled.h \
 src/QChooseGUIStyleImpl.h
SOURCES = src/mainwindowimpl.cpp \
 src/main.cpp \
 src/editimpl.cpp \
 src/FCxml.cpp \
 src/NetworksXml.cpp \
 src/aboutFCimpl.cpp \
 qled.cpp \
 src/QChooseGUIStyleImpl.cpp
RESOURCES += res.qrc
