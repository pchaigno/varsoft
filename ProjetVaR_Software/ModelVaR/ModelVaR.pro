#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T17:09:02
#
#-------------------------------------------------

QT       -= gui

TARGET = ModelVaR
TEMPLATE = lib

DEFINES += MODELVAR_LIBRARY

SOURCES += ModelVaR.cpp

HEADERS += ModelVaR.h\
        ModelVaR_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
