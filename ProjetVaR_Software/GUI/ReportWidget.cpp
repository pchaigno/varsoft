#include "ReportWidget.h"
#include "ui_ReportWidget.h"

ReportWidget::ReportWidget(Report *report, QWidget *parent) :
	QWidget(parent), ui(new Ui::ReportWidget), report(report)
{
	ui->setupUi(this);
}

ReportWidget::~ReportWidget()
{
	delete ui;
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

void ReportWidget::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
