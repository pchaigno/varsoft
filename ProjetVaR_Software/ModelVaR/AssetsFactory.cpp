#include "AssetsFactory.h"

/**
 * @brief Singleton definition. Mandatory.
 */
AssetsFactory* AssetsFactory::instance = NULL;

/**
 * @brief Private constructor.
 */
AssetsFactory::AssetsFactory() {
    this->assets = SessionBuilder::getInstance()->buildAssets();
}

/**
 * @brief Retrieves an asset by its name.
 * @param name The name of the asset to retrieve.
 * @return A pointer to the asset.
 */
Asset* AssetsFactory::retrieveAsset(QString name) {
    if(!this->assets.contains(name)) {
        this->assets[name] = SessionBuilder::getInstance()->buildAsset(name);
    }
    return this->assets[name];
}