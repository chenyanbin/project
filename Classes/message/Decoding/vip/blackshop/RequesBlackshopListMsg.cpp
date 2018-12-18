//
//  RequesBlackshopListMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
//

#include "RequesBlackshopListMsg.h"
RequesBlackshopListMsg::RequesBlackshopListMsg(int refresh, int free)
:m_refresh(refresh)
,m_free(free)
{
    
}
RequesBlackshopListMsg::~RequesBlackshopListMsg()
{
    
}
ByteStream* RequesBlackshopListMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BLACK_BlackPageReq);
    headBufferee->put(m_refresh);
    headBufferee->put(m_free);
    SetMessageLength();
}