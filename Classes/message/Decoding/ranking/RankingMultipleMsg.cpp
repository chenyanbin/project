//
//  RankingMultipleMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#include "RankingMultipleMsg.hpp"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
RankingMultipleMsg::RankingMultipleMsg()
{
    
}
RankingMultipleMsg::~ RankingMultipleMsg()
{
    
}
ByteStream *RankingMultipleMsg::encodingData()
{
//    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendRankFinalPageReq);
    SetMessageLength();
}