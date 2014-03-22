#include "StatisticsReportFactory.h"

/**
 * @brief Constructor
 */
StatisticsReportFactory::StatisticsReportFactory(Portfolio * portfolio):
    ReportFactory() {
    this->portfolio=portfolio;
}

Report *StatisticsReportFactory::getReport()
{
    return new StatisticsReport(QString("../resources/Reports/statisticReport.docx"),QString());
}

ReportDataJson StatisticsReportFactory::createJson()
{
    ReportDataJson data;

    data.addText("portefeuilleName",portfolio->getName());

    return data;
}
