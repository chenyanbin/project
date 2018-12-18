//
//  FamouseTouchMsg.hpp
//  FightPass
//是否触发了boss 是否触发了名将来袭
//  Created by zhangxiaobin on 16/1/25.
//
//

#ifndef FamouseTouchMsg_hpp
#define FamouseTouchMsg_hpp

#include "../MessageSendI.h"
class FamouseTouchMsg:public MessageSendI
{
public:
    FamouseTouchMsg(int battleID);
    ~FamouseTouchMsg();
    ByteStream *encodingData();
    
private:
    int m_battleID;
};

#endif /* FamouseTouchMsg_hpp */
