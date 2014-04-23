#include "DocxGenPathDialog.h"
#include "ui_DocxGenPathDialog.h"

DocxGenPathDialog::DocxGenPathDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DocxGenPathDialog)
{
	ui->setupUi(this);
	QSettings settings;
	connect(ui->browseButton,SIGNAL(clicked()),this,SLOT(browse()));
	ui->pathEdit->setText(settings.value(DOCXSETTINGS,RES_FOLDER+"/DocxGenerator/DocXGenerator.jar").toString());
}

DocxGenPathDialog::~DocxGenPathDialog()
{
	delete ui;
}
/**
 * @brief Open a FileDialog and put the path to the input field
 */
void DocxGenPathDialog::browse()
{
	ui->pathEdit->setText(QFileDialog::getOpenFileName(this, tr("DocxGenerator Jar"),"",tr("Jar (*.jar)")));
}
/**
 * @brief write the settings with the new path
 */
void DocxGenPathDialog::accept()
{
	QSettings settings;
	settings.setValue(DOCXSETTINGS,ui->pathEdit->text());
	this->QDialog::accept();
}
