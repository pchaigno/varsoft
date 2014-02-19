#pragma once

#include "ReportFactory.h"
#include <QString>

class StatisticsReportFactory: public ReportFactory {
public:
	StatisticsReportFactory(QString docxFile, QString pdfFile);
	virtual DocxGenerator& generateDOCX();
};