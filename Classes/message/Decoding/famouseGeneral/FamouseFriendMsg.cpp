//
//  FamouseFriendMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/29.
//
//

#include "FamouseFriendMsg.hpp"
FamouseFriendMsg::FamouseFriendMsg()
{
    
}
FamouseFriendMsg::~FamouseFriendMsg()
{
    
}
ByteStream *FamouseFriendMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendMyFriendPageReq);
   
    SetMessageLength();
}