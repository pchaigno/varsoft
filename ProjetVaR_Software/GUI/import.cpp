#include "import.h"
#include "ui_import.h"

Import::Import(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Import)
{
	ui->setupUi(this);
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
	// Emitting a signal with the new text
	emit this->textEntered(ui->textEdit->toPlainText());
}

// Cancel button clicked
void Import::on_pushButton_2_clicked()
{

}
