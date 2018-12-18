//
//  RequestAwakePageMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/4/7.
//
//

#include "RequestAwakePageMsg.hpp"
RequestAwakePageMsg::RequestAwakePageMsg(int cardId)
:m_heroID(cardId)
{
    
}
RequestAwakePageMsg::~RequestAwakePageMsg()
{
    
}
ByteStream *RequestAwakePageMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroWakeUpPage2Req);
    headBufferee->putInt(m_heroID);
    SetMessageLength();
}