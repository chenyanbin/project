//
//  RoleInfoMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/24.
//
//

#include "RoleInfoMsg.h"

RoleInfoMsg::RoleInfoMsg()
{
    
}
RoleInfoMsg::~RoleInfoMsg()
{
    
}
ByteStream *RoleInfoMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_RoleInfoReq);
  
    SetMessageLength();
}