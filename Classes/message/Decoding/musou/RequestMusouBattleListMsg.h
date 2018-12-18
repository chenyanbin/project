//
//  RequestMusouBattleListMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//请求三国无双关卡战斗列表
//

#ifndef RequestMusouBattleListMsg_hpp
#define RequestMusouBattleListMsg_hpp

#include "../MessageSendI.h"
class RequestMusouBattleListMsg:public MessageSendI
{
public:
    RequestMusouBattleListMsg(int stageID);
    ~RequestMusouBattleListMsg();
    ByteStream *encodingData();
private:
    int m_stageID;
};

#endif /* RequestMusouBattleListMsg_hpp */
