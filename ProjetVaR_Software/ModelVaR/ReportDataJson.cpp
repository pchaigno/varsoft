#include "ReportDataJson.h"

ReportDataJson::ReportDataJson()
{
}

void ReportDataJson::addText(QString key, QString value)
{
    texts[key]=value;
}

void ReportDataJson::addImage(QString key, QString path)
{
    images[key]=path;
}

void ReportDataJson::addImage(QString key, QUrl path)
{
    images[key]=path.toLocalFile();
}

void ReportDataJson::addList(QString key, QList<QMap<QString, QString> > list)
{
    QJsonArray jsonArray;
    QMap<QString, QString> map;
    foreach(map, list)
    {
        QJsonObject jsonMap;
        foreach(QString key, map.keys())
        {
            jsonMap[key]=map[key];
        }
        jsonArray.append(jsonMap);
    }
    lists[key]=jsonArray;
}

QString ReportDataJson::toString()
{
    QJsonDocument data;
    QJsonObject document;
    document["text"]=texts;
    document["images"]=images;
    document["list"]=lists;
    data.setObject(document);
    return data.toJson();
}
