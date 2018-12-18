//
//  FriendHeadIconSelPage.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/28.
//
//

#include "FriendHeadIconSelPage.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
FriendHeadIconSelPage::FriendHeadIconSelPage()
{
    
}
FriendHeadIconSelPage::~FriendHeadIconSelPage()
{
    
}
ByteStream *FriendHeadIconSelPage::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendHeadIconSelPageReq);
    SetMessageLength();
}