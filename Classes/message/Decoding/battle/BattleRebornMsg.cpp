//
//  BattleRebornMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/22.
//
//

#include "BattleRebornMsg.h"
BattleRebornMsg::BattleRebornMsg(int count)
:m_count(count)
{
    
}
BattleRebornMsg::~BattleRebornMsg()
{
    
}
ByteStream* BattleRebornMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_RebornReq);
    headBufferee->put(m_count);

    SetMessageLength();
}