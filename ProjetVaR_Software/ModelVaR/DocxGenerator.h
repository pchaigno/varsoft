#pragma once

#include <string>
#include "ReportGenerator.h"

using namespace std;

class DocxGenerator: public ReportGenerator {
public:
	DocxGenerator(string location);
	virtual void generate();
	void convertToPDF();
};