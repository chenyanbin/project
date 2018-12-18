//
//  LoginMsg.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/21.
//
//

#ifndef __FightPass__LoginMsg__
#define __FightPass__LoginMsg__

#include "../MessageSendI.h"
class LoginMsg:public MessageSendI
{
public:
    LoginMsg();
    ~LoginMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__LoginMsg__) */
