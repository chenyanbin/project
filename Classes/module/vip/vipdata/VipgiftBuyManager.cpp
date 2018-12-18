//
//  VipgiftBuyManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#include "VipgiftBuyManager.h"
VipgiftBuyManager* VipgiftBuyManager::_instance = NULL;

VipgiftBuyManager::VipgiftBuyManager()
:buylist(NULL)
{
    buylist=new Vector<VipGiftBuyData*>();
    
}
VipgiftBuyManager::~VipgiftBuyManager()
{
    buylist->clear();
    CC_SAFE_DELETE(buylist);
    buylist = NULL;
}
VipgiftBuyManager* VipgiftBuyManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new VipgiftBuyManager();
    }
    return _instance;
}
void VipgiftBuyManager::addData(VipGiftBuyData* data)
{
    buylist->pushBack(data);
}
void VipgiftBuyManager::clearbuyList()
{
    this->buylist->clear();
}
void VipgiftBuyManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}