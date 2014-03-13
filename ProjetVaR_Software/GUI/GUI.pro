#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T17:09:16
#
#-------------------------------------------------

QT       += core gui printsupport sql

GTCONFIG +=console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QMAKE_CXXFLAGS += -std=c++11

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    qcustomplot.cpp \
    NewPortfolioWizard.cpp

HEADERS  += MainWindow.h \
    qcustomplot.h \
    NewPortfolioWizard.h

FORMS    += MainWindow.ui \
    NewPortfolioWizard.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR
