//
//  ArenaListMsg.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/10.
//竞技场列表
//

#ifndef ArenaListMsg_hpp
#define ArenaListMsg_hpp

#include "../MessageSendI.h"
class ArenaListMsg:public MessageSendI
{
public:
    ArenaListMsg(int isrefresh);
    ~ArenaListMsg();
    ByteStream *encodingData();
private:
    int m_isrefresh;
};

#endif /* ArenaListMsg_hpp */
