//
//  FamouseGetRewardMsg.hpp
//  FightPass
//详情页领取奖励
//  Created by zhangxiaobin on 16/1/29.
//
//

#ifndef FamouseGetRewardMsg_hpp
#define FamouseGetRewardMsg_hpp

#include "../MessageSendI.h"
class FamouseGetRewardMsg:public MessageSendI
{
public:
    FamouseGetRewardMsg(int bossID);
    ~FamouseGetRewardMsg();
    ByteStream *encodingData();
    
private:
    int m_bossID;
};

#endif /* FamouseGetRewardMsg_hpp */
