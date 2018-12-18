//
//  ChatMyInfoMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/14.
//
//

#include "ChatFriendsListMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
ChatFriendsListMsg::ChatFriendsListMsg()
{
    
}
ChatFriendsListMsg::~ChatFriendsListMsg()
{
    
}
ByteStream *ChatFriendsListMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendMyPageReq);
    SetMessageLength();
}