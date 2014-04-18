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
#include "import.h"

/**
* @brief Import Constructor
* @param parent QDialog Widget to use
*/
Import::Import(QWidget *parent): QDialog(parent), ui(new Ui::Import) {
	ui->setupUi(this);
	//Date of the day
	ui->dateEdit->setDate(QDate::currentDate());
	ui->dateEdit->setCalendarPopup(true);
	ui->dateEdit_2->setCalendarPopup(true);
	connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
}

Import::~Import() {
	delete ui;
}

/**
* @brief Called when Importing file window's "OK" button is pushed
* Emit a signal with all data set in the window
*/
void Import::on_pushButton_clicked() {
	// TODO : check the field is not empty and print a message to force the user to give a name
	emit this->dataEntered(ui->textEdit->toPlainText(), ui->dateEdit->dateTime(),
							ui->dateEdit_2->dateTime(), ui->comboBox->currentText());
	this->close();
}

/**
* @brief Called when Importing file window's "Cancel" button is pushed
* Blank all fields
*/
void Import::on_pushButton_2_clicked() {
	//TODO: cancel import
}
