#include "ReportGenerator.h"


ReportGenerator::ReportGenerator(Report *report) : report(report)
{

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
