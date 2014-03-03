#pragma once

#include <QMainWindow>
#include <QDateTime>
#include <QDialog>
#include <QComboBox>
#include "import.h"
#include <string>

namespace Ui{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void importCSV();
	void setImportCSV();
public slots:
	void onDataEntered(const QString &text, const QDateTime &fDate ,const QDateTime &lDate, const QString &source);
	//void onFirstDateEntered(const QDateTime &date);
	//void onLastDateEntered(const QDateTime &date);
private:
	Ui::MainWindow *ui;
	Import import_win;
	QString stockName;
	QDateTime firstDate;
	QDateTime lastDate;
	QString fileName;
	QString source;
};

