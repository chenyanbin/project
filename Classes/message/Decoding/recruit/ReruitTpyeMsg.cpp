//
//  ReruitTpyeMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#include "ReruitTpyeMsg.hpp"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
ReruitTpyeMsg::ReruitTpyeMsg(int _countMode)
:m_countMode(_countMode)
{
    
}
ReruitTpyeMsg::~ ReruitTpyeMsg()
{
    
}
ByteStream *ReruitTpyeMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_FRIEND_FriendHeadIconSelPageReq);
    headBufferee->put(m_countMode);
    SetMessageLength();
}