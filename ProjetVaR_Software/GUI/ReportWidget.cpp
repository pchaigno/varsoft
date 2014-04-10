#include "ReportWidget.h"
#include "ui_ReportWidget.h"


ReportWidget::ReportWidget(Report *report, QWidget *parent) :
	QWidget(parent), ui(new Ui::ReportWidget), report(report)
{
	ui->setupUi(this);
	connect(ui->docxButton,SIGNAL(clicked()),this,SLOT(openDocx()));
	connect(ui->pdfButton,SIGNAL(clicked()),this,SLOT(openPDF()));
	connect(ui->supprButton,SIGNAL(clicked()),this,SLOT(deleteReport()));
}

ReportWidget::~ReportWidget()
{
	delete ui;
}

void ReportWidget::openPDF()
{
	QDesktopServices::openUrl(QUrl(report->getFile()+".pdf"));
}

void ReportWidget::openDocx()
{
	QDesktopServices::openUrl(QUrl(report->getFile()+".docx"));
}

void ReportWidget::deleteReport()
{
	QMessageBox::StandardButton rep = QMessageBox::question(this,"Are you sure ?", "Are you sure to delete this report ?");
	if (rep==QMessageBox::Yes)
	{
		emit deleteRequest();
	}
}


void ReportWidget::setTitle(QString title)
{
	ui->titleLabel->setText(title);
}

QString ReportWidget::getTile() const
{
	return ui->titleLabel->text();
}

void ReportWidget::setIcon(QString path)
{
	QPixmap img(path);
	ui->imgLabel->setPixmap(img);
}

void ReportWidget::setIcon(QPixmap &img)
{
	ui->imgLabel->setPixmap(img);
}

ReportType ReportWidget::getTypeReport() const
{
	return report->getType();
}

Report *ReportWidget::getReport() const
{
	return report;
}

void ReportWidget::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
