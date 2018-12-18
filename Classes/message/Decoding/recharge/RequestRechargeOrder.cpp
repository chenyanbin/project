//
//  RequestRechargeOrder.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/16.
//
//

#include "RequestRechargeOrder.h"
#include "../../../sdk/SdkManager.h"
RequestRechargeOrder::RequestRechargeOrder(int chargeType,int goldPackID,int cardId,int userMoney)
:_chargeType(chargeType)
,_goldPackID(goldPackID)
,_cardID(cardId)
,_userMoney(userMoney)
{
    
}
RequestRechargeOrder::~RequestRechargeOrder()
{
    
}
ByteStream *RequestRechargeOrder::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_PAY_Sdk1PayCreateOrderReq);
    headBufferee->put(_chargeType);
    headBufferee->put(_goldPackID);
    headBufferee->put(_cardID);
    headBufferee->putInt(_userMoney);
    headBufferee->putUTF8(SdkManager::getInstance()->channel.c_str());
    log("SdkManager::getInstance()->channelName==%s",SdkManager::getInstance()->channelName.c_str());
    headBufferee->putUTF8(SdkManager::getInstance()->channelName.c_str());
    SetMessageLength();
}