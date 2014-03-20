#include "DocxGenerator.h"

/**
 * @brief Constructor
 * @param location The path to the DOCX file to generate.
 * @param templateFile The template file of the report
 * @param data the json data
 */
DocxGenerator::DocxGenerator(Report *report) {
    this->report=report;
}

/**
 * @brief Generates the DOCX file;
 */
void DocxGenerator::generate() {
    QProcess docx;
    docx.start("java DocxGenerator", QStringList() << report->getTemplateFile() << report->getTemplateFile());
    if (!docx.waitForStarted())
     return false;

    docx.write(report->getDataJson().toJson(QJsonDocument::Compact));
    docx.closeWriteChannel();

    docx.waitForFinished();
}
