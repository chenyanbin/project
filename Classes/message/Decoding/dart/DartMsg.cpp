//
//  DartMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/13.
//
//

#include "DartMsg.hpp"
DartMsg::DartMsg()
{
    
}
DartMsg::~ DartMsg()
{
    
}
ByteStream *DartMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_Gemstone_GemstoneGrabReq);
    SetMessageLength();
}