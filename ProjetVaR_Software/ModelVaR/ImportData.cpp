#include "ImportData.h"

/**
* @brief Import method for our own CSV files
* @param name The name of the stock
* @param file The file where are located the values.
* @param origin The origin of the file with the values.
* @param firstDate The date of the first value defined.
* @param lastDate The date of the last value defined.
*/
void ImportData::import(const QString &name, const QString &file, const QString &origin, const QDateTime &firstDate, const QDateTime &lastDate)const{
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
                rowOfData = data.split("\n");
				importedCSV.close();
			}
		qDebug() << "Données importées";

        for (int x =0; x < rowOfData.size(); x++)
		{
		   rowData = rowOfData.at(x).split(",");

               qDebug() << rowData[1];
			   QTableWidgetItem* item = new QTableWidgetItem();
               item->setText(rowData[2]);
		}

		//Asset a1 = Asset("name",name,firstDate,lastDate);
	}
