#ifndef H_STATISTICSREPORT
#define H_STATISTICSREPORT

#include "Report.h"

class StatisticsReport: public Report {
public:
    StatisticsReport(QString docxPath, QString pdfPath);
};

#endif
