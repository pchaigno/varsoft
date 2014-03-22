#include "ReportFactory.h"

/**
 * @brief ReportFactory::ReportFactory
 */
ReportFactory::ReportFactory(){

}

ReportFactory::ReportFactory(QString &, QString &)
{

}

Report *ReportFactory::buildReport()
{
    Report * report = getReport();
    report->setDataJson(createJson());
    return report;
}
