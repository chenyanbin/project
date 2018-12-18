//
//  ReloginMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/25.
//断线重连
//

#ifndef ReloginMsg_hpp
#define ReloginMsg_hpp

#include "../MessageSendI.h"
class ReloginMsg:public MessageSendI
{
public:
    ReloginMsg();
    ~ReloginMsg();
    ByteStream *encodingData();
};

#endif /* ReloginMsg_hpp */
