//
//  LetterDeliverMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/28.
//
//

#include "LetterDeliverMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
LetterDeliverMsg::LetterDeliverMsg(int letterId)
:_id(letterId)
{
    
}
LetterDeliverMsg::~LetterDeliverMsg()
{
    
}
ByteStream *LetterDeliverMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_BOOK_BookDeliverReq);
    headBufferee->putInt(_id);
    SetMessageLength();
}