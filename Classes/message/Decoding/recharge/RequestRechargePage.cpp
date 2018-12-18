//
//  RequestRechargePage.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/26.
//
//

#include "RequestRechargePage.h"
RequestRechargePage::RequestRechargePage()
{
    
}
RequestRechargePage::~RequestRechargePage()
{
    
}
ByteStream * RequestRechargePage::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_PAY_PayPageReq);
   
    SetMessageLength();
}