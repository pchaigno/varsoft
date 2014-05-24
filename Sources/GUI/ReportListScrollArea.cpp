/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.
 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ReportListScrollArea.h"
#include "ui_ReportListScrollArea.h"

ReportListScrollArea::ReportListScrollArea(QWidget *parent) :
	QScrollArea(parent),
	ui(new Ui::ReportListScrollArea)
{
	ui->setupUi(this);
	layout = new FlowLayout();
	this->setLayout(layout);
	current=NULL;
}

ReportListScrollArea::~ReportListScrollArea()
{
	delete ui;
}

void ReportListScrollArea::removeReport(Report *report)
{
	foreach(ReportWidget * repWid, portfolioReportWidgets[current])
	{
		Report * rep = repWid->getReport();
		if (*report==*rep)
		{
			removeReportWidget(repWid);
		}
	}
}

void ReportListScrollArea::deleteAll()
{
	foreach(ReportWidget * repWid, portfolioReportWidgets[current])
	{
		removeReportWidget(repWid);
	}
}

/**
 * @brief Initialize the layout with the report of the portfolio given.
 * @param Portfolio which you want to display reports.
 */
void ReportListScrollArea::setCurrent(Portfolio *portfolio)
{
	if (current!=NULL)
	{
		disconnect(current,SIGNAL(reportAdded(Report*)),this,SLOT(addReport(Report*)));
		disconnect(current,SIGNAL(reportRemoved()),this,SLOT(updateReportWidgetList()));
	}
	clearLayout();
	current=portfolio;
	updateLayout();
	connect(portfolio,SIGNAL(reportAdded(Report*)),this,SLOT(addReport(Report*)));
	connect(portfolio,SIGNAL(reportRemoved()),this,SLOT(updateReportWidgetList()));
}

/**
 * @brief Construct the ReportWidget of the report param and display for the current portfolio
 * @param report
 */
void ReportListScrollArea::addReport(Report *report)
{
	ReportWidget * reportWidget = ReportWidgetFactory::buildReportWidget(report);
	connect(reportWidget,SIGNAL(deleteRequest()),this,SLOT(removeReportWidget()));
	portfolioReportWidgets[current].append(reportWidget);
	addToLayout(reportWidget);
}

void ReportListScrollArea::removeReportWidget()
{
	ReportWidget *reportWidget = qobject_cast<ReportWidget *>(sender());
	if (reportWidget)
		removeReportWidget(reportWidget);
}
/**
 * @brief Remove the ReportWidget and its reports from the layout and the portfolio
 * @param reportWidget
 */
void ReportListScrollArea::removeReportWidget(ReportWidget *reportWidget)
{
	portfolioReportWidgets[current].removeOne(reportWidget);
	Report * report = reportWidget->getReport();
	current->removeReport(report);
	updateLayout();
}

/**
 * @brief Add the reportWidget to the layout
 * @param reportWidget
 */
void ReportListScrollArea::addToLayout(ReportWidget *reportWidget)
{
	layout->addWidget(reportWidget);
}

/**
 * @brief Clear the layout and load the ReportWidget of the current Portfolio
 */
void ReportListScrollArea::updateLayout()
{
	clearLayout(false);
	QList<ReportWidget*> listReportCurrentPortfolio = portfolioReportWidgets[current];
	foreach(ReportWidget* repWid,listReportCurrentPortfolio)
	{
		addToLayout(repWid);
	}
}

void ReportListScrollArea::updateReportWidgetList()
{
	clearLayout(true);
	portfolioReportWidgets[current].clear();
	foreach(Report * report, current->getReports())
	{
		addReport(report);
	}
}

/**
 * @brief Clear the main layout
 */
void ReportListScrollArea::clearLayout(bool deleteWidgets)
{
	clearLayout(layout,deleteWidgets);
}

void ReportListScrollArea::clearLayout(QLayout *layout, bool deleteWidgets)
{
	while (QLayoutItem* item = layout->takeAt(0)) {
		if (deleteWidgets) {
			if (QWidget* widget = item->widget())
				delete widget;
		} else
			item->widget()->setParent(NULL);
		if (QLayout* childLayout = item->layout())
			clearLayout(childLayout, deleteWidgets);
		delete item;
	}
}
