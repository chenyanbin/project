//
//  FriendAgreeMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/24.
//
//

#include "FriendAgreeMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
FriendAgreeMsg::FriendAgreeMsg(long id)
:userId(id)
{
    
}
FriendAgreeMsg::~FriendAgreeMsg()
{
    
}
ByteStream *FriendAgreeMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendAddAgreeReq);
    headBufferee->putLong(userId);
    SetMessageLength();
}