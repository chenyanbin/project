//
//  RequestEndStageBattle.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/18.
//
//

#include "RequestEndStageBattle.h"
#include "../../../commonData/GlobalInfo.h"
RequestEndStageBattle::RequestEndStageBattle(int battleID,bool isSuc,int star,int bloodBottle)
:m_battleID(battleID)
,m_isSuc(isSuc)
,m_starCount(star)
,m_bloodBottle(bloodBottle)
{
    
}
RequestEndStageBattle::~RequestEndStageBattle()
{
    
}
ByteStream * RequestEndStageBattle::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_EndBattleReq);
    
    headBufferee->put(GlobalInfo::getInstance()->stageMode);
    headBufferee->putInt(m_battleID);
    headBufferee->put(m_isSuc);
    headBufferee->put(m_starCount);
    headBufferee->putInt(m_bloodBottle);
    SetMessageLength();
}