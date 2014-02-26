#include "import.h"
#include "ui_import.h"

Import::Import(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Import)
{
	ui->setupUi(this);
}

Import::~Import()
{
	delete ui;
}
