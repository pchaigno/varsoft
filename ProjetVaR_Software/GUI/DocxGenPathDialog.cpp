#include "DocxGenPathDialog.h"
#include "ui_DocxGenPathDialog.h"

DocxGenPathDialog::DocxGenPathDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DocxGenPathDialog)
{
	ui->setupUi(this);
	QSettings settings;
	settings.setValue("DocXGenPath",ui->pathEdit->text());
	connect(ui->browseButton,SIGNAL(clicked()),this,SLOT(browse()));
	ui->pathEdit->setText(settings.value("DocXGenPath","../Resources/DocxGenerator/DocXGenerator.jar").toString());
}

DocxGenPathDialog::~DocxGenPathDialog()
{
	delete ui;
}

void DocxGenPathDialog::browse()
{
	ui->pathEdit->setText(QFileDialog::getOpenFileName(this, tr("DocxGenerator Jar"),"",tr("Jar (*.jar)")));
}

void DocxGenPathDialog::accept()
{
	QSettings settings;
	settings.setValue("DocXGenPath",ui->pathEdit->text());
	this->QDialog::accept();
}
