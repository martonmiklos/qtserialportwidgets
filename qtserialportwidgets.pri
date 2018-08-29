QT       += core widgets serialport

INCLUDEPATH +=  $$PWD

SOURCES += \
    $$PWD/databitscombobox.cpp \
    $$PWD/flowcontrolcombobox.cpp \
    $$PWD/paritycombobox.cpp \
    $$PWD/stopbitscombobox.cpp \
    $$PWD/baudratecombobox.cpp \
    $$PWD/serialportcombobox.cpp \
    $$PWD/serialportsettingsdialog.cpp \
    $$PWD/serialportselectormenu.cpp

HEADERS += \
    $$PWD/flowcontrolcombobox.h \
    $$PWD/paritycombobox.h \
    $$PWD/stopbitscombobox.h \
    $$PWD/baudratecombobox.h \
    $$PWD/serialportcombobox.h \
    $$PWD/databitscombobox.h \
    $$PWD/serialportsettingsdialog.h \
    $$PWD/serialportselectormenu.h

FORMS += \
    $$PWD/serialportsettingsdialog.ui

