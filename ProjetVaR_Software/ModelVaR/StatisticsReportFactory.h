#pragma once

#include "ReportFactory.h"
#include <QString>
#include "Portfolio.h"
#include "StatisticsReport.h"

class StatisticsReportFactory: public ReportFactory {
public:
    StatisticsReportFactory(Portfolio *portfolio);

protected:

    virtual Report * getReport();
    virtual ReportDataJson createJson();

    Portfolio * portfolio;


};
