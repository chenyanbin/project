//
//  LetterGiftMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/28.
//
//

#include "LetterGiftMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
LetterGiftMsg::LetterGiftMsg(int letterId)
:_id(letterId)
{
    
}
LetterGiftMsg::~LetterGiftMsg()
{
    
}
ByteStream *LetterGiftMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_BOOK_BookGiftReq);
    headBufferee->putInt(_id);
    SetMessageLength();
}