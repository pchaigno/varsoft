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

#ifndef REPORTLISTSCROLLAREA_H
#define REPORTLISTSCROLLAREA_H

#include <QScrollArea>
#include "FlowLayout.h"
#include <QHash>
#include <QList>
#include "Portfolio.h"
#include "ReportWidget.h"
#include "ReportWidgetFactory.h"
#include "ui_ReportListScrollArea.h"

namespace Ui {
class ReportListScrollArea;
}

class ReportView : public QScrollArea
{
	Q_OBJECT
	
public:
	explicit ReportView(QWidget *parent = 0);
	~ReportView();

	void removeReport(Report * report);


public slots:
	void setCurrent(Portfolio * portfolio);

private slots:
	void addReport(Report * report);
	void removeReportWidget();
	void removeReportWidget(ReportWidget * reportWidget);
	void updateReportWidgetList();

private:
	void addToLayout(ReportWidget * reportWidget);
	void clearLayout(bool deleteWidgets=false);
	void clearLayout(QLayout* layout,bool deleteWidgets=false);
	
private:
	Ui::ReportListScrollArea *ui;
	FlowLayout * layout;
	Portfolio * current;
	//QHash<Portfolio*, QList<ReportWidget*> > portfolioReportWidgets;
};

#endif // REPORTLISTSCROLLAREA_H
