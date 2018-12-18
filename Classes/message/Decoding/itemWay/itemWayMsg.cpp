//
//  itemWayMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/10.
//
//

#include "itemWayMsg.h"
#include "../../../commonData/GlobalInfo.h"

itemWayMsg::itemWayMsg(int itemType,int itemId,int itemQuality)
:_itemType(itemType)
,_itemId(itemId)
,_itemQuality(itemQuality)
{
    
}
itemWayMsg::~itemWayMsg()
{
    
}
ByteStream *itemWayMsg::encodingData()
{
  
     MessageSendI::encodingData(SCENSE_CLIENT_ITEM_ItemWayReq);
    headBufferee->put(_itemType);
    headBufferee->putInt(_itemId);
    headBufferee->put(_itemQuality);
    SetMessageLength();
}