//
//  FirstRechargeMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/19.
//
//

#include "FirstRechargeMsg.h"
FirstRechargeMsg::FirstRechargeMsg()
{
    
}
FirstRechargeMsg::~FirstRechargeMsg()
{
    
}
ByteStream* FirstRechargeMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_FIRSTCHARGE_FirstChargePageReq);
    //    headBufferee->put(m_function);
    
    SetMessageLength();
}