#pragma once

#include <string>

using namespace std;

class Report {
private:
	string docxPath;
	string pdfPath;

public:
	Report(string docxPath, string pdfPath);
	string getDOCXPath() const;
	string getPDFPath() const;
};