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
	report/Report.cpp \
	report/GarchReport.cpp \
	report/VaRReport.cpp \
	report/BacktestingReport.cpp \
	report/StatisticsReport.cpp \
	report/CorrelationReport.cpp \
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
	VaRReportFactory.cpp \
	GarchReportFactory.cpp \
	ImportNewData.cpp \
	IImport.cpp \
	MathFunctions.cpp \
	ArchiveManager.cpp \
	ExportManager.cpp \
	ImportManager.cpp \
	ReportDataJson.cpp \
	ReportGenerator.cpp \
	ReportException.cpp \
	GetStartEndDates.cpp \
	reportFactory/ReportFactory.cpp \
	reportFactory/BacktestingReportFactory.cpp \
	reportFactory/StatisticsReportFactory.cpp \
	reportFactory/CorrelationReportFactory.cpp

HEADERS +=\
	Asset.h \
	Portfolio.h \
	report/Report.h \
	report/GarchReport.h \
	report/VaRReport.h \
	report/BacktestingReport.h \
	report/StatisticsReport.h \
	report/CorrelationReport.h \
	AssetsFactory.h \
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
	VaRReportFactory.h \
	GarchReportFactory.h \
	ImportNewData.h \
	IImport.h \
	GetStartEndDates.h \
	ReportDataJson.h \
	ReportException.h \
	ArchiveManager.h \
	ExportManager.h \
	ImportManager.h \
	ExportException.h \
	ImportException.h \
	MathFunctions.h \
	reportFactory/ReportFactory.h \
	reportFactory/BacktestingReportFactory.h \
	reportFactory/StatisticsReportFactory.h \
	reportFactory/CorrelationReportFactory.h \
	exceptions/CannotOpenFileException.h \
	exceptions/CreateAssetException.h \
	exceptions/PortfolioCalculationException.h \
	exceptions/InvalidDefinitionPeriodException.h \
	exceptions/NonexistentAssetException.h \
	exceptions/IdAlreadyAttributedException.h \
	exceptions/ReportAlreadyCreatedException.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../quazip/quazip/release/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../quazip/quazip/debug/ -lquazip
else:unix: LIBS += -L$$OUT_PWD/../quazip/quazip/ -lquazip

INCLUDEPATH += $$PWD/../quazip/quazip
DEPENDPATH += $$PWD/../quazip/quazip
