//
//  FamouseStatsMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#include "FamouseStatsMsg.hpp"
FamouseStatsMsg::FamouseStatsMsg()
{
    
}
FamouseStatsMsg::~FamouseStatsMsg()
{
    
}
ByteStream *FamouseStatsMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendHistoryPageReq);
    SetMessageLength();
}