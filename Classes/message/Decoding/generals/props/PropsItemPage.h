//
//  PropsItemPage.h
//  FightPass
//
//  Created by 超 顾 on 15/9/23.
//
//

#ifndef __FightPass__PropsItemPage__
#define __FightPass__PropsItemPage__

#include "../../MessageSendI.h"
class PropsItemPage:public MessageSendI
{
public:
    PropsItemPage();
    ~PropsItemPage();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__PropsItemPage__) */
