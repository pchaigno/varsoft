#include "ReportGenerator.h"


ReportGenerator::ReportGenerator(Report *report) : report(report)
{
	connect(this,SIGNAL(finished()),report,SLOT(filesGenerationFinish()));
	connect(report,SIGNAL(filesNotOk()),this,SLOT(errorReport()));
}
/**
 * @brief Call the virtual pure method generate() and emits the signal error(QString) if
 * the generate method raises an exception.
 */
void ReportGenerator::run()
{
	try
	{
		generate();
	}
	catch (std::exception & e)
	{
		emit error(e.what());
	}
}
/**
 * @brief Getter of the report which is generated.
 * @return the report
 */
Report *ReportGenerator::getReport()
{
	return report;
}

void ReportGenerator::errorReport()
{
	emit error("Error in the generation, report has not been created.");
}
