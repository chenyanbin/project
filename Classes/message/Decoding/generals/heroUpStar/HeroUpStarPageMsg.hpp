//
//  HeroUpStarMsg.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/31.
//武将升星页
//

#ifndef HeroUpStarPageMsg_hpp
#define HeroUpStarPageMsg_hpp

#include "../../MessageSendI.h"
class HeroUpStarPageMsg:public MessageSendI
{
public:
    HeroUpStarPageMsg(int heroID);
    ~HeroUpStarPageMsg();
    ByteStream *encodingData();
private:
    int m_heroID;
};

#endif /* HeroUpStarPageMsg_hpp */
