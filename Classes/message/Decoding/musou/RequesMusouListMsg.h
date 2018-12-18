//
//  RequesMusouListMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//三国无双关卡列表
//

#ifndef RequesMusouListMsg_hpp
#define RequesMusouListMsg_hpp

#include "../MessageSendI.h"
class RequesMusouListMsg:public MessageSendI
{
public:
    RequesMusouListMsg();
    ~RequesMusouListMsg();
    ByteStream *encodingData();
};
#endif /* RequesMusouListMsg_hpp */
