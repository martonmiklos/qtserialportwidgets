QT       += core gui 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH +=  build \
                $$PWD

greaterThan(QT_MAJOR_VERSION, 4) {
    LIBS += -lQt5SerialPort
} else {
    LIBS += -lqtserialport
} 


SOURCES += 	$$PWD/serialportsettingsdialog.cpp \
                        $$PWD/serialportwidgets.cpp
			
HEADERS += 	$$PWD/serialportsettingsdialog.h \
                        $$PWD/serialportwidgets.h
			
FORMS += 	$$PWD/serialportsettingsdialog.ui

