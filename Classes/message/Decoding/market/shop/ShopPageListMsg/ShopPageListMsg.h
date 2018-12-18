//
//  ShopPageListMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#ifndef __FightPass__ShopPageListMsg__
#define __FightPass__ShopPageListMsg__

#include "../../../MessageSendI.h"
class ShopPageListMsg:public MessageSendI
{
public:
    ShopPageListMsg();
    ~ShopPageListMsg();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__ShopPageListMsg__) */
