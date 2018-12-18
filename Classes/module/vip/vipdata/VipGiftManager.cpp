//
//  VipGiftManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#include "VipGiftManager.h"
VipGiftManager* VipGiftManager::_instance = NULL;

VipGiftManager::VipGiftManager()
:giftList(NULL)
{
    giftList=new Vector<VipGiltData*>();
    
}
VipGiftManager::~VipGiftManager()
{
    giftList->clear();
    CC_SAFE_DELETE(giftList);
    giftList = NULL;
}
VipGiftManager* VipGiftManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new VipGiftManager();
    }
    return _instance;
}
void VipGiftManager::addData(VipGiltData* data)
{
    giftList->pushBack(data);
}
void VipGiftManager::cleargiltList()
{
    this->giftList->clear();
}
void VipGiftManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}