//
//  MessageSendI.h
//  IpGame
//
//  Created by 孙宏利 on 14-4-4.
//
//

#ifndef IpGame_MessageSendI_h
#define IpGame_MessageSendI_h
#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
#include "../../net/bytestream.h"
#include "../DynamicallyCreateObj.h"

#include "../../protocol/Protocal.h"
#define  SetMessageLength() \
int templen = headBufferee->position()-4;\
headBufferee->setPosition(0);\
headBufferee->putInt(templen);\
headBufferee->setPosition(templen+4);\
return headBufferee;


class MessageSendI{
    
    DECLEAR_DYNCRT_BASE(MessageSendI)
    DECLEAR_DYNCRT_CLASS(MessageSendI, MessageSendI)
    
public:
    
    MessageSendI();
    ~MessageSendI();
    ByteStream *headBufferee;
    virtual ByteStream* encodingData();
    virtual ByteStream* encodingData(int msgID);
    int getMessageID();
    int messageID;
    static int sequenceCode;
};

#endif
