//
//  SellHeroMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#include "SellHeroMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
SellHeroMsg::SellHeroMsg(Vector<CardPropertyData*> *list)
:cardList(list)
{
    
}
SellHeroMsg::~SellHeroMsg()
{
    CC_SAFE_DELETE(cardList);
    cardList=NULL;
}
ByteStream *SellHeroMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroSellReq);
    int size=(int)cardList->size();
    headBufferee->putShort(size);
    for (int i=0; i<size; i++) {
        headBufferee->putInt(cardList->at(i)->heroId);
    }
    SetMessageLength();
}