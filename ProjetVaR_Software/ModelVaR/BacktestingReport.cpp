#include "BacktestingReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
BacktestingReport::BacktestingReport() {

}

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
BacktestingReport::BacktestingReport(QString docxFile, QString pdfFile): Report(docxFile, pdfFile) {

}

/**
 * @brief Constructor
 * @param id The id of the report in the database.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
BacktestingReport::BacktestingReport(int id, QString docxFile, QString pdfFile): Report(id, docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType BacktestingReport::getType() const {
    return BACKTESTING;
}

QString BacktestingReport::getTemplateFile() const
{
    return "";
}
