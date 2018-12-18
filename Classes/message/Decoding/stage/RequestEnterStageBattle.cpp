//
//  RequestEnterStageBattle.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/18.
//
//

#include "RequestEnterStageBattle.h"
#include "../../../commonData/GlobalInfo.h"
RequestEnterStageBattle::RequestEnterStageBattle(int battleID)
:m_battleID(battleID)
{
    if(m_battleID == 0)
    {
        log("RequestEnterStageBattle RequestEnterStageBattle ====0");
    }
}
RequestEnterStageBattle::~RequestEnterStageBattle()
{
    
}
ByteStream * RequestEnterStageBattle::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_StartBattleReq);
    
    
    headBufferee->put(GlobalInfo::getInstance()->stageMode);
    headBufferee->putInt(m_battleID);
    
    
    SetMessageLength();
}