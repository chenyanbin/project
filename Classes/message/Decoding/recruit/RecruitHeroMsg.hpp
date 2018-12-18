//
//  RecruitHeroMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#ifndef RecruitHeroMsg_hpp
#define RecruitHeroMsg_hpp

#include "../MessageSendI.h"
class RecruitHeroMsg:public MessageSendI
{
public:
    RecruitHeroMsg();
    ~ RecruitHeroMsg();
    ByteStream *encodingData();
};

#endif /* RecruitHeroMsg_hpp */
