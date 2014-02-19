#pragma once

#include <QString>
#include "ReportGenerator.h"

using namespace std;

class DocxGenerator: public ReportGenerator {
public:
    DocxGenerator(QString location);
	virtual void generate();
	void convertToPDF();
};
