//
//  FriendApplyMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/22.
//
//

#include "FriendApplyMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
FriendApplyMsg::FriendApplyMsg()
{
    
}
FriendApplyMsg::~FriendApplyMsg()
{
    
}
ByteStream *FriendApplyMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendAddAskPageReq);
    SetMessageLength();
}