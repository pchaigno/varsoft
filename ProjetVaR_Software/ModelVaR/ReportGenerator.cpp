#include "ReportGenerator.h"


ReportGenerator::ReportGenerator(Report *report) : report(report)
{

}

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

Report *ReportGenerator::getReport()
{
	return report;
}
