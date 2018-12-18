//
//  LoginMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/21.
//
//

#include "LoginMsg.h"
#include "../../../commonData/GlobalInfo.h"

LoginMsg::LoginMsg()
{
    
}
LoginMsg::~LoginMsg()
{
    
}
ByteStream *LoginMsg::encodingData()
{

    MessageSendI::encodingData(SCENE_CLIENT_LOGIN_UP);
    headBufferee->putUTF8(GlobalInfo::getInstance()->sessionID.c_str());
    headBufferee->putUTF8("");
    SetMessageLength();
}