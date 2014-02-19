#ifndef H_CORRELATIONREPORT
#define H_CORRELATIONREPORT

#include <QString>
#include "Report.h"

class CorrelationReport: public Report {
public:
    CorrelationReport(QString docxPath, QString pdfPath);
};
#endif
