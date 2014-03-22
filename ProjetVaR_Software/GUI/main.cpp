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

    return a.exec();
}
