//
//  RequestFamouseRewardMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/28.
//
//

#ifndef RequestFamouseRewardMsg_hpp
#define RequestFamouseRewardMsg_hpp

#include "../MessageSendI.h"
class RequestFamouseRewardMsg:public MessageSendI
{
public:
    RequestFamouseRewardMsg(int bossID);
    ~RequestFamouseRewardMsg();
    ByteStream *encodingData();
    
private:
    int m_bossID;
};

#endif /* RequestFamouseRewardMsg_hpp */
