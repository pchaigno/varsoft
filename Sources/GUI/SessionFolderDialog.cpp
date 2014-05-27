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
#include "SessionFolderDialog.h"

SessionFolderDialog::SessionFolderDialog(QWidget *parent): QDialog(parent), ui(new Ui::SessionFolderDialog) {
	ui->setupUi(this);
	this->setting.setValue("path", "C:/");
}

SessionFolderDialog::~SessionFolderDialog() {
	delete ui;
}

void SessionFolderDialog::on_okButton_clicked() {
	if(ui->filePath->text() == "") {
		QMessageBox::warning(0, "Warning", "You must select a folder.");
		return;
	}

	SessionSaver::setSessionFolder(QDir(ui->filePath->text()));
	this->close();
}

void SessionFolderDialog::on_cancelButton_clicked() {
	this->close();
	qApp->exit();
}

void SessionFolderDialog::on_selectButton_clicked() {
	QString path = this->setting.value("path").toString();
	QFileInfo sessionFolder = QFileDialog::getExistingDirectory(this, ("Save in"), path, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if(sessionFolder.isDir()) {
		this->setting.setValue("path", sessionFolder.absolutePath());
		ui->filePath->setText(sessionFolder.filePath());
	}
}
