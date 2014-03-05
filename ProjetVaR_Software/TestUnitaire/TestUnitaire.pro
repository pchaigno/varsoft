#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T18:13:24
#
#-------------------------------------------------

QT       += testlib
QT += widgets

QT       -= gui

TARGET = tst_TestUnitaireTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    TestImportNewData.cpp \
    TestImportData.cpp \
    main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR

HEADERS += \
    TestImportNewData.h \
    TestImportData.h
