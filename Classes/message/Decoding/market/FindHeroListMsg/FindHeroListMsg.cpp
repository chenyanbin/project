//
//  FindHeroListMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#include "FindHeroListMsg.h"
#include "../../../../commonData/GlobalInfo.h"

FindHeroListMsg:: FindHeroListMsg()
{
    
}
FindHeroListMsg::~ FindHeroListMsg()
{
    
}
ByteStream * FindHeroListMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_FIND_FindHeroSelPageReq);
    SetMessageLength();
}