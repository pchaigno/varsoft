#pragma once

#include "Report.h"
#include "DocxGenerator.h"
#include <QString>

class ReportFactory {
protected:
	DocxGenerator docxGenerator;

private:
	QString docxPath;
	QString pdfPath;

public:
	ReportFactory(QString docxPath, QString pdfPath);
	Report generateReport();
	virtual DocxGenerator& generateDOCX() const =0;
	void generatePDF();
};