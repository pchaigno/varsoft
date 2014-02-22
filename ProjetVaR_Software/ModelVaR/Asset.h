#pragma once

#include <QString>
#include <QDateTime>

class Asset {
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
};
