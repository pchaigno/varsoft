#pragma once

#include <string>
#include "Asset.h"

using namespace std;

class AssetsFactory {
private:
	static AssetsFactory* instance;

public:
	Asset* retrieveAsset(string name);
	static AssetsFactory* getInstance() {
		if(instance == NULL) {
			instance = new AssetsFactory();
		}
		return instance;
	}

private:
	AssetsFactory();
};