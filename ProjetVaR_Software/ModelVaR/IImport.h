#pragma once
#include <QDateTime>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QTableWidgetItem>
#include "Asset.h"
#include "ModelVaR_global.h"

/**
* @brief Import Strategy Interface
*/
class MODELVARSHARED_EXPORT IImport
{
public:
    virtual void import(const QString &name, const QString &file, const QString &origin,
                        const QDateTime &firstDate, const QDateTime &lastDate) const =0;
};

