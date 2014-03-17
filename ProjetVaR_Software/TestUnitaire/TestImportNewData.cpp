#include "TestImportNewData.h"

/**
* @brief Initializes an asset for the tests.
*/
TestImportNewData::TestImportNewData() {
    TestImportNewData::stockName = "Gogole";
    TestImportNewData::firstDate = "2014-02-07";
    TestImportNewData::lastDate = "2014-01-01";
    TestImportNewData::origin = "Yahoo";
    QString data;
    QFile importedCSV("../../CSV_examples/table.csv");
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

    TestImportNewData::newFile = "../../CSV_examples/"+TestImportNewData::stockName+"_test.csv";
    QFile fileCreated(TestImportNewData::newFile);
    if (!fileCreated.open(QIODevice::WriteOnly | QIODevice::Text))
       return;
    QTextStream flux(&fileCreated);
    flux.setCodec("UTF-8");
    const QDateTime &fiDate = QDateTime::fromString(TestImportNewData::firstDate,"yyyy-MM-dd");
    const QDateTime &laDate = QDateTime::fromString(TestImportNewData::lastDate,"yyyy-MM-dd");
    for (int x =1; x < rowOfData.size()-1; x++)
    {
        rowData = rowOfData.at(x).split(",");
        QDateTime currentDate = QDateTime::fromString(rowData[0],"yyyy-MM-dd");
        if ((fiDate >= currentDate)){
            if(laDate >= currentDate){
                break;
            }
            flux << rowData[0] << "," << rowData[6] << "\n";
        }
    }
    fileCreated.close();
}

/**
* @brief Checks that the firstDate and the lastDate of the generated file correspond to the params
*/
void TestImportNewData::testDates() {
    QString data;
    QFile importedCSV(TestImportNewData::newFile);
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();
    qDebug() << TestImportNewData::newFile;
    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }
    //first date
    rowData = rowOfData.at(0).split(",");
    qDebug() << rowData[0];
    QVERIFY((QDateTime::fromString(TestImportNewData::firstDate,"yyyy-MM-dd")) >= (QDateTime::fromString(rowData[0],"yyyy-MM-dd")));

    //last date
    rowData = rowOfData.at(rowOfData.size()-2).split(",");
    qDebug() << rowData[0];
    QVERIFY((QDateTime::fromString(TestImportNewData::lastDate,"yyyy-MM-dd")) <= (QDateTime::fromString(rowData[0],"yyyy-MM-dd")));
}
