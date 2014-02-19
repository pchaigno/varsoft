#ifndef H_STATISTICSREPORTFACTORY
#define H_STATISTICSREPORTFACTORY

#include "ReportFactory.h"

class StatisticsReportFactory: public ReportFactory {
public:
    StatisticsReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};

#endif
