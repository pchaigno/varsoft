#pragma once
#include "IImport.h"
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT ImportNewData : public IImport{
public:
    virtual void import(const QString &name, const QString &file, const QString &origin,
                        const QDateTime &firstDate, const QDateTime &lastDate) const;
};
