//
//  AddFriendMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/22.
//
//

#include "AddFriendMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
AddFriendMsg::AddFriendMsg(long id)
:userId(id)
{
    
}
AddFriendMsg::~AddFriendMsg()
{
    
}
ByteStream *AddFriendMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendAddReq);
    headBufferee->putLong(userId);
    SetMessageLength();
}