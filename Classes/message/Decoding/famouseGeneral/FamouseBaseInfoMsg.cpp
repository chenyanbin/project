//
//  FamouseBaseInfoMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#include "FamouseBaseInfoMsg.hpp"
FamouseBaseInfoMsg::FamouseBaseInfoMsg()
{
    
}
FamouseBaseInfoMsg::~FamouseBaseInfoMsg()
{
    
}
ByteStream* FamouseBaseInfoMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendBaseInfoReq);
    SetMessageLength();
}