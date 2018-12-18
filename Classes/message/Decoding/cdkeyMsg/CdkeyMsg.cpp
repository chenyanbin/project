//
//  CdkeyMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/19.
//
//

#include "CdkeyMsg.h"
#include "../../../common/Dialog/Dialog.h"
CdkeyMsg::CdkeyMsg(string str)
:m_str(str)
{
    
}
CdkeyMsg::~CdkeyMsg()
{
    
}
ByteStream* CdkeyMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_CDKEY_CdkeyEnterReq);
    headBufferee->putUTF8(m_str.c_str());
    SetMessageLength();
}