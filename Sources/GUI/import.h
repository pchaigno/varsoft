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

#include "ui_import.h"
#include "ImportNewData.h"
#include <QDateTime>
#include <QDialog>

namespace Ui {
	class Import;
}
/**
* @brief Useful for the import window links with the mainwindow
*/
class Import : public QDialog {
	Q_OBJECT

public:
    explicit Import(QString fileName, QDate startDate, QDate endDate, QWidget *parent = 0);
	~Import();

private:
	Ui::Import *ui;
    QString fileName;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();

signals:
};
