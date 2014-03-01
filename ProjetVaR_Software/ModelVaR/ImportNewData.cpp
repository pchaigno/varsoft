#include "ImportNewData.h"

void ImportNewData::import(const QString file, const QString name, const QDateTime firstDate, const QDateTime lastDate) const{
		QString fileName = file;
		QString data;
		QFile importedCSV(fileName);
		QStringList rowOfData;
		QStringList rowData;
		data.clear();
		rowOfData.clear();
		rowData.clear();

		if (importedCSV.open(QFile::ReadOnly))
			{
				data = importedCSV.readAll();
				rowOfData = data.split("\r\n");
				importedCSV.close();
			}
		qDebug() << "Données importées";

//////CREATION DU FICHIER DES DONNEES IMPORTEES
		//Faire des noms aléatoires et uniques
		QString namealea = "Qt.txt";
		QFile fileCreated(namealea);
		// On ouvre notre fichier en lecture seule et on vérifie l'ouverture
		if (!fileCreated.open(QIODevice::WriteOnly | QIODevice::Text))
		   return;
		QTextStream flux(&fileCreated);
		flux.setCodec("UTF-8");

		// x = 1 to avoid the first line with labels
		// rowOfData.size()-1 to avoid a blank line a the end of the file

		// TODO : avec les dates, ne sélectionner que les parties intéressantes
		for (int x =1; x < rowOfData.size()-1; x++)
		{
			rowData = rowOfData.at(x).split(",");
			if ((QDateTimeEdit::dateTimeFromText(rowData[0]) >= firstDate) && (QDateTimeEdit::dateTimeFromText(rowData[0]) <= lastDate)){
				qDebug() << rowData[6];
				//  ui->tableWidget->insertRow(indice);
				QTableWidgetItem* item = new QTableWidgetItem();
				// the index of the interesting column is always the same for yahoo files
				item->setText(rowData[6]);
				flux << rowData[0] << "," << rowData[6] << "\n";
			}
			//ui->tableWidget->setItem(x-1,0,item);
		}
		//obligé de faire des conversions pour passer de QString à QDateTime
		QString fd = rowOfData.at(1).split(",")[0];
		//firstDate = QDateTime::fromString(fd,"yyyy:MM:dd ");
		QString ld = rowOfData.at(rowOfData.size()-1).split(",")[0];
		//lastDate = QDateTime::fromString(ld,"yyyy:MM:dd ");
		Asset a1 = Asset(name,namealea,firstDate,lastDate);
	}
