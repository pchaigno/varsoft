#pragma once

#include "ReportFactory.h"
#include <QString>

class StatisticsReportFactory: public ReportFactory {
public:
	StatisticsReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};