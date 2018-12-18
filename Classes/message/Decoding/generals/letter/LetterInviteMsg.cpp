//
//  LetterInviteMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/28.
//
//

#include "LetterInviteMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

LetterInviteMsg::LetterInviteMsg(int letterId)
:_id(letterId)
{
    
}
LetterInviteMsg::~LetterInviteMsg()
{
    
}
ByteStream *LetterInviteMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_BOOK_BookInvite2Req);
    headBufferee->putInt(_id);
    SetMessageLength();
}