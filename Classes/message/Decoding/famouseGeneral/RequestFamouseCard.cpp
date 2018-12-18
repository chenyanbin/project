//
//  RequestFamouseCard.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/2/1.
//
//

#include "RequestFamouseCard.hpp"
RequestFamouseCard::RequestFamouseCard()
{
    
}
RequestFamouseCard::~RequestFamouseCard()
{
    
}
ByteStream *RequestFamouseCard::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendRestoreAttackCountPageReq);
      SetMessageLength();
}