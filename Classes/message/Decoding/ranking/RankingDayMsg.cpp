//
//  RankingDayMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#include "RankingDayMsg.hpp"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
RankingDayMsg::RankingDayMsg()
{
    
}
RankingDayMsg::~ RankingDayMsg()
{
    
}
ByteStream *RankingDayMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendRankTodayPageReq);
    SetMessageLength();
}