#include "ReportGenerator.h"


ReportGenerator::ReportGenerator(Report *report) : report(report)
{

}

void ReportGenerator::run()
{
	generate();
}

Report *ReportGenerator::getReport()
{
	return report;
}
