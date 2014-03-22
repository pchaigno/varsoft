#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include "Report.h"
#include "Portfolio.h"
#include "DocxGenerator.h"
#include "StatisticsReportFactory.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QMap<Asset*,int> compo;
    QVector<Report*> reports;
    Portfolio * port = new Portfolio(QString("test"),compo,reports);
    ReportFactory * factory = new StatisticsReportFactory(port);
    Report * report = factory->buildReport();
    ReportGenerator * gen = new DocxGenerator(report);
    gen->generate();

    return a.exec();
}
