//
//  TDTalkDataManager.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/4.
//
//

#ifndef TDTalkDataManager_hpp
#define TDTalkDataManager_hpp

#include "cocos2d.h"
#include "TDCCTalkingDataGA.h"
#include "TDCCAccount.h"

class TDTalkDataManager
{
public:
     static TDTalkDataManager* getInstance();
private:
    TDTalkDataManager();
    ~TDTalkDataManager();
    
public:
    void start();
    void setAnncordID();
    void setAccountName();
    void setLevel();
    void setGameServer();
    void setSex();
    void setAccountType();
    /////////充值相关////////////////////////
    void onChargeRequest(const char* orderID,const char* itemName,int money,const char* currencyType,int virtualMoney,const char* paymentType);
    void onChargeSuc(const char* orderID);
    void onChargeFailed(const char* orderID);
    //赠予的货币
    void onReward(double coin,const char* reson);
    //购买了几个道具
    void onPurchase(const char* itemName,int count,int unitPrice);
    //哪几物品消失了
     void onUse(const char* itemName,int count);
    
    //////////////////任务，关卡，副本//////////////////////
    void onMissionBegain(const char* messionID);
    void onMissionCompleted(const char* messionID);
    void onMissionFailed(const char* messionID);
private:
    static TDTalkDataManager* _instance;
    TDCCAccount* mTDGAaccount;
     std::string m_orderID;
};

#endif /* TDTalkDataManager_hpp */
