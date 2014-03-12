#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T17:09:16
#
#-------------------------------------------------

QT       += core gui printsupport

GTCONFIG +=console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QMAKE_CXXFLAGS += -std=c++11

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    NewPortfolioDialog.cpp \
    qcustomplot.cpp

HEADERS  += MainWindow.h \
    NewPortfolioDialog.h \
    qcustomplot.h

FORMS    += MainWindow.ui \
    NewPortfolioDialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR
