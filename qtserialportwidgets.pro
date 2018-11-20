#-------------------------------------------------
#
# Project created by QtCreator 2014-08-01T12:01:40
#
#-------------------------------------------------

TARGET = qtserialportwidgets
TEMPLATE = lib
#CONFIG += staticlib
DEFINES += QTSERIALPORTWIDGETS_LIBRARY

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build
DESTDIR = bin

include(qtserialportwidgets.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    serialportselectormenu.h

SOURCES += \
