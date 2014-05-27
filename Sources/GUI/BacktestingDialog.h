#pragma once

#include <QDialog>
#include <QMessageBox>
#include "VaRHistorical.h"
#include "VaRRiskmetrics.h"
#include "Backtesting.h"

namespace Ui {
	class BacktestingDialog;
}

class BacktestingDialog : public QDialog
{
	Q_OBJECT

public:
	explicit BacktestingDialog(QWidget *parent = 0, Portfolio * portfolio = 0);
	~BacktestingDialog();

private:
	Ui::BacktestingDialog *ui;
	Portfolio * portfolio;

private slots:
	void on_pushButton_run_backtesting_historical_clicked();
	void on_pushButton_run_backtesting_riskmetrics_clicked();
	void on_pushButton_cancel_1_clicked();
	void on_pushButton_cancel_2_clicked();
};
