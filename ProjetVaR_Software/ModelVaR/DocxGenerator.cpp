#include "DocxGenerator.h"

/**
 * @brief Constructor
 * @param location The path to the DOCX file to generate.
 */
DocxGenerator::DocxGenerator(QString location, QString templateFile, QJsonDocument doc) {
    this->location=location;
    this->templateFile=templateFile;
    this->doc=doc;
}

/**
 * @brief Generates the DOCX file;
 */
void DocxGenerator::generate() {
    QProcess docx;
    docx.start("java DocxGenerator", QStringList() << templateFile << location);
    if (!docx.waitForStarted())
     return false;

    docx.write(doc.toJson(QJsonDocument::Compact));
    docx.closeWriteChannel();

    docx.waitForFinished();
}
