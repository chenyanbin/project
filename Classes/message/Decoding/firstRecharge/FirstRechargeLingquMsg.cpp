//
//  FirstRechargeLingquMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/19.
//
//

#include "FirstRechargeLingquMsg.h"
FirstRechargeLingquMsg::FirstRechargeLingquMsg()
{
    
}
FirstRechargeLingquMsg::~ FirstRechargeLingquMsg()
{
    
}
ByteStream* FirstRechargeLingquMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_FIRSTCHARGE_FirstChargeReceiveReq);
    //    headBufferee->put(m_function);
    
    SetMessageLength();
}