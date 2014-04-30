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
QPair<double, double> RInterface::checkCorrelation(const Portfolio& portfolio, int timeLag, QDateTime date, int period) {

	// Check that parameters are correct
	if(timeLag <= 0) {
		throw std::invalid_argument("The timeLag parameter must be strictly positive");
	}
	if(period <= 0 ) {
		throw std::invalid_argument("The period parameter must be strictly positive");
	}

	// The statistical value and p-value couple
	QPair<double, double> result;

	// The only command line argument passed to Rscript is
	// the R script file
	QString rScriptFilePath = "../../R_scripts/correlation-niveau.r";
	QStringList arguments;
	arguments << rScriptFilePath;

	// Makes the string sent to the Rscript standard input
	// Made of two lines, one paramater a line
	// timeLag on the first, the returns on the second,separated by space characters
	QString parameters = QString::number(timeLag) + "\n";
	QVector<double> returns = portfolio.retrieveReturns(date, period);
	for(QVector<double>::const_iterator it=returns.begin(); it!=returns.end(); ++it) {
		parameters += QString::number(*it) + " ";
	}

	QProcess process;
	process.start("rscript", arguments);
	process.waitForStarted();
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
	QStringList lines;
	lines = output.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

	// Gets only the values (removes matrix indices)
	double qstat = lines.value(2).mid(6).toDouble();
	double pvportm = lines.value(5).mid(6).toDouble();

	result.first = qstat;
	result.second = pvportm;

	return result;
}

/**
 * @brief Call the R script performing the square correlation test.
 * @param portfolio The portfolio on which the correlation test is performed
 * @param timeLag Time lag of the statistical test
 * @param date The date from which the historical returns will be taken
 * @param period The number of returns
 * @return The statistical value and p-value couple
 */
QPair<double, double> RInterface::checkSquareCorrelation(const Portfolio& portfolio, int timeLag, QDateTime date, int period) {

	// Check that parameters are correct
	if(timeLag <= 0) {
		throw std::invalid_argument("The timeLag parameter must be strictly positive");
	}
	if(period <= 0 ) {
		throw std::invalid_argument("The period parameter must be strictly positive");
	}

	// The statistical value and p-value couple
	QPair<double, double> result;

	// The only command line argument passed to Rscript is
	// the R script file
	QString rScriptFilePath = "../../R_scripts/correlation-carre.r";
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
	double ststdport = lines.value(1).mid(4).toDouble();
	double pvportcarre = lines.value(3).mid(4).toDouble();

	result.first = ststdport;
	result.second = pvportcarre;

	return result;
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
