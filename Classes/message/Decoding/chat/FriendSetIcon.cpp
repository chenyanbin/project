//
//  FriendSetIcon.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/28.
//
//

#include "FriendSetIcon.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
FriendSetIcon::FriendSetIcon(int id)
:heroDictId(id)
{
    
}
FriendSetIcon::~FriendSetIcon()
{
    
}
ByteStream *FriendSetIcon::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendSetIconReq);
    headBufferee->putInt(heroDictId);
    SetMessageLength();
}