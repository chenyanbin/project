//
//  MaterPageMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/9.
//
//

#include "MaterPageMsg.h"
#include "../../../../commonData/GlobalInfo.h"

MaterPageMsg::MaterPageMsg()
{
    
}
MaterPageMsg::~MaterPageMsg()
{
    
}
ByteStream *MaterPageMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_MATER_MaterPageReq);
    SetMessageLength();
}