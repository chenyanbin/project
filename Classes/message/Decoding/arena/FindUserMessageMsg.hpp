//
//  FindUserMessageMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/28.
//
//  查看对方

#ifndef FindUserMessageMsg_hpp
#define FindUserMessageMsg_hpp

#include "../MessageSendI.h"
class FindUserMessageMsg:public MessageSendI
{
public:
    FindUserMessageMsg(int idType,long roleId);
    ~ FindUserMessageMsg();
    ByteStream *encodingData();
private:
    int m_idType;
    long m_roleid;
    
};

#endif /* FindUserMessageMsg_hpp */
