/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "StatisticsReportFactory.h"

/**
 * @brief Constructor
 */
StatisticsReportFactory::StatisticsReportFactory(Portfolio * portfolio):
    ReportFactory() {
    this->portfolio=portfolio;
}
/**
 * @brief Generate a name and return a new statistic report
 * @return a pointer to the report
 */
Report *StatisticsReportFactory::createReport()
{
    QString file = QString("../resources/Reports/statisticReport");
    QDateTime startDate = portfolio->retrieveStartDate();
    QDateTime endDate = portfolio->retrieveEndDate();
    file += "_"+portfolio->getName()+"_"+startDate.toString("dd-MM-yy")+"_"+endDate.toString("dd-MM-yy");
    return new StatisticsReport(file);
}
/**
 * @brief Create the Json for the statistic report.
 * @return
 */
ReportDataJson StatisticsReportFactory::createJson()
{
    ReportDataJson data;

    data.addText("portefeuilleName",portfolio->getName());
    data.addText("dateDeb",portfolio->retrieveStartDate().toString("dd/MM/yyyy"));
    QDateTime endDate = portfolio->retrieveEndDate();
    data.addText("dateFin",endDate.toString("dd/MM/yyyy"));
    data.addText("date",endDate.toString("dd/MM/yyyy"));
    QMap<QDateTime,double> valuesPortfolio = portfolio->retrieveValuesByDate(endDate,endDate);
    data.addText("val",QString::number(valuesPortfolio[endDate]));

    QVector<double> values = portfolio->retrieveValues();
    data.addText("moyenne",QString::number(getAverage(values)));
    data.addText("variance", QString::number(getVariance(values)));
    qSort(values.begin(),values.end());
    data.addText("min",QString::number(values.first()));
    data.addText("max",QString::number(values.last()));

    QList<QMap<QString,QString> > listAssets;
    QVector<Asset*> assets = portfolio->getAssets();
    QMap<Asset*,int> compo = portfolio->getComposition();
    foreach(Asset* asset, assets)
    {
        QMap<QDateTime,double> values =  asset->retrieveValuesByDate(endDate,endDate);
        QMap<QString,QString> map;
        map["Name"]=asset->getName();
        map["Qte"]=QString::number(compo[asset]);
        map["Unit"]=QString::number(values[endDate]);
        map["Total"]=QString::number(compo[asset]*values[endDate]);

        listAssets.append(map);
    }

    data.addList("asset",listAssets);

    return data;
}
/**
 * @brief Get the average of the given vector of values
 * @param values
 * @return the average
 */
double StatisticsReportFactory::getAverage(QVector<double> values)
{
    double average=0;
    foreach(double val, values)
    {
        average+=val;
    }

    return average/values.count();
}
/**
 * @brief Get the variance of the given vector of values
 * @param values
 * @return the variance
 */
double StatisticsReportFactory::getVariance(QVector<double> values)
{
    double m = getAverage(values);
    double variance = 0;

    foreach (double val, values)
    {
        variance += (val-m)*(val-m);
    }
    return variance / values.count();
}
