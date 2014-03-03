#include "ImportNewData.h"

void ImportNewData::import(const QString name, const QString file, const QString origin, const QDateTime firstDate, const QDateTime lastDate) const{
		//QString fileName = file;
		QString data;
		QFile importedCSV(file);
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
		QString namealea = name+"_"+file+".txt";
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
			//QString format = "yyyy-MM-dd";
			QDateTime currentDate = QDateTime::fromString(rowData[0],"yyyy-MM-dd");
			if ((firstDate >= currentDate) && (currentDate >= lastDate)){
				qDebug() << rowData[6];
				//  ui->tableWidget->insertRow(indice);
				QTableWidgetItem* item = new QTableWidgetItem();
				// the index of the interesting column is always the same for yahoo files
				item->setText(rowData[6]);
				flux << rowData[0] << "," << rowData[6] << "\n";
			}
			//ui->tableWidget->setItem(x-1,0,item);
		}
		//Asset a1 = Asset(name,namealea,origin,firstDate,lastDate);
	}
