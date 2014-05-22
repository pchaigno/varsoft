/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "RInterface.h"

/**
 * @brief Call the R script performing the correlation test.
 * @param portfolio The portfolio on which the correlation test is performed
 * @param timeLag Time lag of the statistical test
 * @param date The date from which the historical returns will be taken
 * @param period The number of returns
 * @return The statistical value and p-value couple
 */
QPair<double, double> RInterface::checkCorrelation(const Portfolio& portfolio, int timeLag, QDate& date, int period) {
	// Check the period parameter
	if(timeLag > period - 2) {
		throw std::invalid_argument("The timeLag parameter cannot be greater than period minus two");
	}

	return executeCorrelationScript(portfolio, timeLag, date, period, "../../R_scripts/correlation-niveau.r");
}

/**
 * @brief Call the R script performing the square correlation test.
 * @param portfolio The portfolio on which the correlation test is performed
 * @param timeLag Time lag of the statistical test
 * @param date The date from which the historical returns will be taken
 * @param period The number of returns
 * @return The statistical value and p-value couple
 */
QPair<double, double> RInterface::checkSquareCorrelation(const Portfolio& portfolio, int timeLag, QDate& date, int period) {
	// Check the period parameter
	if(timeLag > period - 1) {
		throw std::invalid_argument("The timeLag parameter cannot be greater than period minus one");
	}

	return executeCorrelationScript(portfolio, timeLag, date, period, "../../R_scripts/correlation-carre.r");
}

/**
 * @brief RInterface::executeCorrelationScript Generic call to the R script passed as rScriptFilePath parameter
 * @param portfolio The portfolio on which the correlation test is performed
 * @param timeLag Time lag of the statistical test
 * @param date The date from which the historical returns will be taken
 * @param period The number of returns
 * @param rScriptFilePath R script file
 * @return The statistical value and p-value couple
 */
QPair<double, double> RInterface::executeCorrelationScript(const Portfolio& portfolio, int timeLag, QDate& date, int period, QString rScriptFilePath) {
	// Check that parameters are correct
	if(timeLag <= 0) {
		throw std::invalid_argument("The timeLag parameter must be strictly positive");
	}
	if(period <= 0 ) {
		throw std::invalid_argument("The period parameter must be strictly positive");
	}

	// The only command line argument passed to Rscript is
	// the R script file
	QStringList arguments;
	arguments << rScriptFilePath;

	// Makes the string sent to the Rscript standard input
	// Made of two lines, one paramater a line
	// timeLag on the first, the returns on the second, separated by space characters
	QString parameters = QString::number(timeLag) + "\n";
	QVector<double> returns = portfolio.retrieveReturns(date, period);
	for(QVector<double>::const_iterator it=returns.begin(); it!=returns.end(); ++it) {
		parameters += QString::number(*it) + " ";
	}

	QProcess process;
	process.start("Rscript", arguments);
	process.waitForStarted();
	// Writes to R standard input the previously created string
	process.write(parameters.toStdString().c_str());
	process.closeWriteChannel();
	process.waitForFinished();

	// Reads R output
	QByteArray rawOutput = process.readAllStandardOutput();

	// Convert it to QString
	QString output = QString::fromUtf8(rawOutput);

	// Splits the output by newline
	// Removes empty lines as well
	QStringList lines = output.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

	// Gets only the values (removes matrix indices)
	QRegExp rx("\\s+");
	double ststdport = lines.value(1).split(rx).value(1).toDouble();
	double pvportcarre = lines.value(3).split(rx).value(1).toDouble();

	QPair<double, double> result;
	result.first = ststdport;
	result.second = pvportcarre;

	return result;
}


/**
 * @brief Call the R script to compute the GARCH model of a portfolio.
 * @param portfolio The portfolio.
 * @param period Pair of QDate in chronological order defining the interval on which
 * to perform the Garch model computation
 * @return The Garch model.
 */
GarchModel RInterface::computeGarchModel(const Portfolio& portfolio, const QPair<QDate, QDate> &period) {

	// The only command line argument passed to Rscript is
	// the R script file
	QStringList arguments;
	QString rScriptFilePath = "../../R_scripts/garch.r";
	arguments << rScriptFilePath;

	// Makes the string that will be sent to the Rscript standard input
	// Made of a single line containing the log-returns separated by space characters
	QVector<double> logReturns = portfolio.retrieveLogReturns(period.first, period.second);
	if(logReturns.size() <= 2) {
		throw std::invalid_argument("The period argument must be larger than specified to perform garch model computation");
	}
	QString parameters;
	for(QVector<double>::const_iterator it=logReturns.begin(); it!=logReturns.end(); ++it) {
		parameters += QString::number(*it) + " ";
	}

	// Launch Rscript
	QProcess process;
	process.start("Rscript", arguments);
	// Writes to Rscript standard input the previously created string
	process.write(parameters.toStdString().c_str());
	process.closeWriteChannel();
	process.waitForFinished();

	// Reads R output
	QByteArray rawOutput = process.readAllStandardOutput();

	// Convert it to QString
	QString output = QString::fromUtf8(rawOutput);

	// Splits the output by newline
	// Removes empty lines as well
	QStringList lines = output.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

	// Retrieves the coefficient from the right line
	QStringList coefficients = lines.value(1).split(QRegExp("\\s"), QString::SkipEmptyParts);

	// Gets the coefficient values
	double omega = coefficients.value(0).toDouble();
	double alpha = coefficients.value(1).toDouble();
	double beta = coefficients.value(2).toDouble();

	// Retrieves the residuals (eta) from Rscript output
	QVector<double> residuals;
	QStringList residualsList;
	int line;
	bool residual = true;
	for(line=3; residual; line++) {
		residualsList = lines.value(line).split(QRegExp("\\s"), QString::SkipEmptyParts);
		if(residualsList.value(1) == "\"stddev\"") {
			residual = false;
		}
		if(residual) {
			// Process the line itself
			for(int i=1; i < residualsList.size(); i++) {
				residuals.push_back(residualsList.value(i).toDouble());
			}
		}
	}

	// Standard deviation
	// Retrieves the standard deviation values from rscript output
	QStringList stddevList = lines.value(line).split(QRegExp("\\s"), QString::SkipEmptyParts);
	double stddev = stddevList.value(1).toDouble();

	return GarchModel(omega, alpha, beta, residuals, stddev);
}
