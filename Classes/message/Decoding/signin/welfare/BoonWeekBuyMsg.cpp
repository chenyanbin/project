//
//  BoonWeekBuyMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/4.
//
//

#include "BoonWeekBuyMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
BoonWeekBuyMsg::BoonWeekBuyMsg(int _vip)
:m_vip(_vip)
{
    
}
BoonWeekBuyMsg::~BoonWeekBuyMsg()
{
    
}
ByteStream *BoonWeekBuyMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_BOON_BoonWeekBuyReq);
    headBufferee->put(m_vip);
    SetMessageLength();
}