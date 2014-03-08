#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T17:09:02
#
#-------------------------------------------------

QT       -= gui

TARGET = ModelVaR
TEMPLATE = lib

# To compile under Linux
#QMAKE_CXXFLAGS += -std=c++11
# For QSQL
QT += sql

DEFINES += MODELVAR_LIBRARY

SOURCES += \
    Asset.cpp \
    Portfolio.cpp \
    Report.cpp \
    GarchReport.cpp \
    VaRReport.cpp \
    BacktestingReport.cpp \
    StatisticsReport.cpp \
    CorrelationReport.cpp \
    AssetsFactory.cpp \
    VaRAlgorithm.cpp \
    VaRHistorical.cpp \
    VaRGarch.cpp \
    VaRRiskmetrics.cpp \
    GarchModel.cpp \
    ModelVaR.cpp \
    SQLiteManager.cpp \
    SessionSaver.cpp \
    SessionBuilder.cpp \
    RInterface.cpp \
    Backtesting.cpp \
    DocxGenerator.cpp \
    ReportFactory.cpp \
    BacktestingReportFactory.cpp \
    VaRReportFactory.cpp \
    GarchReportFactory.cpp \
    StatisticsReportFactory.cpp \
    CorrelationReportFactory.cpp

HEADERS +=\
    Asset.h \
    Portfolio.h \
    Report.h \
    GarchReport.h \
    VaRReport.h \
    BacktestingReport.h \
    StatisticsReport.h \
    CorrelationReport.h \
    AssetsFactory.h \
    IdAlreadyAttributedException.h \
    VaRAlgorithm.h \
    VaRHistorical.h \
    VaRGarch.h \
    VaRRiskmetrics.h \
    GarchModel.h \
    ModelVaR.h \
    ModelVaR_global.h \
    SQLiteManager.h \
    SessionSaver.h \
    SessionBuilder.h \
    RInterface.h \
    Backtesting.h \
    DocxGenerator.h \
    ReportGenerator.h \
    ReportFactory.h \
    BacktestingReportFactory.h \
    VaRReportFactory.h \
    GarchReportFactory.h \
    StatisticsReportFactory.h \
    CorrelationReportFactory.h \
    CannotOpenFileException.h \
    PortfolioCalculationException.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
