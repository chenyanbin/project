//
//  FamouseBossListMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#include "FamouseBossListMsg.hpp"
FamouseBossListMsg::FamouseBossListMsg()
{
    
}
FamouseBossListMsg::~FamouseBossListMsg()
{
    
}
ByteStream* FamouseBossListMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendBossPageReq);
    SetMessageLength();
}