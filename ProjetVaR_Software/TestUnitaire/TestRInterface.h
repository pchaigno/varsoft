#pragma once

#include <QtTest>
#include <QDir>
#include <QMap>
#include <QVector>
#include "RInterface.h"

class TestRInterface: public QObject {
	Q_OBJECT

private:

public:
	TestRInterface();

private Q_SLOTS:
	void testCheckCorrelation();
};
