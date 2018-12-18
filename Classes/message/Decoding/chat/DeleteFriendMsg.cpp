//
//  DeleteFriendMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/22.
//
//

#include "DeleteFriendMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
DeleteFriendMsg::DeleteFriendMsg(long id)
:userId(id)
{
    
}
DeleteFriendMsg::~DeleteFriendMsg()
{
    
}
ByteStream *DeleteFriendMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendDelReq);
    headBufferee->putLong(userId);
    SetMessageLength();
}