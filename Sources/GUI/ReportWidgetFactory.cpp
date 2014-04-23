#include "ReportWidgetFactory.h"

ReportWidgetFactory::ReportWidgetFactory()
{
}
/**
 * @brief Create the ReportWidget in matching with the given report.
 * @param report
 * @return the ReportWidget for the given report
 */
ReportWidget *ReportWidgetFactory::buildReportWidget(Report *report)
{
	ReportWidget * widget = new ReportWidget(report);
	switch(report->getType())
	{
		case BACKTESTING:
			widget->setTitle("Backtesting report");
			widget->setIcon(RES_FOLDER+"/Icons/backtestingReport.png");
			break;
		case CORRELATION:
			widget->setTitle("Correlation report");
			widget->setIcon(RES_FOLDER+"/Icons/correlationReport.png");
			break;
		case GARCH:
			widget->setTitle("GARCH report");
			widget->setIcon(RES_FOLDER+"/Icons/garchReport.png");
			break;
		case STATISTICS:
			widget->setTitle("Statistic report");
			widget->setIcon(RES_FOLDER+"/Icons/statsReport.png");
			break;
		case VAR:
			widget->setTitle("VaR report");
			widget->setIcon(RES_FOLDER+"/Icons/varReport.png");
			break;
	}

	return widget;
}
