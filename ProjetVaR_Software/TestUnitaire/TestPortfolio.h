#pragma once

#include "Portfolio.h"
#include <QtTest>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QVector>
#include "Asset.h"

class TestPortfolio: public QObject {
	Q_OBJECT

private:
	Portfolio father;
	Portfolio son;
	Portfolio uncle;

public:
	TestPortfolio();

private Q_SLOTS:
	void testId();
	void testName();
	void testRetrieveValues();
};
