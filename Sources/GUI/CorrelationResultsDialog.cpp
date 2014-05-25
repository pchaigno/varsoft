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
#include "CorrelationResultsDialog.h"

/**
* @brief CorrelationRes Constructor
* Range of date is limited by the file's range dates
* @param portfolio The Portfolio
* @param startDate The oldest date in the file
* @param endDate The latest date in the file
* @param parent QDialog Widget to use
*/
CorrelationResultsDialog::CorrelationResultsDialog(QList<CorrelationResults> *results, QString testType, QPair<double,double> res, QWidget *parent): QDialog(parent), ui(new Ui::CorrelationResultsDialog) {
	ui->setupUi(this);
	ui->testType->setText("Test's type: "+ testType);
	ui->pValue->setText("p-value: "+QString::number(res.second));
	ui->statValue->setText("Statistical value: "+QString::number(res.first));
	this->results = results;
	this->pair = res;
	this->type = testType;
	//delete automatically the QDialog
	this->setAttribute(Qt::WA_DeleteOnClose);
}

CorrelationResultsDialog::~CorrelationResultsDialog() {
	delete ui;
	//delete pair;
	//delete type;
	//delete results;
}

/**
* @brief Save a test
*/
void CorrelationResultsDialog::on_save_clicked() {
	results->append(CorrelationResults(type,pair.first,pair.second));
	ui->save->setEnabled(false);
}

/**
* @brief Close the window and delete previous results
*/
void CorrelationResultsDialog::on_quit_clicked() {
	this->close();
	qobject_cast<Correlation*>(this->parentWidget())->quit();
	//delete results;
}

/**
* @brief Close the window and show the correlation set up's window
*/
void CorrelationResultsDialog::on_testAgain_clicked() {
	this->close();
}

/**
* @brief Generate the report with the previous tests
*/
void CorrelationResultsDialog::on_generate_clicked() {
	//generer le rapport
}


