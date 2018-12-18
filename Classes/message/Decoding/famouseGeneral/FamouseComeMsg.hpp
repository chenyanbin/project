//
//  FamouseComeMsg.hpp
//  FightPass
//名将来袭页
//  Created by zhangxiaobin on 16/1/25.
//
//

#ifndef FamouseComeMsg_hpp
#define FamouseComeMsg_hpp

#include "../MessageSendI.h"
class FamouseComeMsg:public MessageSendI
{
public:
    FamouseComeMsg();
    ~FamouseComeMsg();
    ByteStream *encodingData();
};

#endif /* FamouseComeMsg_hpp */
