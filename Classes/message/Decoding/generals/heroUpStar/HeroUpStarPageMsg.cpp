//
//  HeroUpStarMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/31.
//
//

#include "HeroUpStarPageMsg.hpp"
HeroUpStarPageMsg::HeroUpStarPageMsg(int heroId)
:m_heroID(heroId)
{
    
}
HeroUpStarPageMsg::~HeroUpStarPageMsg()
{
    
}
ByteStream *HeroUpStarPageMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroStarUpPageReq);
    headBufferee->putInt(m_heroID);
    SetMessageLength();
}