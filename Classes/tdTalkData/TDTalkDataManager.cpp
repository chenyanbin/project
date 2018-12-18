//
//  TDTalkDataManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/4.
//
//

#include "TDTalkDataManager.hpp"
#include "../commonData/GlobalInfo.h"
#include "../sdk/SdkManager.h"
#include "../common/PublicShowUI.h"
#include "TDCCVirtualCurrency.h"
#include "TDCCMission.h"
#include "TDCCItem.h"
TDTalkDataManager* TDTalkDataManager::_instance = NULL;
TDTalkDataManager* TDTalkDataManager::getInstance()
{
    if(!_instance)
    {
        _instance = new TDTalkDataManager();
    }
    return _instance;
}
TDTalkDataManager::TDTalkDataManager()
{
//    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    mTDGAaccount = NULL;
//    #endif
    mTDGAaccount = NULL;
}
TDTalkDataManager::~TDTalkDataManager()
{
    _instance = NULL;
}
void TDTalkDataManager::start()
{
    log("applicationDidFinishLaunching DeviceId:%s", TDCCTalkingDataGA::getDeviceId());
     log("SdkManager::getInstance()->channel:%s", SdkManager::getInstance()->channel.c_str());
         log("SdkManager::getInstance()->channelName:%s", SdkManager::getInstance()->channelName.c_str());
     TDCCTalkingDataGA::onStart("BDDEC63C37DCDA2B8B636D40F8FBBDB9",  SdkManager::getInstance()->channelName.c_str());

}
void TDTalkDataManager::setAnncordID()
{
    string roleID = PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->roleID);

    log(" TDTalkDataManager setAnncordID :%s", roleID.c_str());
    mTDGAaccount = TDCCAccount::setAccount(roleID.c_str());

}
void TDTalkDataManager::setAccountName()
{

       if(mTDGAaccount)
       {
           mTDGAaccount->setAccountName(GlobalInfo::getInstance()->gameRole->name.c_str());
           log(" TDTalkDataManager setAccountName setAccountName");
       }
}
void TDTalkDataManager::setLevel()
{

    if(mTDGAaccount)  mTDGAaccount->setLevel(GlobalInfo::getInstance()->gameRole->level);
}
void TDTalkDataManager::setGameServer()
{

    if(mTDGAaccount)  mTDGAaccount->setGameServer(GlobalInfo::getInstance()->nowServerName.c_str());

}
void TDTalkDataManager::setSex()
{
    if (mTDGAaccount) mTDGAaccount->setGender(mTDGAaccount->kGenderUnknown);
   
}
void TDTalkDataManager::setAccountType()
{
    if (mTDGAaccount) mTDGAaccount->setAccountType(mTDGAaccount->kAccountAnonymous);
}

//购买了几个道具
void TDTalkDataManager::onPurchase(const char* itemName,int count,int unitPrice)
{
    TDCCItem::onPurchase(itemName, count, unitPrice);
}
//哪几物品消失了
void TDTalkDataManager::onUse(const char* itemName,int count)
{
     TDCCItem::onUse(itemName, count);
}
void TDTalkDataManager::onChargeRequest(const char* orderID,const char* itemName,int money,const char* currencyType,int virtualMoney,const char* paymentType)
{
    m_orderID = orderID;
    TDCCVirtualCurrency::onChargeRequest(orderID,itemName, money, "CN", virtualMoney , paymentType);
}
void TDTalkDataManager::onChargeSuc(const char* orderID)
{
     TDCCVirtualCurrency::onChargeSuccess(m_orderID.c_str());
}
void TDTalkDataManager::onChargeFailed(const char* orderID)
{
    //没有失败回调
}
void TDTalkDataManager::onReward(double coin,const char* reson)
{
    TDCCVirtualCurrency::onReward(coin, reson);
}

void TDTalkDataManager::onMissionBegain(const char* messionID)
{
    TDCCMission::onBegin(messionID);
}
void TDTalkDataManager::onMissionCompleted(const char* messionID)
{
    TDCCMission::onCompleted(messionID);
}
void TDTalkDataManager::onMissionFailed(const char* messionID)
{
    TDCCMission::onFailed(messionID, NULL);
}