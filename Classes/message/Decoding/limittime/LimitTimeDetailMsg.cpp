//
//  LimitTimeDetailMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/19.
//
//

#include "LimitTimeDetailMsg.hpp"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
LimitTimeDetailMsg::LimitTimeDetailMsg()
{
    
}
LimitTimeDetailMsg::~ LimitTimeDetailMsg()
{
    
}
ByteStream *LimitTimeDetailMsg::encodingData()
{
//    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendLeadPageReq);
    SetMessageLength();
}