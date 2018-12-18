//
//  RequestFamouseRewardMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/28.
//
//

#include "RequestFamouseRewardMsg.hpp"
RequestFamouseRewardMsg::RequestFamouseRewardMsg(int bossID)
:m_bossID(bossID)
{
    
}
RequestFamouseRewardMsg::~RequestFamouseRewardMsg()
{
    
}
ByteStream *RequestFamouseRewardMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendRewardPageReq);
    headBufferee->putInt(m_bossID);
    SetMessageLength();
}