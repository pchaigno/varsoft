#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T17:09:02
#
#-------------------------------------------------

QT += sql printsupport

TARGET = ModelVaR
TEMPLATE = lib


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
	ImportNewData.cpp \
	IImport.cpp \
	PortfolioItemModel.cpp \
	CorrelationReportFactory.cpp \
	PortfolioViewModel.cpp \
	ReportDataJson.cpp \
	ReportGenerator.cpp \
	ReportException.cpp \
	GetStartEndDates.cpp

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
	ImportNewData.h \
	CannotOpenFileException.h \
	IImport.h \
	PortfolioItemModel.h \
	PortfolioCalculationException.h \
	GetStartEndDates.h \
	PortfolioViewModel.h \
	ReportDataJson.h \
	ReportException.h \
	InvalidDefinitionPeriodException.h \
	ImportException.h \
	ReportAlreadyCreatedException.h

unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/lib
	}
	INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qcustomplot/release/ -lqcustomplotd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qcustomplot/debug/ -lqcustomplotd
else:unix: LIBS += -L$$OUT_PWD/../qcustomplot/ -lqcustomplotd

INCLUDEPATH += $$PWD/../qcustomplot
DEPENDPATH += $$PWD/../qcustomplot
