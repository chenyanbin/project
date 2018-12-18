//
//  UpdateYaYaIdMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 16/1/7.
//
//

#ifndef UpdateYaYaIdMsg_h
#define UpdateYaYaIdMsg_h

#include "../MessageSendI.h"
class UpdateYaYaIdMsg:public MessageSendI
{
public:
    UpdateYaYaIdMsg(int id);
    ~UpdateYaYaIdMsg();
    ByteStream *encodingData();
private:
    int userId;
};

#endif /* UpdateYaYaIdMsg_h */
