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
	AssetsFactory.cpp \
	ModelVaR.cpp \
	SQLiteManager.cpp \
	SessionSaver.cpp \
	SessionBuilder.cpp \
	ArchiveManager.cpp \
	ExportManager.cpp \
	ImportManager.cpp \
	report/Report.cpp \
	report/GarchReport.cpp \
	report/VaRReport.cpp \
	report/BacktestingReport.cpp \
	report/StatisticsReport.cpp \
	report/CorrelationReport.cpp \
	report/ReportDataJson.cpp \
	report/DocxGenerator.cpp \
	report/ReportGenerator.cpp \
	math/VaRAlgorithm.cpp \
	math/VaRHistorical.cpp \
	math/VaRGarch.cpp \
	math/VaRRiskmetrics.cpp \
	math/GarchModel.cpp \
	math/RInterface.cpp \
	math/Backtesting.cpp \
	math/MathFunctions.cpp \
	import/ImportNewData.cpp \
	import/IImport.cpp \
	import/GetStartEndDates.cpp \
	reportFactory/ReportFactory.cpp \
	reportFactory/GarchReportFactory.cpp \
	reportFactory/VaRReportFactory.cpp \
	reportFactory/BacktestingReportFactory.cpp \
	reportFactory/StatisticsReportFactory.cpp \
	reportFactory/CorrelationReportFactory.cpp \
	exceptions/ReportException.cpp \
	CreateAsset.cpp \
	CorrelationResults.cpp \
	Savable.cpp


HEADERS +=\
	Asset.h \
	Portfolio.h \
	AssetsFactory.h \
	ModelVaR.h \
	ModelVaR_global.h \
	SQLiteManager.h \
	SessionSaver.h \
	SessionBuilder.h \
	CreateAsset.h \
	ArchiveManager.h \
	ExportManager.h \
	ImportManager.h \
	exceptions/ReportException.h \
	exceptions/ReportAlreadyCreatedException.h \
	exceptions/PortfolioCalculationException.h \
	exceptions/NonexistentAssetException.h \
	exceptions/InvalidDefinitionPeriodException.h \
	exceptions/ImportException.h \
	exceptions/IdAlreadyAttributedException.h \
	exceptions/ExportException.h \
	exceptions/CreateAssetException.h \
	exceptions/CannotOpenFileException.h \
	report/Report.h \
	report/ReportGenerator.h \
	report/ReportDataJson.h \
	report/GarchReport.h \
	report/VaRReport.h \
	report/BacktestingReport.h \
	report/StatisticsReport.h \
	report/CorrelationReport.h \
	report/DocxGenerator.h \
	import/ImportNewData.h \
	import/IImport.h \
	import/GetStartEndDates.h \
	import/ImportException.h \
	math/VaRAlgorithm.h \
	math/VaRHistorical.h \
	math/VaRGarch.h \
	math/VaRRiskmetrics.h \
	math/GarchModel.h \
	math/RInterface.h \
	math/Backtesting.h \
	math/MathFunctions.h \
	reportFactory/VaRReportFactory.h \
	reportFactory/ReportFactory.h \
	reportFactory/BacktestingReportFactory.h \
	reportFactory/StatisticsReportFactory.h \
	reportFactory/CorrelationReportFactory.h \
	reportFactory/GarchReportFactory.h \
	exceptions/CannotOpenFileException.h \
	exceptions/CreateAssetException.h \
	exceptions/PortfolioCalculationException.h \
	exceptions/InvalidDefinitionPeriodException.h \
	exceptions/NonexistentAssetException.h \
	exceptions/IdAlreadyAttributedException.h \
	exceptions/ExportException.h \
	exceptions/ReportException.h \
	exceptions/ReportAlreadyCreatedException.h \
	Savable.h \
	CorrelationResults.h \
	Savable.h \
	SessionFolderMissingException.h

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

RESOURCES +=
