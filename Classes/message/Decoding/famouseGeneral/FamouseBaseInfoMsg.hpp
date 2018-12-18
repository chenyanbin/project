//
//  FamouseBaseInfoMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//名将传基础信息
//

#ifndef FamouseBaseInfoMsg_hpp
#define FamouseBaseInfoMsg_hpp

#include "../MessageSendI.h"
class FamouseBaseInfoMsg:public MessageSendI
{
public:
    FamouseBaseInfoMsg();
    ~FamouseBaseInfoMsg();
    ByteStream *encodingData();
};

#endif /* FamouseBaseInfoMsg_hpp */
