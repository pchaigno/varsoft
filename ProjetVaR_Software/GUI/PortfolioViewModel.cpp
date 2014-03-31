#include "PortfolioViewModel.h"

PortfolioViewModel::PortfolioViewModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

PortfolioViewModel::PortfolioViewModel(Portfolio* portfolio, QObject *parent) :
    QAbstractTableModel(parent)
{
    this->portfolio = portfolio;
    createDataStructure();
}

int PortfolioViewModel::rowCount(const QModelIndex &parent) const
{
    int row=0;
    foreach(QVector<QString> tab, mydata)
    {
        if (tab.count()>row)
            row=tab.count();
    }

    return row;
}

int PortfolioViewModel::columnCount(const QModelIndex &parent) const
{
    return mydata.count();
}

QVariant PortfolioViewModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        if (index.column() < mydata.count() && index.row() < mydata[index.column()].count())
            return QVariant(mydata[index.column()][index.row()]);
    }
    return QVariant();
}


QVariant PortfolioViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    #define NB_COLUMNS_BEFORE_ASSET 2
    if (role != Qt::DisplayRole)
           return QVariant();

       if (orientation == Qt::Horizontal)
       {
            if (section<NB_COLUMNS_BEFORE_ASSET)
                return QString("");
            else
            {
                QList<Asset*> values = portfolio->getComposition().keys();
                return QString("%1").arg(values.at(section-NB_COLUMNS_BEFORE_ASSET)->getName());
            }
       }
       else
       {
           return QString("Row %1").arg(section);
       }
}

/**
 * @brief PortfolioItemModel::flags
 * Define the flags for the model, here is ItemIsSelectable and ItemIsEnable
 * (this method is call by Qt and should never be called by user, see Qt'doc)
 * @param index
 * @return the flags
 */
Qt::ItemFlags PortfolioViewModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void PortfolioViewModel::setPortfolio(Portfolio *portfolio)
{
    this->portfolio=portfolio;
    createDataStructure();
}

bool PortfolioViewModel::removePortfolio()
{
    beginRemoveRows(QModelIndex(),0,mydata[0].count());
    mydata.clear();
    endRemoveRows();
    return true;

}

void PortfolioViewModel::createDataStructure(){
    QMap<Asset*, int> values = portfolio->getComposition();
    QMap<QDateTime, double> dates = portfolio->retrieveValuesByDate(portfolio->retrieveFirstDate(),portfolio->retrieveLastDate());
    QVector<QString> columns;

    columns.append("");
    foreach(QDateTime date, dates.keys())
    {
        columns.append(date.toString("yyyy-MM-dd"));
    }
    mydata+=columns;

    columns.clear();
    columns.append("");
    foreach(double value, dates.values())
    {
        columns.append(QString::number(value));
    }
    mydata+=columns;


    foreach(Asset* asset, values.keys())
    {
        columns.clear();
        QVector<double> valvector = asset->retrieveValues();

        foreach(double val,valvector)
        {
            columns.append(QString::number(val));
        }
        mydata+=columns;
    }

    /*
    //QMap<QDateTime, double> dates = portfolio->retrieveValuesByDate(portfolio->retrieveFirstDate(), portfolio->retrieveLastDate());


    for (int i=0; i<values.size(); i++)
       //dates.size() => numberOfDates
        matrix[i].fill("", dates.size());

    //Dates and values are added
    int i =0;
    for(QMap<QDateTime, double>::const_iterator it=dates.begin(); it!=dates.end(); ++it) {
        matrix[i][0]=it.key().toString("yyyy-MM-dd");
        matrix[i][1]=QString::number(it.value());
        i++;
    }

    //each asset's value is added
    int j =0;
    for(QMap<Asset*, int>::const_iterator it=values.begin(); it!=values.end(); ++it) {
        //get all the values
        int k =2;
        QVector<double> val = it.key()->getValues(it.key()->getFirstDate(),it.key()->getLastDate());
        for(int i=0; i < dates.size(); i++){
            // no verification upon the date's existance
            if (k<matrix[j].count())
                matrix[j][k] = QString::number(val.at(k));
            k++;
        }
        j++;
    }*/

   // mydata=matrix;
}
