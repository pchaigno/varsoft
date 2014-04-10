#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDesktopServices>
#include "Report.h"
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class ReportWidget;
}

class ReportWidget : public QWidget
{
	Q_OBJECT

signals:
	void deleteRequest();

public:
	explicit ReportWidget(Report * report=NULL, QWidget *parent = 0);
	~ReportWidget();

	void setTitle(QString title);
	QString getTile() const;

	void setIcon(QString path);
	void setIcon(QPixmap & img);

	ReportType getTypeReport() const;

	Report *getReport() const;

public slots:
	void openPDF();
	void openDocx();
	void deleteReport();

private:
	void paintEvent(QPaintEvent *pe);


	Ui::ReportWidget *ui;
	Report * report;
};

#endif // REPORTWIDGET_H
