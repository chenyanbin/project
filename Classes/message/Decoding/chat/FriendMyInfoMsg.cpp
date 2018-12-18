//
//  FriendMyInfoMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 16/1/7.
//
//

#include "FriendMyInfoMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
FriendMyInfoMsg::FriendMyInfoMsg()
{
    
}
FriendMyInfoMsg::~FriendMyInfoMsg()
{
    
}
ByteStream *FriendMyInfoMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendMyInfoPageReq);
    SetMessageLength();
}