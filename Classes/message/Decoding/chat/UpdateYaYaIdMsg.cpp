//
//  UpdateYaYaIdMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 16/1/7.
//
//

#include "UpdateYaYaIdMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
UpdateYaYaIdMsg::UpdateYaYaIdMsg(int id)
:userId(id)
{
    
}
UpdateYaYaIdMsg::~UpdateYaYaIdMsg()
{
    
}
ByteStream *UpdateYaYaIdMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendUpdateYaYaIdReq);
    headBufferee->putInt(userId);
    SetMessageLength();
}