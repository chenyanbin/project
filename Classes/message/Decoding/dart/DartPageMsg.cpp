//
//  DartPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/13.
//
//

#include "DartPageMsg.hpp"
DartPageMsg::DartPageMsg()
{
    
}
DartPageMsg::~ DartPageMsg()
{
    
}
ByteStream *DartPageMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_Gemstone_GemstonePageReq);
    SetMessageLength();
}