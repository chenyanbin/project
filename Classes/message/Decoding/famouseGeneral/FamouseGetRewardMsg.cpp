//
//  FamouseGetRewardMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/29.
//
//

#include "FamouseGetRewardMsg.hpp"
FamouseGetRewardMsg::FamouseGetRewardMsg(int bossID)
:m_bossID(bossID)
{
    
}
FamouseGetRewardMsg::~FamouseGetRewardMsg()
{
    
}
ByteStream *FamouseGetRewardMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendRewardReq);
    headBufferee->putInt(m_bossID);
    SetMessageLength();
}