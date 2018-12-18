//
//  EnvironmentMonsterDeadMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/9.
//
//

#include "EnvironmentMonsterDeadMsg.h"
EnvironmentMonsterDeadMsg::EnvironmentMonsterDeadMsg(int monnsterID)
:m_monsterID(monnsterID)
{
    
}
EnvironmentMonsterDeadMsg::~EnvironmentMonsterDeadMsg()
{
    
}
ByteStream* EnvironmentMonsterDeadMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_BattleLootReq);
    headBufferee->putInt(m_monsterID);
    
    SetMessageLength();
}