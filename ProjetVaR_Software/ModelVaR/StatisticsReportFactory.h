#pragma once

#include "ReportFactory.h"

class StatisticsReportFactory: public ReportFactory {
public:
    StatisticsReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};