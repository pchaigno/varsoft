#include "ImportNewData.h"

void ImportNewData::import(QString s) const{
		QString fileName = s;
		QString data;
		QFile importedCSV(fileName);
		QStringList rowOfData;
		QStringList rowData;
		QDateTime firstDate;
		QDateTime lastDate;
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
		QString name = "Qt.txt";
		QFile file(name);
		// On ouvre notre fichier en lecture seule et on vérifie l'ouverture
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		   return;
		QTextStream flux(&file);
		flux.setCodec("UTF-8");

		//TODO : Add rows automaticaly according to the file imported
		// Try to import with a file with a size lower or equals to 9*9

		// x = 1 to avoid the first line with labels
		// rowOfData.size()-1 to avoid a blank line a the end of the file
		for (int x =1; x < rowOfData.size()-1; x++)
		{
		   rowData = rowOfData.at(x).split(",");

			   qDebug() << rowData[6];
			   //  ui->tableWidget->insertRow(indice);
			   QTableWidgetItem* item = new QTableWidgetItem();
			   // the index of the interesting column is always the same for yahoo files
			   item->setText(rowData[6]);

			   // Écriture des différentes lignes dans le fichier, mais il devient imcompatible avec l'importation
			   flux << rowData[0] << "," << rowData[6] << "\n";
			   //ui->tableWidget->setItem(x-1,0,item);
		}
		//obligé de faire des conversions pour passer de QString à QDateTime
		QString fd = rowOfData.at(1).split(",")[0];
		firstDate = QDateTime::fromString(fd,"yyyy:MM:dd ");
		QString ld = rowOfData.at(rowOfData.size()-1).split(",")[0];
		lastDate = QDateTime::fromString(ld,"yyyy:MM:dd ");
		Asset a1 = Asset("name",name,firstDate,lastDate);
	}
