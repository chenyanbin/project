//
//  RequestMarqueeMsg.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/2.
//请求跑马灯列表
//

#ifndef RequestMarqueeMsg_hpp
#define RequestMarqueeMsg_hpp

#include "../MessageSendI.h"
class RequestMarqueeMsg:public MessageSendI
{
public:
    RequestMarqueeMsg();
    ~RequestMarqueeMsg();
    ByteStream *encodingData();
};

#endif /* RequestMarqueeMsg_hpp */
