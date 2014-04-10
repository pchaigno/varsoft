#include "ReportWidgetFactory.h"

ReportWidgetFactory::ReportWidgetFactory()
{
}

ReportWidget *ReportWidgetFactory::buildReportWidget(Report *report)
{
	ReportWidget * widget = new ReportWidget(report);
	switch(report->getType())
	{
		case BACKTESTING:
			widget->setTitle("Backtesting report");
			widget->setIcon("../Resources/Icons/backtestingReport.png");
			break;
		case CORRELATION:
			widget->setTitle("Correlation report");
			widget->setIcon("../Resources/Icons/correlationReport.png");
			break;
		case GARCH:
			widget->setTitle("GARCH report");
			widget->setIcon("../Resources/Icons/garchReport.png");
			break;
		case STATISTICS:
			widget->setTitle("Statistic report");
			widget->setIcon("../Resources/Icons/statsReport.png");
			break;
		case VAR:
			widget->setTitle("VaR report");
			widget->setIcon("../Resources/Icons/varReport.png");
			break;
	}

	return widget;
}
