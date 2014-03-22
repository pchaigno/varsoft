#pragma once

#include "Report.h"
#include "DocxGenerator.h"
#include <QString>

class ReportFactory {
public:
    ReportFactory();
    ReportFactory(QString&,QString &);

    Report *buildReport();

protected:
    virtual Report * getReport() =0;
    virtual ReportDataJson createJson() = 0;

};
