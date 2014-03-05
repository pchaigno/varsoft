#include "ImportNewData.h"

/**
* @brief Import method for Yahoo files
* @param name The name of the stock
* @param file The file where are located the values.
* @param origin The origin of the file with the values.
* @param firstDate The date of the first value defined.
* @param lastDate The date of the last value defined.
*/
void ImportNewData::import(const QString &name, const QString &file, const QString &origin, const QDateTime &firstDate, const QDateTime &lastDate) const{
		QString data;
		QFile importedCSV(file);
		QStringList rowOfData;
		QStringList rowData;
		data.clear();
		rowOfData.clear();
        rowData.clear();
        // column_of_values_to_import =6;


        //if (origin == Yahoo)
        //  column_of_values_to_import = 6
        //else if(origin == ProjetVaR)
        //  column_of_values_to_import = 2
        //==> no strategy, no duplicated code ....

		if (importedCSV.open(QFile::ReadOnly))
			{
				data = importedCSV.readAll();
				rowOfData = data.split("\r\n");
				importedCSV.close();
			}
		qDebug() << "Données importées";

        //CREATION DU FICHIER DES DONNEES IMPORTEES
		//Faire des noms aléatoires et uniques
        QString namealea = name+".txt";
        qDebug() << namealea;
		QFile fileCreated(namealea);
		// On ouvre notre fichier en lecture seule et on vérifie l'ouverture
		if (!fileCreated.open(QIODevice::WriteOnly | QIODevice::Text))
		   return;
		QTextStream flux(&fileCreated);
		flux.setCodec("UTF-8");

		// x = 1 to avoid the first line with labels
		// rowOfData.size()-1 to avoid a blank line a the end of the file
		for (int x =1; x < rowOfData.size()-1; x++)
		{
			rowData = rowOfData.at(x).split(",");
			QDateTime currentDate = QDateTime::fromString(rowData[0],"yyyy-MM-dd");
			if ((firstDate >= currentDate) && (currentDate >= lastDate)){
				qDebug() << rowData[6];
                //useful to print into a tableWidget
                    QTableWidgetItem* item = new QTableWidgetItem();
                    // the index of the interesting column is always the same for yahoo files
                    item->setText(rowData[6]);
				flux << rowData[0] << "," << rowData[6] << "\n";
			}
            //else{
                // seulement quand la derniere date est atteinte
              //  break;
            //}
		}
        fileCreated.close();
        //Asset a1 = Asset(name,namealea,origin,firstDate,lastDate);
	}
