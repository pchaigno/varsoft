#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT ReportDataJson
{
public:
    ReportDataJson();

    void addText(QString key, QString value);
    void addImage(QString key, QString path);
    void addImage(QString key, QUrl path);
    void addList(QString key, QList<QMap<QString,QString> > list);

    QString toString();

private:
    QJsonObject texts;
    QJsonObject images;
    QJsonObject lists;
};
