//
//  PropsItemUseMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/9/24.
//
//

#ifndef __FightPass__PropsItemUseMsg__
#define __FightPass__PropsItemUseMsg__

#include "../../MessageSendI.h"
class PropsItemUseMsg:public MessageSendI
{
public:
    PropsItemUseMsg(int itemId);
    ~PropsItemUseMsg();
    ByteStream *encodingData();
private:
    int _itemId;
    
};

#endif /* defined(__FightPass__PropsItemUseMsg__) */
