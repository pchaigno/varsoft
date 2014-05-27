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
#include "ReportView.h"

ReportView::ReportView(QWidget *parent) :
	QScrollArea(parent),
	ui(new Ui::ReportListScrollArea)
{
	ui->setupUi(this);
	layout = new FlowLayout();
	this->setLayout(layout);
	current=NULL;
}

ReportView::~ReportView()
{
	delete ui;
}

void ReportView::removeReport(Report *report)
{
	current->removeReport(*report);
}


/**
 * @brief Initialize the layout with the report of the portfolio given.
 * @param Portfolio which you want to display reports.
 */
void ReportView::setCurrent(Portfolio *portfolio)
{
	if (current!=NULL)
	{
		disconnect(current,SIGNAL(reportAdded(Report*)),this,SLOT(addReport(Report*)));
		disconnect(current,SIGNAL(reportRemoved()),this,SLOT(updateReportWidgetList()));
	}
	clearLayout();
	current=portfolio;
	updateReportWidgetList();
	connect(portfolio,SIGNAL(reportAdded(Report*)),this,SLOT(addReport(Report*)));
	connect(portfolio,SIGNAL(reportRemoved()),this,SLOT(updateReportWidgetList()));
}

/**
 * @brief Construct the ReportWidget of the report param and display for the current portfolio
 * @param report
 */
void ReportView::addReport(Report *report)
{
	ReportWidget * reportWidget = ReportWidgetFactory::buildReportWidget(report);
	connect(reportWidget,SIGNAL(deleteRequest()),this,SLOT(removeReportWidget()));
	addToLayout(reportWidget);
}

void ReportView::removeReportWidget()
{
	ReportWidget *reportWidget = qobject_cast<ReportWidget *>(sender());
	if (reportWidget)
		removeReportWidget(reportWidget);
}
/**
 * @brief Remove the ReportWidget and its reports from the layout and the portfolio
 * @param reportWidget
 */
void ReportView::removeReportWidget(ReportWidget *reportWidget)
{
	Report * report = reportWidget->getReport();
	current->removeReport(*report);
	updateReportWidgetList();
}

/**
 * @brief Add the reportWidget to the layout
 * @param reportWidget
 */
void ReportView::addToLayout(ReportWidget *reportWidget)
{
	layout->addWidget(reportWidget);
}


void ReportView::updateReportWidgetList()
{
	clearLayout(true);
	foreach(Report * report, current->getReports())
	{
		addReport(report);
	}
}

/**
 * @brief Clear the main layout
 */
void ReportView::clearLayout(bool deleteWidgets)
{
	clearLayout(layout,deleteWidgets);
}

void ReportView::clearLayout(QLayout *layout, bool deleteWidgets)
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
