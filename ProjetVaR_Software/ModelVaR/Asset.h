#pragma once

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT Asset {
private:
    QString file;
    QString name;
    QDateTime firstDate;
    QDateTime lastDate;

public:
    Asset();
    Asset(QString name, QString file, QDateTime firstDate, QDateTime lastDate);
    QString getFile() const;
    QString getName() const;
    QDateTime getFirstDate() const;
    QDateTime getLastDate() const;
    void changeName(QString name);
    QVector<double> getValues(const QDateTime &startDate, const QDateTime &endDate);
};
