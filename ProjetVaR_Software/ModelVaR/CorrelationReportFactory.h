#ifndef H_CORRELATIONREPORTFACTORY
#define H_CORRELATIONREPORTFACTORY

#include "ReportFactory.h"
#include <QString>

class CorrelationReportFactory: public ReportFactory {
public:
    CorrelationReportFactory(QString docxPath, QString pdfPath);
	virtual DocxGenerator& generateDOCX();
};

#endif
