#include "BacktestingDialog.h"
#include "ui_BacktestingDialog.h"

BacktestingDialog::BacktestingDialog(QWidget *parent, Portfolio *portfolio) : QDialog(parent), ui(new Ui::BacktestingDialog)
{
	ui->setupUi(this);
	this->portfolio = portfolio;
}

BacktestingDialog::~BacktestingDialog()
{
	delete ui;
}

void BacktestingDialog::on_pushButton_run_backtesting_historical_clicked() {
	int nbDaysLossGreaterThanVaR = 0;

	try {
		VaRHistorical varAlgo(*portfolio, ui->riskBacktestingHistorical->value(), ui->timeHorizonBacktestingHistorical->value(), ui->numberOfPeriodsBacktestingHistorical->value());

		QPair<QDate, QDate> period;
		QDate startDate = ui->startDatePeriodBacktestingHistorical->date();
		QDate endDate = ui->endDatePeriodBacktestingHistorical->date();
		period.first = startDate;
		period.second = endDate;

		Backtesting backtesting(*portfolio, varAlgo, period);
		nbDaysLossGreaterThanVaR = backtesting.compute();
	} catch(std::invalid_argument& ia) {
		QMessageBox::warning(0, "Warning", QString(ia.what()));
		return;
	}

	QMessageBox msgBox;
	msgBox.setWindowTitle("Backtesting result");
	msgBox.setText("Number of day(s) on which the loss was greater than the Value-at-Risk: "+QString::number(nbDaysLossGreaterThanVaR));
	msgBox.exec();

}

void BacktestingDialog::on_pushButton_run_backtesting_riskmetrics_clicked() {
	int nbDaysLossGreaterThanVaR = 0;

	try {
		VaRRiskmetrics varAlgo(*portfolio, ui->riskBacktestingRiskmetrics->value(), ui->timeHorizonBacktestingRiskmetrics->value(), ui->nbIterationsBacktestingRiskmetrics->value());

		QPair<QDate, QDate> period;
		QDate startDate = ui->startDatePeriodBacktestingRiskMetrics->date();
		QDate endDate = ui->endDatePeriodBacktestingRiskMetrics->date();
		period.first = startDate;
		period.second = endDate;

		Backtesting backtesting(*portfolio, varAlgo, period);
		nbDaysLossGreaterThanVaR = backtesting.compute();
	} catch(std::invalid_argument& ia) {
		QMessageBox::warning(0, "Warning", QString(ia.what()));
		return;
	}

	QMessageBox msgBox;
	msgBox.setWindowTitle("Backtesting result");
	msgBox.setText("Number of day(s) on which the loss was greater than the Value-at-Risk: "+QString::number(nbDaysLossGreaterThanVaR));
	msgBox.exec();
}

void BacktestingDialog::on_pushButton_cancel_1_clicked() {
	this->close();
}

void BacktestingDialog::on_pushButton_cancel_2_clicked() {
	this->close();
}
