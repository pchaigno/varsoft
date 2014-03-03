#include "import.h"
#include "ui_import.h"

Import::Import(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Import)
{
	ui->setupUi(this);
	//Date of the day
	ui->dateEdit->setDate(QDate::currentDate());
	ui->dateEdit->setCalendarPopup(true);
	ui->dateEdit_2->setCalendarPopup(true);
	connect(ui->pushButton, SIGNAL(clicked()),
			   this, SIGNAL(on_pushButton_clicked));
}

Import::~Import()
{
	delete ui;
}

// Validate button clicked
void Import::on_pushButton_clicked()
{
	// TODO : vérifier que le texte n'est pas vide
	//if(ui->textEdit->toPlainText() != "")
		emit this->dataEntered(ui->textEdit->toPlainText(), ui->dateEdit->dateTime(),
							   ui->dateEdit_2->dateTime(), ui->comboBox->currentText());
	//else
		// afficher quelque chose pour obliger à renseigner un nom
	//emit this->firstDateEntered(ui->dateEdit->dateTime());
	//emit this->lastDateEntered(ui->dateEdit_2->dateTime());
	this->close();
}

// Cancel button clicked
void Import::on_pushButton_2_clicked()
{
	//annuler totalement l'importation????
	//reseter les champs???
	//this->textEntered(ui->textEdit->toPlainText(""));
}
