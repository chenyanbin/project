//
//  RoleInfoMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/24.
//请求角色信息
//

#ifndef RoleInfoMsg_hpp
#define RoleInfoMsg_hpp

#include "../MessageSendI.h"
class RoleInfoMsg:public MessageSendI
{
public:
    RoleInfoMsg();
    ~RoleInfoMsg();
    ByteStream *encodingData();
};


#endif /* RoleInfoMsg_hpp */
