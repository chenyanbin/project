//
//  FamouseActiveMsg.hpp
//  FightPass
//名将传 活动页
//  Created by zhangxiaobin on 16/1/21.
//
//

#ifndef FamouseActiveMsg_hpp
#define FamouseActiveMsg_hpp
#include "../MessageSendI.h"
class FamouseActiveMsg:public MessageSendI
{
public:
    FamouseActiveMsg();
    ~FamouseActiveMsg();
    ByteStream *encodingData();
};

#endif /* FamouseActiveMsg_hpp */
