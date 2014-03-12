#pragma once

#include <QDialog>

namespace Ui {
class Import;
}
/**
* @brief Useful for the import window links with the mainwindow
*/
class Import : public QDialog
{
	Q_OBJECT

public:
	explicit Import(QWidget *parent = 0);
	~Import();

private:
	Ui::Import *ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();

signals:
		void dataEntered(const QString &name, const QDateTime &fDate,const QDateTime &lDate, const QString &source);
};

