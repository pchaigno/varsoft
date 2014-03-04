#include "TestImportNewData.h"

/**
* @brief Initializes an asset for the tests.
*/
TestImportNewData::TestImportNewData() {
    TestImportNewData::stockName = "Gogole";
    TestImportNewData::firstDate = "2014-01-02";
    TestImportNewData::lastDate = "2014-01-01";
    TestImportNewData::fileName = "test.csv";
    TestImportNewData::origin = "Yahoo";
}

/**
* @brief Checks that the firstDate and the lastDate of the generated file correspond to the params
*/
void TestImportNewData::testDates() {
    //mettre une valeur par défaut au firstdate et lastdate
    //les donner en param de l'algo d'importation
    //lire le fichier généré
    //comparer les dates obtenues
    //QString file = QFileDialog::getOpenFileName(this, ("Open File"), "C:/", ("csv File(*.csv)"));
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

    //CREATION DU FICHIER DES DONNEES IMPORTEES
    //Faire des noms aléatoires et uniques
    QString namealea =  TestImportNewData::stockName+"_"+file+".txt";
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
            QTableWidgetItem* item = new QTableWidgetItem();
            // the index of the interesting column is always the same for yahoo files
            item->setText(rowData[6]);
            flux << rowData[0] << "," << rowData[6] << "\n";
        }
    }
    //Asset a1 = Asset(name,namealea,origin,firstDate,lastDate);
}
/*
    QCOMPARE(this->google.getId(), -1);
    this->google.setId(42);
    QCOMPARE(this->google.getId(), 42);
    try {
        this->google.setId(43);
    } catch(const IdAlreadyAttributedException e) {
        return;
    }
    QFAIL("No exception thrown when attributed an id to an asset twice.");

}
*/
/**
* @brief Checks that the name can actually be changed.
*/
void TestImportNewData::testName() {
    /*
    QVERIFY(this->google.getName() == "Google");
    this->google.changeName("Googl");
    QVERIFY(this->google.getName() == "Googl");
    */
}
