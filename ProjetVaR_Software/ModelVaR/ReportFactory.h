#pragma once

#include "Report.h"
#include "DocxGenerator.h"
#include <string>

using namespace std;

class ReportFactory {
protected:
	DocxGenerator docxGenerator;

private:
	string docxPath;
	string pdfPath;

public:
	ReportFactory(string docxPath, string pdfPath);
	Report generateReport();
	virtual DocxGenerator& generateDOCX() const =0;
	void generatePDF();
};