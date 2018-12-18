//
//  FamouseShareFriendMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/29.
//
//

#include "FamouseShareFriendMsg.hpp"
FamouseShareFriendMsg::FamouseShareFriendMsg(int bossID,vector<long>* friendList)
:m_bossID(bossID)
,m_frindList(friendList)
{
    
}
FamouseShareFriendMsg::~FamouseShareFriendMsg()
{
    m_frindList = NULL;
}
ByteStream *FamouseShareFriendMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendShareBossReq);
    headBufferee->putInt(m_bossID);
    short size = m_frindList->size();
    headBufferee->put(size);
    for(short i = 0; i < size ; i++)
    {
        headBufferee->putLong(m_frindList->at(i));
    }
    
    SetMessageLength();
}