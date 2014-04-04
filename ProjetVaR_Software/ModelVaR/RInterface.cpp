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
 * @param portfolio The portfolio on which the correlation test is performed
 * @param timeLag Time lag of the stastical test
 * @param startDate The start date of the returns used for the test
 * @param endDate The end date of the returns used for the test
 * @return The statistical value and p-value couple
 */
QPair<double, double> RInterface::checkCorrelation(/*const Portfolio& portfolio, int timeLag, QDateTime startDate, QDateTime endDate*/) {

	QVector<double> returns;
	QProcess process;
	QStringList arguments;
	QPair<double, double> result;

	//returns = portfolio.retrieveReturns(startDate, endDate);
	//portfolio.retrieveReturns();

	// Parametres bidon pour tester
	int abc = 1;
	returns.push_back(1);
	returns.push_back(2);
	returns.push_back(3);

	QString rScriptFilePath = "../../R_scripts/correlation-niveau.r";
	//QString file = "../../R_scripts/correlation-carre.r";
	//QString file = "../../R_scripts/simple.r";
	//QString file = "../../R_scripts/simplefunction.r";
	//QString file = "../../R_scripts/stdin.r";

	// The only command line argument passed to Rscript is
	// the R script file
	arguments << rScriptFilePath;

	// Makes the string sent to the Rscript standard input
	// Made of two lines, one paramater a line
	// timeLag, then the returns separated by space characters
	QString parameters;
	parameters = QString::number(abc) + "\n";
	for(QVector<double>::const_iterator it=returns.begin(); it!=returns.end(); ++it) {
		parameters += QString::number(*it) + " ";
	}

	process.start("Rscript", arguments);

	// Writes to R standard input the previously created string
	process.write(parameters.toStdString().c_str());
	process.closeWriteChannel();

	if (!process.waitForFinished()) {}
			// TOIMPROVE: Manage properly
			//return false;

	// Reads R output
	// Why these question marks in the string
	// -> unicode related apparently
	QByteArray rawOutput = process.readAllStandardOutput();

	// Convert it to QString
	QString output = QString::fromUtf8(rawOutput);

	// Splits the output by newline
	// Removes empty lines as well
	QStringList tokens;
	tokens = output.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

	// Gets only the values (removes matrix indices)
	double qstat = tokens.value(2).mid(6).toDouble();
	double pvportm = tokens.value(5).mid(6).toDouble();

	result.first = qstat;
	result.second = pvportm;

	return result;
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
GarchModel RInterface::computeGarchModel(const Portfolio& portfolio) {
	// TODO
	return GarchModel();
}
