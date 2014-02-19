#pragma once

#include <QString>
#include "ReportGenerator.h"

class DocxGenerator: public ReportGenerator {
public:
	DocxGenerator(QString location);
	virtual void generate();
	void convertToPDF();
};