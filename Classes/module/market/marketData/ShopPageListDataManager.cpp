//
//  ShopPageListDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/8.
//
//

#include "ShopPageListDataManager.h"
ShopPageListDataManager* ShopPageListDataManager::_instance = NULL;

ShopPageListDataManager::ShopPageListDataManager()
:shopList(NULL)
{
    shopList=new Vector<ShopPageListData*>();
    
}
ShopPageListDataManager::~ShopPageListDataManager()
{
    shopList->clear();
    CC_SAFE_DELETE(shopList);
    shopList = NULL;
}
ShopPageListDataManager* ShopPageListDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ShopPageListDataManager();
    }
    return _instance;
}
void ShopPageListDataManager::addData(ShopPageListData* data)
{
    shopList->pushBack(data);
}
void ShopPageListDataManager::clearshopList()
{
    this->shopList->clear();
}
void ShopPageListDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}