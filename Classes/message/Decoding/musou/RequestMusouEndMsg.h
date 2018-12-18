//
//  RequestMusouEndMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#ifndef RequestMusouEndMsg_hpp
#define RequestMusouEndMsg_hpp

#include "../MessageSendI.h"
class RequestMusouEndMsg:public MessageSendI
{
public:
    //succ	是否成功	byte	Y	0失败 1成功
    RequestMusouEndMsg(int battleID,bool isSuc,int starCount,int bloodBottle);
    ~RequestMusouEndMsg();
    ByteStream *encodingData();
private:
    int m_battleID;
    bool m_isSuc;
    int m_starCount;
    int m_bloodBottle;
};

#endif /* RequestMusouEndMsg_hpp */
