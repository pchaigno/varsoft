#pragma once

#include <string>
#include "IdAlreadyAttributedException.h"

using namespace std;

enum ReportType {
	NONE = 0,
	BACKTESTING,
	CORRELATION,
	GARCH,
	STATISTICS,
	VAR
};

class Report {
private:
	int id;
	string docxFile;
	string pdfFile;

public:
	Report(string docxFile, string pdfFile);
	Report(int id, string docxFile, string pdfFile);
	void init(int id, string docxFile, string pdfFile);

	int getId() const;
	void setId(int id);
	string getDOCXFile() const;
	string getPDFFile() const;
	// TODO Any way to make it abstract?
	virtual ReportType getType() const;
};