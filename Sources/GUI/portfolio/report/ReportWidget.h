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
#pragma once

#include <QWidget>
#include <QPainter>
#include <QDesktopServices>
#include "Report.h"
#include <QMessageBox>
#include <QFileInfo>

namespace Ui {
	class ReportWidget;
}

class ReportWidget : public QWidget {
	Q_OBJECT
signals:
	void deleteRequest();

public:
	explicit ReportWidget(Report * report=NULL, QWidget *parent = 0);
	~ReportWidget();

	void setTitle(QString title);
	QString getTile() const;

	void setIcon(QString path);
	void setIcon(QPixmap & img);

	ReportType getTypeReport() const;
	Report *getReport() const;

public slots:
	void openPDF();
	void openDocx();
	void deleteReport();
	void generationFinish();

private:
	void paintEvent(QPaintEvent *pe);

	Ui::ReportWidget *ui;
	Report * report;
};
