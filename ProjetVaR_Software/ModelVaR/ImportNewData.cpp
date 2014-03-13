#include "ImportNewData.h"
#include <QMessageBox>
#include "SessionSaver.h"

/**
* @brief Import method for Yahoo files
* @param name The name of the stock
* @param file The file where are located the values.
* @param origin The origin of the file with the values.
* @param startDate The date of the first value defined.
* @param endDate The date of the last value defined.
* @throw BadFile The file is not handled
*/
void ImportNewData::import(const QString &name, const QString &file, const QString &origin, const QDateTime &startDate, const QDateTime &endDate) const{
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
                rowOfData = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
				importedCSV.close();
			}

        //FILE CREATION OF IMPORTED DATA
        //Do random names
        //uint time = QDateTime::toTime_t();
        //QString stime = QString::number(time);
        QString namealea = name+".csv";
		QFile fileCreated(namealea);
        // The file is open in write-only mode and we check the opening
		if (!fileCreated.open(QIODevice::WriteOnly | QIODevice::Text))
		   return;
		QTextStream flux(&fileCreated);
		flux.setCodec("UTF-8");

		// x = 1 to avoid the first line with labels
		// rowOfData.size()-1 to avoid a blank line a the end of the file

        for (int x =1; x < rowOfData.size()-1; x++)
        {
            rowData = rowOfData.at(x).split(",");
            //TODO : Check the date is correct
            //if(!(rowData.count() >= 2) || !(rowData.count() >= 6)){
            if(!(rowData.count() >= 6)){
                 QMessageBox::warning(0, "Attention","Le fichier que vous avez essayé d'importer n'est pas valide");
                 fileCreated.close();
                 fileCreated.remove();
                 break;
            }

            QDateTime currentDate = QDateTime::fromString(rowData[0],"yyyy-MM-dd");
            if ((startDate >= currentDate)){
                if(endDate >= currentDate){
                    break;
                }
                    //useful to print into a tableWidget
                        //QTableWidgetItem* item = new QTableWidgetItem();
                        // the index of the interesting column is always the same for yahoo files
                        //item->setText(rowData[6]);
                        //ui->tableWidget->setItem(x-1,0,item);
                flux << rowData[0] << "," << rowData[6] << "\n";
            }
        }
        fileCreated.close();

      //  Asset &a = Asset(name,namealea,origin,startDate,endDate);
      //  SessionSaver::saveAsset(a);
	}
