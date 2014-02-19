#pragma once

#include "Report.h"

class StatisticsReport: public Report {
public:
    StatisticsReport(QString docxPath, QString pdfPath);
};