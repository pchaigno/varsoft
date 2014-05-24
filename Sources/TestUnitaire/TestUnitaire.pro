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
	TestImportNewData.cpp \
	TestAsset.cpp \
	TestPortfolio.cpp \
	main.cpp \
	TestReport.cpp \
	TestSQLiteManagers.cpp \
	TestPortfolioItemModel.cpp \
	TestVaRHistorical.cpp \
	TestArchiveManagers.cpp \
	TestBacktesting.cpp \
	TestVaRRiskmetrics.cpp \
	TestMathFunctions.cpp \
	TestRInterface.cpp

HEADERS += \
	TestImportNewData.h \
	TestAsset.h \
	TestReport.h \
	TestPortfolio.h \
	TestSQLiteManagers.h \
	TestPortfolioItemModel.h \
	TestVaRHistorical.h \
	TestArchiveManagers.h \
	TestBacktesting.h \
	TestVaRRiskmetrics.h \
	TestMathFunctions.h \
	TestRInterface.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += UNITTEST

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/release/ -lModelVaR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelVaR/debug/ -lModelVaR
else:unix: LIBS += -L$$OUT_PWD/../ModelVaR/ -lModelVaR

INCLUDEPATH += $$PWD/../ModelVaR
DEPENDPATH += $$PWD/../ModelVaR


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../quazip/quazip/release/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../quazip/quazip/debug/ -lquazip
else:unix: LIBS += -L$$OUT_PWD/../quazip/quazip/ -lquazip

INCLUDEPATH += $$PWD/../quazip/quazip
DEPENDPATH += $$PWD/../quazip/quazip
