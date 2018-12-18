//
//  ChatMyInfoMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/14.
//
//

#include "ChatMyInfoMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
ChatMyInfoMsg::ChatMyInfoMsg()
{
    
}
ChatMyInfoMsg::~ChatMyInfoMsg()
{
    
}
ByteStream *ChatMyInfoMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendMyPageReq);
    SetMessageLength();
}