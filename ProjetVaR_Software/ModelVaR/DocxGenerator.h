#ifndef H_DOCXGENERATOR
#define H_DOCXGENERATOR

#include <QString>
#include "ReportGenerator.h"

using namespace std;

class DocxGenerator: public ReportGenerator {
public:
    DocxGenerator(QString location);
	virtual void generate();
	void convertToPDF();
};
#endif
