//
//  RecruitHeroMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#include "RecruitHeroMsg.hpp"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
RecruitHeroMsg::RecruitHeroMsg()
{
    
}
RecruitHeroMsg::~ RecruitHeroMsg()
{
    
}
ByteStream *RecruitHeroMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendHeadIconSelPageReq);
    SetMessageLength();
}