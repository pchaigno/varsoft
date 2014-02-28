#pragma once

#include "Portfolio.h"
#include <QtTest>

class TestPortfolio: public QObject {
	Q_OBJECT

private:
	Portfolio father;
	Portfolio son;

public:
	TestPortfolio();

private Q_SLOTS:
	void testId();
	void testName();
};