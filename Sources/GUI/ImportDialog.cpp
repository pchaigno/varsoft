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
#include "ImportDialog.h"

/**
* @brief Import Constructor
* Ranges of dates or limited by the range file
* @param the name of the asset file
* @param parent QDialog Widget to use
*/
Import::Import(QString fileName, QDate startDate, QDate endDate, QWidget *parent): QDialog(parent), ui(new Ui::Import) {
	ui->setupUi(this);
    ui->endDate->setDate(endDate);
	ui->endDate->setMaximumDate(endDate);
	ui->endDate->setMinimumDate(startDate);
	ui->endDate->setCalendarPopup(true);
	ui->startDate->setMinimumDate(startDate);
	ui->startDate->setMaximumDate(endDate);
	ui->startDate->setDate(startDate);
    ui->startDate->setCalendarPopup(true);
    this->fileName=fileName;

    //delete automatically the QDialog
    this->setAttribute(Qt::WA_DeleteOnClose);
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
    ImportNewData algo = ImportNewData();
	if(ui->startDate->dateTime() >= ui->endDate->dateTime()){
		QMessageBox::warning(0, "Attention","Les dates ne sont pas valides");
        return;
	}
	else{
        try{
            QString namealea = ui->textEdit->toPlainText()+"_"+QString::number(QDateTime::currentMSecsSinceEpoch())+".csv";
            Asset a = Asset(ui->textEdit->toPlainText(),namealea,ui->comboBox->currentText(),ui->startDate->dateTime(),ui->endDate->dateTime());
            algo.import(a, fileName);
            SessionSaver::getInstance()->saveAsset(a);
        }
        catch(ImportException &e){
            const QString& mes = QString(e.what());
            QMessageBox::warning(0,"Attention",mes);
            return;
        }
        this->close();
	}
}

/**
* @brief Called when Importing file window's "Cancel" button is pushed
* Cancel csv's import
*/
void Import::on_pushButton_2_clicked() {
    this->close();
}
