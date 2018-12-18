//
//  LetterPageMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/28.
//
//

#include "LetterPageMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

LetterPageMsg::LetterPageMsg()
{
    
}
LetterPageMsg::~LetterPageMsg()
{
    
}
ByteStream *LetterPageMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_BOOK_BookPage2Req);
    SetMessageLength();
}