#include "BacktestingDialog.h"
#include "ui_BacktestingDialog.h"

BacktestingDialog::BacktestingDialog(QWidget *parent, Portfolio *portfolio) : QDialog(parent), ui(new Ui::BacktestingDialog)
{
	ui->setupUi(this);
	this->portfolio = portfolio;
	initDates();
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

void BacktestingDialog::on_pushButton_run_backtesting_garch_clicked() {
	int nbDaysLossGreaterThanVaR = 0;

	try {
		QPair<QDate, QDate> modelPeriod;
		QDate modelStartDate = ui->startDatePeriodBacktestingGarchModel->date();
		QDate modelEndDate = ui->endDatePeriodBacktestingGarchModel->date();
		modelPeriod.first = modelStartDate;
		modelPeriod.second = modelEndDate;

		QPair<QDate, QDate> backtestPeriod;
		QDate backtestStartDate = ui->startDatePeriodBacktestingGarch->date();
		QDate backtestEndDate = ui->endDatePeriodBacktestingGarch->date();
		backtestPeriod.first = backtestStartDate;
		backtestPeriod.second = backtestEndDate;

		GarchModel model = RInterface::computeGarchModel(*portfolio, modelPeriod);

		VaRGarch algo(*portfolio, ui->riskBacktestingGarch->value(), ui->timeHorizonBacktestingGarch->value(), model, ui->bootstrapIterationsBacktestingGarch->value(), ui->initIterationsBacktestingGarch->value());
		Backtesting backtesting(*portfolio, algo,backtestPeriod);
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

void BacktestingDialog::on_pushButton_cancel_3_clicked() {
	this->close();
}

void BacktestingDialog::initDates() {
	QDate startDate = portfolio->retrieveStartDate();
	ui->startDatePeriodBacktestingGarch->setDate(startDate);
	ui->startDatePeriodBacktestingGarchModel->setDate(startDate);
	ui->startDatePeriodBacktestingHistorical->setDate(startDate);
	ui->startDatePeriodBacktestingRiskMetrics->setDate(startDate);

	QDate endDate = portfolio->retrieveEndDate();
	ui->endDatePeriodBacktestingGarch->setDate(endDate);
	ui->endDatePeriodBacktestingGarchModel->setDate(endDate);
	ui->endDatePeriodBacktestingHistorical->setDate(endDate);
	ui->endDatePeriodBacktestingRiskMetrics->setDate(endDate);
}
