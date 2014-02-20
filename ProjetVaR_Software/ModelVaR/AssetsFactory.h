#pragma once

#include <QString>
#include "Asset.h"

class AssetsFactory {
private:
	static AssetsFactory instance;

public:
	Asset* retrieveAsset(QString name);
	static AssetsFactory& getInstance() {
		return instance;
	}

private:
	AssetsFactory();
};