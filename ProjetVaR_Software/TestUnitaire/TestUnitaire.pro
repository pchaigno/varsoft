#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T18:13:24
#
#-------------------------------------------------

QT       += testlib
QT       += widgets
QT       -= gui
# For QSQL
QT += sql

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    TestImportNewData.cpp \
    TestImportData.cpp \
    TestAsset.cpp \
	TestReport.cpp \
    TestPortfolio.cpp \
	TestSQLiteManagers.cpp \
    main.cpp

HEADERS += \
    TestImportNewData.h \
    TestImportData.h \
    TestAsset.h \
	TestReport.h \
	TestPortfolio.h \
	TestSQLiteManagers.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR
