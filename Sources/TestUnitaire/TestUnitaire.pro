#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T18:13:24
#
#-------------------------------------------------

QT += testlib sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
	TestAsset.cpp \
	TestPortfolio.cpp \
	main.cpp \
	TestReport.cpp \
	TestSQLiteManagers.cpp \
	#TestPortfolioItemModel.cpp \
	TestVaRHistorical.cpp \
	TestCreateAsset.cpp \
	TestArchiveManagers.cpp \
	TestVaRRiskmetrics.cpp \
	TestVaRGarch.cpp \
	TestBacktesting.cpp \
	TestMathFunctions.cpp \
	TestRInterface.cpp

HEADERS += \
	TestAsset.h \
	TestReport.h \
	TestPortfolio.h \
	TestSQLiteManagers.h \
	#TestPortfolioItemModel.h \
	TestVaRHistorical.h \
	TestCreateAsset.h \
	TestArchiveManagers.h \
	TestVaRRiskmetrics.h \
	TestVaRGarch.h \
	TestBacktesting.h \
	TestMathFunctions.h \
	TestRInterface.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += UNITTEST

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qcustomplot/release/ -lqcustomplotd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qcustomplot/debug/ -lqcustomplotd
else:unix: LIBS += -L$$OUT_PWD/../qcustomplot/ -lqcustomplotd

INCLUDEPATH += $$PWD/../qcustomplot
DEPENDPATH += $$PWD/../qcustomplot

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../quazip/quazip/release/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../quazip/quazip/debug/ -lquazip
else:unix: LIBS += -L$$OUT_PWD/../quazip/quazip/ -lquazip

INCLUDEPATH += $$PWD/../quazip/quazip
DEPENDPATH += $$PWD/../quazip/quazip
