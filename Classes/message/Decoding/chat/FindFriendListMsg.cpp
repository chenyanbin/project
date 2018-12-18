//
//  FindFriendListMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/22.
//
//

#include "FindFriendListMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
FindFriendListMsg::FindFriendListMsg(string name)
:userName(name)
{
    
}
FindFriendListMsg::~FindFriendListMsg()
{
    
}
ByteStream *FindFriendListMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendSearchRoleReq);
    headBufferee->putUTF8(userName.c_str());
    SetMessageLength();
}