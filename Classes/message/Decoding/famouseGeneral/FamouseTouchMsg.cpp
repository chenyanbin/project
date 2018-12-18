//
//  FamouseTouchMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/25.
//
//

#include "FamouseTouchMsg.hpp"
FamouseTouchMsg::FamouseTouchMsg(int battleID)
:m_battleID(battleID)
{
    
}
FamouseTouchMsg::~FamouseTouchMsg()
{
    
}
ByteStream *FamouseTouchMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendTouchBossReq);
    headBufferee->putInt(m_battleID);
    SetMessageLength();
}