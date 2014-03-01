#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "import.h"

namespace Ui {
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
	void import();
public slots:
	void onTextEntered(const QString &text);
private:
	Ui::MainWindow *ui;
	Import import_win;
};

#endif // MAINWINDOW_H
