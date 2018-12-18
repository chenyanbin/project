  //
//  VipBlackShopManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
//

#include "VipBlackShopManager.h"
VipBlackShopManager* VipBlackShopManager::_instance = NULL;

VipBlackShopManager::VipBlackShopManager()
:bsList(NULL)
{
    bsList=new Vector<VipBlackshopData*>();
    
}
VipBlackShopManager::~VipBlackShopManager()
{
    bsList->clear();
    CC_SAFE_DELETE(bsList);
    bsList = NULL;
}
VipBlackShopManager* VipBlackShopManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new VipBlackShopManager();
    }
    return _instance;
}
void VipBlackShopManager::addData(VipBlackshopData* data)
{
    bsList->pushBack(data);
}
void VipBlackShopManager::clearblackshopList()
{
    this->bsList->clear();
}
void VipBlackShopManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}