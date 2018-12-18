//
//  SigninDayGetMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/9.
//
//

#include "SigninDayGetMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
SigninDayGetMsg::SigninDayGetMsg(int day)
:_day(day)
{
    
}
SigninDayGetMsg::~SigninDayGetMsg()
{
    
}
ByteStream *SigninDayGetMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_SIGNDAY_SignDaySignReq);
    headBufferee->put(_day);
    SetMessageLength();
}