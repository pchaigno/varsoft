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
* @param parent QDialog Widget to use
*/
Import::Import(QWidget *parent): QDialog(parent), ui(new Ui::Import) {
	ui->setupUi(this);

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
	CreateAsset algo = CreateAsset();
	if(ui->startDate->dateTime() >= ui->endDate->dateTime()) {
		QMessageBox::warning(0, "Warning", "Dates are not valid.");
		return;
	}
	if(ui->textEdit->text().trimmed().isEmpty()) {
		QMessageBox::warning(0, "Warning", "Please provide a name.");
		return;
	}

	if(AssetsFactory::getInstance()->retrieveAsset(ui->textEdit->text()) != NULL) {
		QMessageBox::warning(0, "Error", "This name is already used");
		return;
	} else {
		try {
			QDir resourcesFolder(SessionSaver::getSessionFolder() + QDir::separator() + "Resources");
			if (!resourcesFolder.exists("Assets")) {
				resourcesFolder.mkpath("Assets");
			}
			QString namealea = ui->textEdit->text() + "_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".csv";
			QString assetPath = QString("Resources/Assets") + QDir::separator() + namealea;
			Asset a = Asset(ui->textEdit->text(), assetPath, ui->comboBox->currentText(), ui->startDate->date(), ui->endDate->date());
			algo.import(a, fileName);
			SessionSaver::getInstance()->saveAsset(a);
		} catch(CreateAssetException &e) {
			const QString& mes = QString(e.what());
			QMessageBox::warning(0, "Error", mes);
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

void Import::on_importButton_clicked(){
	QString path = this->setting.value("createAssetFolder", "C:/").toString();
	QFileInfo fileName = QFileDialog::getOpenFileName(this, ("Open file"), path, ("CSV Text (*.csv *.txt);;All files (*.*)") );
	if(fileName.isFile()){
		this->setting.setValue("createAssetFolder", fileName.absolutePath());
		//get startDate and endDate before calling the import function
		GetStartEndDates* gsed = new GetStartEndDates();
		gsed->retreiveDates(fileName.filePath());
		QDate endDate = gsed->getEndDate();
		QDate startDate = gsed->getStartDate();
		ui->filePath->setText(fileName.filePath());
		ui->endDate->setDate(endDate);
		ui->endDate->setMaximumDate(endDate);
		ui->endDate->setMinimumDate(startDate);
		ui->endDate->setCalendarPopup(true);
		ui->startDate->setMinimumDate(startDate);
		ui->startDate->setMaximumDate(endDate);
		ui->startDate->setDate(startDate);
		ui->startDate->setCalendarPopup(true);
		this->fileName = fileName.filePath();
	}
}
