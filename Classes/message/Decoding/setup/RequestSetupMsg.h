//
//  RequestSetupMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/10/22.
//
//

#ifndef __FightPass__RequestSetupMsg__
#define __FightPass__RequestSetupMsg__

#include "../MessageSendI.h"
class RequestSetupMsg:public MessageSendI
{
public:
    RequestSetupMsg(string _name);
    ~RequestSetupMsg();
    ByteStream *encodingData();
private:
    string m_name;//名字哦
};


#endif /* defined(__FightPass__RequestSetupMsg__) */
