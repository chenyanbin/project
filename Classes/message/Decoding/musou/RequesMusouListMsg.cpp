//
//  RequesMusouListMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#include "RequesMusouListMsg.h"
RequesMusouListMsg::RequesMusouListMsg()
{
    
}
RequesMusouListMsg::~RequesMusouListMsg()
{
    
}
ByteStream* RequesMusouListMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MUSOU_MusouPageReq);
    SetMessageLength();

}