//
//  FamouseComeMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/25.
//
//

#include "FamouseComeMsg.hpp"
#include "../../../commonData/GlobalInfo.h"
FamouseComeMsg::FamouseComeMsg()
{
    
}
FamouseComeMsg::~FamouseComeMsg()
{
    
}
ByteStream *FamouseComeMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendBattlePageReq);
    headBufferee->putInt( GlobalInfo::getInstance()->famouseBossID);
    SetMessageLength();
}