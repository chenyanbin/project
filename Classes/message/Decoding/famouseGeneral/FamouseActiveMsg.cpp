//
//  FamouseActiveMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#include "FamouseActiveMsg.hpp"
FamouseActiveMsg::FamouseActiveMsg()
{
    
}
FamouseActiveMsg::~FamouseActiveMsg()
{
    
}
ByteStream *FamouseActiveMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendActivityPageReq);
    SetMessageLength();
}