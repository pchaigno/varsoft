#pragma once

#include "Report.h"
#include "DocxGenerator.h"
#include <QString>

class ReportFactory {
protected:
	DocxGenerator docxGenerator;

private:
	QString docxFile;
	QString pdfFile;

public:
	ReportFactory(QString docxFile, QString pdfFile);
	Report generateReport();
	virtual DocxGenerator& generateDOCX() const =0;
	void generatePDF();
};