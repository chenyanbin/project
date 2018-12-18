//
//  RequestRandName.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#include "RequestRandName.hpp"
RequestRandName::RequestRandName(int sex)
:m_sex(sex)
{
    
}
RequestRandName::~RequestRandName()
{
    
}
ByteStream* RequestRandName::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_RandomRoleNameReq);
    headBufferee->put(m_sex);
    SetMessageLength();
}