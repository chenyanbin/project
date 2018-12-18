//
//  RequestHeroAwakeMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/4/7.
//
//

#include "RequestHeroAwakeMsg.hpp"
RequestHeroAwakeMsg::RequestHeroAwakeMsg(int cardId)
:m_heroID(cardId)
{
    
}
RequestHeroAwakeMsg::~RequestHeroAwakeMsg()
{
    
}
ByteStream *RequestHeroAwakeMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroWakeUp2Req);
    headBufferee->putInt(m_heroID);
    SetMessageLength();
}