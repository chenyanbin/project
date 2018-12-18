//
//  SellHeroMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#ifndef __FightPass__SellHeroMsg__
#define __FightPass__SellHeroMsg__
#include "../../../../module/generals/data/CardDataManager.h"
#include "../../MessageSendI.h"
class SellHeroMsg:public MessageSendI
{
public:
    SellHeroMsg(Vector<CardPropertyData*> *list);
    ~SellHeroMsg();
    ByteStream *encodingData();
private:
    Vector<CardPropertyData*> *cardList;
};

#endif /* defined(__FightPass__SellHeroMsg__) */
