//
//  FriendRefuseMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/24.
//
//

#include "FriendRefuseMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
FriendRefuseMsg::FriendRefuseMsg(long id)
:userId(id)
{
    
}
FriendRefuseMsg::~FriendRefuseMsg()
{
    
}
ByteStream *FriendRefuseMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendAddRefuseReq);
    headBufferee->putLong(userId);
    SetMessageLength();
}