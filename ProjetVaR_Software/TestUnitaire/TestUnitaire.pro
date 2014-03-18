#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T18:13:24
#
#-------------------------------------------------

QT       += testlib
QT       -= gui
# For QSQL
QT += sql

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += TestPortfolio.cpp \
    TestAsset.cpp \
    main.cpp \
    TestReport.cpp \
    TestSQLiteManagers.cpp \
    TestPortfolioItemModel.cpp

HEADERS += \
    TestPortfolio.h \
    TestAsset.h \
    TestReport.h \
    TestSQLiteManagers.h \
    TestPortfolioItemModel.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += UNITTEST

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR
