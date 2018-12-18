//
//  RequestProgressPrize.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/30.
//领取日常任务进度奖励
//

#ifndef RequestProgressPrize_hpp
#define RequestProgressPrize_hpp

#include "../MessageSendI.h"
class RequestProgressPrize:public MessageSendI
{
public:
    RequestProgressPrize(int progressID);
    ~RequestProgressPrize();
    ByteStream *encodingData();
private:
    int m_progressID;
};

#endif /* RequestProgressPrize_hpp */
