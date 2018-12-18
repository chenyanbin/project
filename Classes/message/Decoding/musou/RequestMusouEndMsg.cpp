//
//  RequestMusouEndMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#include "RequestMusouEndMsg.h"

RequestMusouEndMsg::RequestMusouEndMsg(int battleID,bool isSuc,int star,int bloodBottle)
:m_battleID(battleID)
,m_isSuc(isSuc)
,m_starCount(star)
,m_bloodBottle(bloodBottle)
{
    
}
RequestMusouEndMsg::~RequestMusouEndMsg()
{
    
}
ByteStream * RequestMusouEndMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MUSOU_MusouEndBattleReq);
    
    headBufferee->putInt(m_battleID);
    headBufferee->put(m_isSuc);
    headBufferee->put(m_starCount);
    headBufferee->putInt(m_bloodBottle);
    SetMessageLength();
}