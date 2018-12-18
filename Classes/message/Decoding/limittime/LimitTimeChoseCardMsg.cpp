//
//  LimitTimeChoseCardMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/19.
//
//

#include "LimitTimeChoseCardMsg.hpp"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
LimitTimeChoseCardMsg::LimitTimeChoseCardMsg(int _cardType)
:m_cardType(_cardType)
{
    
}
LimitTimeChoseCardMsg::~ LimitTimeChoseCardMsg()
{
    
}
ByteStream *LimitTimeChoseCardMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendLeadReq);
    headBufferee->put(m_cardType);
    SetMessageLength();
}