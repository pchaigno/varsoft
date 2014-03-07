#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T18:13:24
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    TestAsset.cpp \
    TestPortfolio.cpp \
    main.cpp \
    TestVaRHistorical.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR

HEADERS += \
    TestAsset.h \
    TestPortfolio.h \
    TestVaRHistorical.h
