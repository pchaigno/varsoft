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
 * @return The GARCH model.
 */
GarchModel RInterface::computeGarchModel(const Portfolio& portfolio, QDateTime date, int period) {

	QProcess process;
	QStringList arguments;
	QVector<double> residuals;
	QVector<double> stddev;

	bool debug = true;

//	QVector<double> logReturns = portfolio.retrieveLogReturns(date, period);

	if(debug) {
		qDebug() << "logReturns";
		qDebug() << logReturns;
	}

	QString rScriptFilePath = "../../R_scripts/garch.r";

	// The only command line argument passed to Rscript is
	// the R script file
	arguments << rScriptFilePath;

	// Makes the string sent to the Rscript standard input
	// Made of a single line containing the log-returns separated by space characters
	QString parameters;
	for(QVector<double>::const_iterator it=logReturns.begin(); it!=logReturns.end(); ++it) {
		parameters += QString::number(*it) + " ";
	}

	process.start("Rscript", arguments);

	// Writes to R standard input the previously created string
	process.write(parameters.toStdString().c_str());
	process.closeWriteChannel();
	process.waitForFinished();

	// Reads R output
	QByteArray rawOutput = process.readAllStandardOutput();

	if(debug) {
		qDebug() << rawOutput;
	}

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

	// Residuals (eta)
	// Retrieves the residuals from rscript output
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

	if(debug) {
		qDebug() << "residuals";
		qDebug() << residuals;
	}

	// Standard deviation
	// Retrieves the standard deviation values from rscript output
	QStringList stddevList;
	for(; line < lines.size(); line++) {
		stddevList = lines.value(line).split(QRegExp("\\s"), QString::SkipEmptyParts);
		for(int i=1; i < stddevList.size(); i++) {
			stddev.push_back(stddevList.value(i).toDouble());
		}
	}

	if(debug) {
		qDebug() << "stddev";
		qDebug() << stddev;
	}

	return GarchModel(omega, alpha, beta, residuals, stddev);
}
