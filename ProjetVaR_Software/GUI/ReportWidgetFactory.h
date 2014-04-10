#ifndef REPORTWIDGETFACTORY_H
#define REPORTWIDGETFACTORY_H

#include "ReportWidget.h"

class ReportWidgetFactory
{
public:
	static ReportWidget *buildReportWidget(Report * report);
private:
	ReportWidgetFactory();
};

#endif // REPORTWIDGETFACTORY_H
