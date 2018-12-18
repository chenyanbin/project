//
//  FamouseBossListMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#ifndef FamouseBossListMsg_hpp
#define FamouseBossListMsg_hpp

#include "../MessageSendI.h"
class FamouseBossListMsg:public MessageSendI
{
public:
    FamouseBossListMsg();
    ~FamouseBossListMsg();
    ByteStream *encodingData();
};

#endif /* FamouseBossListMsg_hpp */
