//
//  FamouseStatsMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//名将传 统计页数据
//

#ifndef FamouseStatsMsg_hpp
#define FamouseStatsMsg_hpp

#include "../MessageSendI.h"
class FamouseStatsMsg:public MessageSendI
{
public:
    FamouseStatsMsg();
    ~FamouseStatsMsg();
    ByteStream *encodingData();
};

#endif /* FamouseStatsMsg_hpp */
