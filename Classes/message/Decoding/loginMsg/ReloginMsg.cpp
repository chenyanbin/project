//
//  ReloginMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/25.
//
//

#include "ReloginMsg.hpp"
#include "../../../commonData/GlobalInfo.h"
ReloginMsg::ReloginMsg()
{
    
}
ReloginMsg::~ReloginMsg()
{
    
}
ByteStream *ReloginMsg::encodingData()
{
    MessageSendI::encodingData(SCENE_CLIENT_LOGIN_UP);
    headBufferee->putUTF8(GlobalInfo::getInstance()->sessionID.c_str());
    headBufferee->putUTF8(GlobalInfo::getInstance()->gameSessionId.c_str());
    SetMessageLength();
}