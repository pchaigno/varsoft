#include "StatisticsReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
StatisticsReport::StatisticsReport() {

}

StatisticsReport::StatisticsReport(QString docxFile, QString pdfFile) : Report(docxFile,pdfFile)
{

}

/**
 * @brief Constructor
 * @param id The id of the report in the database.
 */
StatisticsReport::StatisticsReport(int id,  QString docxFile, QString pdfFile): Report(id,docxFile,pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType StatisticsReport::getType() const {
    return STATISTICS;
}
/**
 * @brief StatisticsReport::getTemplateFile
 * Getter of the templateFile path
 * @return a QString of the template path
 */
QString StatisticsReport::getTemplateFile() const
{
    return QString("../resources/ReportTemplate/statisticTemplate.docx");
}
