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
    return mydata[0].count();
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
    if (role != Qt::DisplayRole)
           return QVariant();

       if (orientation == Qt::Horizontal)
           return QString("Column %1").arg(section);
       else
           return QString("Row %1").arg(section);
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
    /*BOOST_SCOPE_EXIT(this_){
        this_->endRemoveRows();
    }BOOST_SCOPE_EXIT_END//*/
    mydata.clear();
    endRemoveRows();
    return true;
    /*
    beginRemoveRows(QModelIndex(),row,row);
    Asset * asset = assetList.at(row);
    bool res = assetList.removeOne(asset);
    if (res)
        delete asset;
    endRemoveRows();
    */
}

void PortfolioViewModel::createDataStructure(){
    //portfolio->getComposition().size() => number of assets
    //we need to add two colums more for : the dates and the values of the porfolio
    QDateTime endDate3(QDate(2014, 1, 6), QTime(0, 0, 0));
    QDateTime endDate2(QDate(2014, 1, 7), QTime(0, 0, 0));
    QDateTime endDate1(QDate(2014, 1, 8), QTime(0, 0, 0));
    QMap<Asset*, int> values = portfolio->getComposition();
    QMap<QDateTime, double> dates = QMap<QDateTime, double>();
    dates[(endDate3)] = 6;
    dates[(endDate2)] = (double)5;
    dates[(endDate1)] = (double)4;
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
        columns.append(asset->getName());
        QVector<double> valvector = asset->getValues(asset->getFirstDate(),asset->getLastDate());

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
