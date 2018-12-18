//
//  HeroAddExpMsg.hpp
//  FightPass
//
//  Created by zhangbin on 16/4/7.
//武将加经验，升级
//

#ifndef HeroAddExpMsg_hpp
#define HeroAddExpMsg_hpp

#include "../../MessageSendI.h"
class HeroAddExpMsg:public MessageSendI
{
public:
    HeroAddExpMsg(int heroID);
    ~HeroAddExpMsg();
    ByteStream *encodingData();
private:
    int m_heroID;
};

#endif /* HeroAddExpMsg_hpp */
