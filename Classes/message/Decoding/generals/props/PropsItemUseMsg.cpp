//
//  PropsItemUseMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/24.
//
//

#include "PropsItemUseMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
PropsItemUseMsg::PropsItemUseMsg(int itemId)
:_itemId(itemId)
{
    
}
PropsItemUseMsg::~PropsItemUseMsg()
{
    
}
ByteStream *PropsItemUseMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_ITEM_ItemUseReq);
    headBufferee->putInt(_itemId);
    SetMessageLength();
}