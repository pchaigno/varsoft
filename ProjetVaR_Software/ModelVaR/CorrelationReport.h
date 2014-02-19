#pragma once

#include <QString>
#include "Report.h"

class CorrelationReport: public Report {
public:
    CorrelationReport(QString docxPath, QString pdfPath);
};