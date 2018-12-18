//
//  MaterComposeMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/9.
//
//

#include "MaterComposeMsg.h"
#include "../../../../commonData/GlobalInfo.h"

MaterComposeMsg::MaterComposeMsg(int materId)
:_materId(materId)
{
    
}
MaterComposeMsg::~MaterComposeMsg()
{
    
}
ByteStream *MaterComposeMsg::encodingData()
{
  
    MessageSendI::encodingData(SCENSE_CLIENT_MATER_MaterComposeReq);
    headBufferee->putInt(_materId);
    SetMessageLength();
}