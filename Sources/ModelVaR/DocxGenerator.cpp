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
#include "DocxGenerator.h"

DocxGenerator::DocxGenerator(Report *report, QString progPath) : ReportGenerator(report) {
	prog=progPath;
	errorTable.append("");
	errorTable.append("Incorrect parameters for the program.");
	errorTable.append("Invalid JSON");
	errorTable.append("Error while reading the template file. ");
	errorTable.append("Error while creating the context for the report.");
	errorTable.append("Error from docxreport about the generation of the DOCX.");
	errorTable.append("Error from docxreport about the convertion to PDF.");
	errorTable.append("Error from docxreport about the generation of the PDF.");
	errorTable.append("In/Out exception: file which can't be opened, written or read. ");
	errorTable.append("The template file can't be found.");
	errorTable.append("The text element in the JSON is missing.");
	errorTable.append("The images element in the JSON is missing.");
	errorTable.append("The list element in the JSON is missing.");
}

/**
 * @brief Generates the DOCX file
 */
void DocxGenerator::generate() {
	if (QFile::exists(prog) && QFile::exists(report->getTemplateFile())) {
		QProcess  docx;
		docx.start("java", QStringList() << "-jar" << prog << report->getTemplateFile() << report->getFile());
		if(!docx.waitForStarted())
		{
			manageError(docx.error());
		}

		QString data = report->getDataJson()->toString();
		int res = docx.write(data.toLatin1(),data.length());
		if (res==-1)
		{
			manageError(docx.error());
		}

		if (!docx.waitForBytesWritten())
		{
			manageError(docx.error());
		}
		docx.closeWriteChannel();

		if (docx.waitForFinished())
		{
			int exitCode=docx.exitCode();
			bool hasCrashed = docx.exitStatus()==QProcess::CrashExit;
			if (exitCode != 0 || hasCrashed) {
				throw std::runtime_error("DocxGenerator error ("+QString::number(exitCode).toStdString()+") : "+errorTable[exitCode].toStdString());
			}
		}
		else
		{
			manageError(docx.error());
		}
	} else {
		if (!QFile::exists(prog))
			throw std::invalid_argument("DocXGenerator does not exists on the disk.");
		else if (!QFile::exists(report->getTemplateFile()))
			throw std::invalid_argument("Template report ("+report->getTemplateFile().toStdString()+") does not exist.");
	}
}

void DocxGenerator::manageError(QProcess::ProcessError error)
{
	QString message;
	switch(error)
	{
		case QProcess::FailedToStart:
			message="The process failed to start. Please try again or contact the administrator.";
			break;
		case QProcess::Crashed:
			message="The program DocxGenerator has crashed. Please try again or contact the administrator.";
			break;
		case QProcess::Timedout:
			message="The program DocxGenerator took too long to execute. Please try again or contact the administrator.";
			break;
		case QProcess::WriteError:
			message="The program DocxGenerator got a error during the writing in the input. Please try again or contact the administrator.";
			break;
		case QProcess::ReadError:
			message="The program DocxGenerator got a error during reading. Please try again or contact the administrator.";
			break;
		case QProcess::UnknownError:
		default:
			message="An unknow error has occurred. Please try again or contact the administrator.";
			break;
	}
	throw std::runtime_error(message.toStdString());
}
