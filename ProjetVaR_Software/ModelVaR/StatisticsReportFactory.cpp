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
	QString file = this->getReportDir()+QString("statisticReport");
    QDateTime startDate = portfolio->retrieveStartDate();
    QDateTime endDate = portfolio->retrieveEndDate();
    file += "_"+portfolio->getName()+"_"+startDate.toString("dd-MM-yy")+"_"+endDate.toString("dd-MM-yy");
	return new StatisticsReport(file);
}
/**
 * @brief Create the Json for the statistic report.
 * @return
 */
ReportDataJson* StatisticsReportFactory::createJson()
{
    ReportDataJson* data = new ReportDataJson();

    data->addText("portefeuilleName",portfolio->getName());
    data->addText("dateDeb",portfolio->retrieveStartDate().toString("dd/MM/yyyy"));
    QDateTime startDate = portfolio->retrieveStartDate();
    QDateTime endDate = portfolio->retrieveEndDate();
    data->addText("dateFin",endDate.toString("dd/MM/yyyy"));
    data->addText("date",endDate.toString("dd/MM/yyyy"));
	QMap<QDateTime,double> valuesPortfolio;
	try {
		valuesPortfolio = portfolio->retrieveValuesByDate(startDate, endDate);
	} catch (std::exception & ) {
		QDateTime tmp = startDate;
		startDate = endDate;
		endDate = tmp;
		//bug des dates dans import ...
		valuesPortfolio = portfolio->retrieveValuesByDate(startDate, endDate);
	}

    data->addText("val",QString::number(valuesPortfolio[endDate]));

	QVector<double> values = valuesPortfolio.values().toVector();
    data->addText("moyenne",QString::number(getAverage(values)));
    data->addText("variance", QString::number(getVariance(values)));
    data->addText("kurtosis", QString::number(getKurtosis(values)));
    data->addText("min",QString::number(getMax(values)));
    data->addText("max",QString::number(getMin(values)));

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

    data->addList("asset",listAssets);

    data->addImage("chart1",generateChart1(portfolio->retrieveValuesByDate(startDate,endDate)));
    data->addImage("chart2",generateChart2(compo.keys(),startDate,endDate));


    return data;
}

QPixmap StatisticsReportFactory::generateChart1(QMap<QDateTime,double> values)
{
    QCustomPlot* customPlot = new QCustomPlot();
    customPlot->setLocale(QLocale(QLocale::French, QLocale::France));

    customPlot->addGraph();
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 200));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setBrush(QBrush(QColor(255/4.0,160,50,150)));

    QVector<double> keys;
    QVector<double> val;

    foreach(QDateTime date, values.keys())
    {
        keys.append(date.toTime_t());
    }
    val = values.values().toVector();
    customPlot->graph()->setData(keys, val);
    customPlot->graph()->setName("values");

    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("dd MMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set axis labels:
    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Values of the portfolio "+portfolio->getName());
    // set axis ranges to show all data:
    customPlot->xAxis->setRange(portfolio->retrieveStartDate().toTime_t(), portfolio->retrieveEndDate().toTime_t());
    customPlot->yAxis->setRange(getMin(values.values().toVector())-10, getMax(values.values().toVector())+10);
    // show legend:
    customPlot->legend->setVisible(false);
    QPixmap pix = customPlot->toPixmap();
    delete customPlot;
    return pix;
}

QPixmap StatisticsReportFactory::generateChart2(QList<Asset*> compo, QDateTime start, QDateTime end)
{
    QCustomPlot* customPlot = new QCustomPlot();
    customPlot->setLocale(QLocale(QLocale::French, QLocale::France));
    int gi = 0;
	double min = INT_MAX, max=INT_MIN;
    foreach(Asset* asset, compo)
    {
      customPlot->addGraph();
      QPen pen;
      pen.setColor(QColor(0, 0, 255, 200));
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setBrush(QBrush(QColor(255/4.0*gi,160,50,150)));
      QVector<double> time;
      QVector<double> value;
      QMap<QDateTime, double> mapData = asset->retrieveValuesByDate(start,end);

      foreach(QDateTime date, mapData.keys())
      {
          time.append(date.toTime_t());
      }
      value = mapData.values().toVector();
      min = qMin(min,getMin(value));
      max = qMax(max,getMax(value));
      customPlot->graph()->setData(time, value);
      customPlot->graph()->setName(asset->getName());
      gi++;
    }
    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("dd MMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set axis labels:
    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Value of each asset in the portfolio");
    // set axis ranges to show all data:
	customPlot->xAxis->setRange(start.toTime_t(), end.toTime_t());
	customPlot->yAxis->setRange(min-((min/100)*10), max+((max/100)*10));
    // show legend:
    customPlot->legend->setVisible(true);
    QPixmap pix = customPlot->toPixmap();
    delete customPlot;
    return pix;
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
/**
 * @brief Get the max value of the given vector
 * @param values
 * @return the max value
 */
double StatisticsReportFactory::getMax(QVector<double> values)
{
    double max = INT_MIN;
    foreach(double val, values)
    {
        max = qMax(max,val);
    }
    return max;
}
/**
 * @brief Get the min value of the given vector
 * @param values
 * @return the min value
 */
double StatisticsReportFactory::getMin(QVector<double> values)
{
    double min = INT_MAX;
    foreach(double val, values)
    {
        min = qMin(min,val);
    }
    return min;
}
/**
 * @brief Compute and get the kurtosis of the given vector
 * @param values
 * @return the kurtosis
 */
double StatisticsReportFactory::getKurtosis(QVector<double> values)
{
    return 0.;
}
