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
 * @brief Call the R script for the correlation test.
 * @param portfolio The portfolio to test.
 * @return True if the test succeed.
 */
bool RInterface::checkCorrelation(const Portfolio& portfolio) {
	// TODO
	return false;
}

/**
 * @brief Call the R script for the square correlation test.
 * @param portfolio The portfolio to test.
 * @return True if the test succeed.
 */
bool RInterface::checkSquareCorrelation(const Portfolio& portfolio) {
	// TODO
	return false;
}

/**
 * @brief Call the R script to compute the GARCH model of a portfolio.
 * @param portfolio The portfolio.
 * @param date The date from which previous returns will be used to compute the Garch model
 * @param period The number of days to consider to compute the Garch model
 * @return The Garch model.
 */
GarchModel RInterface::computeGarchModel(const Portfolio& portfolio, QDate date, int period) {

	if(period < 3) {
		throw std::invalid_argument("The period argument must at least 3 to initialize garch model computation");
	}

	// The only command line argument passed to Rscript is
	// the R script file
	QStringList arguments;
	QString rScriptFilePath = "../../R_scripts/garch.r";
	arguments << rScriptFilePath;

	// Makes the string that will be sent to the Rscript standard input
	// Made of a single line containing the log-returns separated by space characters
	QVector<double> logReturns = portfolio.retrieveLogReturns(date, period);
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
