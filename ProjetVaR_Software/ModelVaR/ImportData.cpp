#include "ImportData.h"

void ImportData::import(const QString file, const QString name, const QDateTime firstDate, const QDateTime lastDate)const{
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

		for (int x =1; x < rowOfData.size()-1; x++)
		{
		   rowData = rowOfData.at(x).split(",");

			   qDebug() << rowData[6];
			   //  ui->tableWidget->insertRow(indice);
			   QTableWidgetItem* item = new QTableWidgetItem();
			   // the index of the interesting column is always the same for yahoo files
			   item->setText(rowData[6]);
			   //ui->tableWidget->setItem(x-1,0,item);
		}

		//Asset a1 = Asset("name",name,firstDate,lastDate);
	}
