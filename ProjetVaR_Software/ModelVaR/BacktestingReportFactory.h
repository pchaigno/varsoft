#pragma once

#include "ReportFactory.h"

class BacktestingReportFactory: public ReportFactory {
public:
	BacktestingReportFactory(QString docxFile, QString pdfFile);
	virtual DocxGenerator& generateDOCX();
};
