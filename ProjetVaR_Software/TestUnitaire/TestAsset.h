#pragma once

#include "Asset.h"
#include <QtTest>

class TestAsset: public QObject {
	Q_OBJECT

private:
	Asset google;

public:
	TestAsset();

private Q_SLOTS:
	void testId();
	void testName();
};