#pragma once

#include <QMainWindow>
#include "NewPortfolioWizard.h"
#include "PortfolioItemModel.h"

namespace Ui {
	class MainWindow;
}

class MainWindow: public QMainWindow {
	Q_OBJECT
    
public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

private slots:
    void newPortfolio();
    void showPortfolio();
    //void showPortfolio(Portfolio* portfolio);
    void importCSV();
private:
	Ui::MainWindow *ui;
    PortfolioItemModel * portfolioModel;
};
