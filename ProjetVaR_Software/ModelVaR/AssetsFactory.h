#pragma once

#include <QString>
#include "Asset.h"
#include "SessionBuilder.h"

class AssetsFactory {
private:
	static AssetsFactory* instance;
	QMap<QString, Asset*> assets;

public:
	Asset* retrieveAsset(QString name);
	static AssetsFactory* getInstance() {
		if(instance == NULL) {
			instance = new AssetsFactory();
		}
		return instance;
	}

private:
	AssetsFactory();
};
