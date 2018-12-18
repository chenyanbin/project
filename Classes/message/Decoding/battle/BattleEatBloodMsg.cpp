//
//  BattleEatBloodMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/22.
//
//

#include "BattleEatBloodMsg.h"
BattleEatBloodMsg::BattleEatBloodMsg(int count)
:m_count(count)
{
    
}
BattleEatBloodMsg::~BattleEatBloodMsg()
{
    
}
ByteStream *BattleEatBloodMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_PotionReq);
    headBufferee->put(m_count);
    
    SetMessageLength();
}