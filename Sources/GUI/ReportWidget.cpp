#include "ReportWidget.h"
#include "ui_ReportWidget.h"


ReportWidget::ReportWidget(Report *report, QWidget *parent) :
	QWidget(parent), ui(new Ui::ReportWidget), report(report)
{
	ui->setupUi(this);
	connect(ui->docxButton,SIGNAL(clicked()),this,SLOT(openDocx()));
	connect(ui->pdfButton,SIGNAL(clicked()),this,SLOT(openPDF()));
	connect(ui->supprButton,SIGNAL(clicked()),this,SLOT(deleteReport()));

	connect(report,SIGNAL(filesOk()),this,SLOT(generationFinish()));
	connect(report,SIGNAL(filesNotOk()),this,SIGNAL(deleteRequest()));
}

ReportWidget::~ReportWidget()
{
	delete ui;
}
/**
 * @brief Open the report in the PDF format with the usual software for reading PDF of the user.
 */
void ReportWidget::openPDF()
{
	QFileInfo file(report->getFile()+".pdf");
	QUrl url(file.absoluteFilePath());
	url.setScheme("file");
	QDesktopServices::openUrl(url);
}
/**
 * @brief Open the report in the Docx format with the usual software for reading Docx of the user.
 */
void ReportWidget::openDocx()
{
	QFileInfo file(report->getFile()+".docx");
	QUrl url(file.absoluteFilePath());
	url.setScheme("file");
	QDesktopServices::openUrl(url);
}
/**
 * @brief Slot called when the user click on the delete button of the ReportWidget.
 * Ask the user if he is sure to delete the report, and send the signal to delete it
 */
void ReportWidget::deleteReport()
{
	QMessageBox::StandardButton rep = QMessageBox::question(this,"Are you sure ?", "Are you sure to delete this report ?");
	if (rep==QMessageBox::Yes)
	{
		emit deleteRequest();
	}
}
/**
 * @brief Slot called when the generation has finished. It enables all the buttons
 */
void ReportWidget::generationFinish()
{
	ui->docxButton->setEnabled(true);
	ui->pdfButton->setEnabled(true);
	ui->supprButton->setEnabled(true);
}

/**
 * @brief Setter of the title
 * @param title
 */
void ReportWidget::setTitle(QString title)
{
	ui->titleLabel->setText(title);
}
/**
 * @brief Getter of the title
 * @return
 */
QString ReportWidget::getTile() const
{
	return ui->titleLabel->text();
}
/**
 * @brief Setter of the icon
 * @param path
 */
void ReportWidget::setIcon(QString path)
{
	QPixmap img(path);
	ui->imgLabel->setPixmap(img);
}

void ReportWidget::setIcon(QPixmap &img)
{
	ui->imgLabel->setPixmap(img);
}
/**
 * @brief Return the enum type of the report
 * @return
 */
ReportType ReportWidget::getTypeReport() const
{
	return report->getType();
}
/**
 * @brief Getter of the report
 * @return
 */
Report *ReportWidget::getReport() const
{
	return report;
}
/**
 * @brief To make work the css
 * @param pe
 */
void ReportWidget::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
