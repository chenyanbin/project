//
//  FamouseFightMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#ifndef FamouseFightMsg_hpp
#define FamouseFightMsg_hpp

#include "../MessageSendI.h"
class FamouseFightMsg:public MessageSendI
{
public:
    FamouseFightMsg(int bossID);
    ~FamouseFightMsg();
    ByteStream *encodingData();
private:
    int m_bossId;
};

#endif /* FamouseFightMsg_hpp */
