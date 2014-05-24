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

#include "CorrelationDialog.h"

/**
* @brief Correlation Constructor
* Range of date is limited by the file's range dates
* @param portfolio The Portfolio
* @param startDate The oldest date in the file
* @param endDate The latest date in the file
* @param parent QDialog Widget to use
*/
Correlation::Correlation(const Portfolio &portfolio, QWidget *parent): QDialog(parent), ui(new Ui::Correlation) {
	ui->setupUi(this);
	this->portfolio = porfolio;
	QDate date = portfolio.retrieveEndDate();
	ui->date->setMinimumDate(date);
	ui->date->setMaximumDate(portfolio.retrieveStartDate());
	ui->date->setDate(date);
	ui->date->setCalendarPopup(true);

	//delete automatically the QDialog
	this->setAttribute(Qt::WA_DeleteOnClose);
}

Correlation::~Correlation() {
	delete ui;
}

/**
* @brief Called when Correlation file window's "Generate" button is pushed
* Emit a signal with all data set in the window
*/
void Correlation::on_pushButton_clicked() {

	RInterface ri = new RInterface();
	if(ui->comboBox->currentText() == "Correlation")
		ri.checkCorrelation(this->portfolio,ui->timelag->value(),ui->date->)
	/*
	ImportNewData algo = ImportNewData();
	if(ui->startDate->dateTime() >= ui->endDate->dateTime()) {
		QMessageBox::warning(0, "Warning", "Dates are not valid");
		return;
	}
	if(ui->textEdit->text().trimmed().isEmpty()) {
		QMessageBox::warning(0, "Warning", "Please provide a name");
		return;
	}
	if(AssetsFactory::getInstance()->retrieveAsset(ui->textEdit->text()) != NULL) {
		QMessageBox::warning(0, "Error", "This name is already used");
		return;
	} else {
		try {
			QString namealea = ui->textEdit->text()+"_"+QString::number(QDateTime::currentMSecsSinceEpoch())+".csv";
			Asset a = Asset(ui->textEdit->text(), namealea, ui->comboBox->currentText(), ui->startDate->date(), ui->endDate->date());
			algo.import(a, fileName);
			SessionSaver::getInstance()->saveAsset(a);
		} catch(ImportException &e) {
			const QString& mes = QString(e.what());
			QMessageBox::warning(0, "Error", mes);
			return;
		}
		this->close();
	}
	*/
}

/**
* @brief Called when Importing file window's "Cancel" button is pushed
* Cancel csv's import
*/
void Correlation::on_pushButton_2_clicked() {
	this->close();
}

