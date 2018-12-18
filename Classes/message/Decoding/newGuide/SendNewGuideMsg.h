//
//  SendNewGuideMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/28.
//
//

#ifndef SendNewGuideMsg_hpp
#define SendNewGuideMsg_hpp

#include "../MessageSendI.h"

class SendNewGuideMsg:public MessageSendI
{
public:
    SendNewGuideMsg(int functionID,int _step);
    ~SendNewGuideMsg();
    ByteStream *encodingData();
private:
    int m_function;
    int m_step;
};


#endif /* SendNewGuideMsg_hpp */
