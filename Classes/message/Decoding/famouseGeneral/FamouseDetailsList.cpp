//
//  FamouseDetailsList.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/25.
//
//

#include "FamouseDetailsList.hpp"
FamouseDetailsList::FamouseDetailsList()
{
    
}
FamouseDetailsList::~FamouseDetailsList()
{
    
}
ByteStream *FamouseDetailsList::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendBossCompletePageReq);
    SetMessageLength();
}