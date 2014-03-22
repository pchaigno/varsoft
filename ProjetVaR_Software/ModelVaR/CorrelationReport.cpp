#include "CorrelationReport.h"

/**
 * @brief Empty constructor
 * Should only be used by Qt containers.
 */
CorrelationReport::CorrelationReport() {

}

/**
 * @brief Constructor
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
CorrelationReport::CorrelationReport(QString docxPath, QString pdfPath): Report(docxPath, pdfPath) {

}

/**
 * @brief Constructor
 * @param id The id of the report in the database.
 * @param docxPath The location of the DOCX file on the disk.
 * @param pdfPath The location of the PDF file on the disk.
 */
CorrelationReport::CorrelationReport(int id, QString docxFile, QString pdfFile): Report(id, docxFile, pdfFile) {

}

/**
 * @brief Accessor to the type of the report.
 * @return The type of the report.
 */
ReportType CorrelationReport::getType() const {
    return CORRELATION;
}

QString CorrelationReport::getTemplateFile() const
{
    return "";
}
