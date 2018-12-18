//
//  HeroUpStarMsg.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/31.
//
//

#ifndef HeroUpStarMsg_hpp
#define HeroUpStarMsg_hpp

#include "../../MessageSendI.h"
class HeroUpStarMsg:public MessageSendI
{
public:
    HeroUpStarMsg(int heroID);
    ~HeroUpStarMsg();
    ByteStream *encodingData();
private:
    int m_heroID;
};

#endif /* HeroUpStarMsg_hpp */
