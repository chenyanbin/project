//
//  CdkeyMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/19.
//
//

#ifndef CdkeyMsg_h
#define CdkeyMsg_h

#include "../MessageSendI.h"
class CdkeyMsg:public MessageSendI
{
public:
    CdkeyMsg(string str);
    ~CdkeyMsg();
    ByteStream *encodingData();
private:
    string m_str;//激活码
};

#endif /* CdkeyMsg_hpp */
