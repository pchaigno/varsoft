#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>
#include <QPainter>
#include "Report.h"

namespace Ui {
class ReportWidget;
}

class ReportWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ReportWidget(Report * report=NULL, QWidget *parent = 0);
	~ReportWidget();

	void setTitle(QString title);
	QString getTile() const;

	void setIcon(QString path);
	void setIcon(QPixmap & img);


	ReportType getTypeReport() const;

private:
	void paintEvent(QPaintEvent *pe);


	Ui::ReportWidget *ui;
	Report * report;
};

#endif // REPORTWIDGET_H
