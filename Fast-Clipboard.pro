TEMPLATE = app
QT = gui core network xml
CONFIG += qt release warn_on resources
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/FastClipboard.ui libs/ui/QChooseGUIStyle.ui ui/edit.ui ui/aboutFC.ui
HEADERS = src/FastClipboardImpl.h \
 libs/src/QChooseGUIStyleImpl.h \
 src/NetworksXml.h \
 src/EditImpl.h \
 src/aboutFCimpl.h \
 src/FCxml.h \
 libs/src/qledbutton.h \
 libs/src/qled.h
SOURCES = src/FastClipboardImpl.cpp \
 src/main.cpp \
 libs/src/QChooseGUIStyleImpl.cpp \
 src/EditImpl.cpp \
 src/FCxml.cpp \
 src/NetworksXml.cpp \
 src/aboutFCimpl.cpp \
 libs/src/qledbutton.cpp \
 libs/src/qled.cpp
RESOURCES += res.qrc
RC_FILE = myapp.rc
