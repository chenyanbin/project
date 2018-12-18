//
//  SendNewGuideMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/28.
//
//

#include "SendNewGuideMsg.h"
SendNewGuideMsg::SendNewGuideMsg(int functionID,int _step)
:m_function(functionID)
,m_step(_step)
{
    
}
SendNewGuideMsg::~SendNewGuideMsg()
{
    
}
ByteStream* SendNewGuideMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_NewGuidePassReq);
    headBufferee->put(m_function);
    headBufferee->put(m_step);
    SetMessageLength();
}