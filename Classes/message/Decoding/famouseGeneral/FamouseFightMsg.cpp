//
//  FamouseFightMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#include "FamouseFightMsg.hpp"
FamouseFightMsg::FamouseFightMsg(int bossID)
:m_bossId(bossID)
{
    
}
FamouseFightMsg::~FamouseFightMsg()
{
    
}
ByteStream* FamouseFightMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendStartBattleReq);
    headBufferee->putInt(m_bossId);
    SetMessageLength();
}