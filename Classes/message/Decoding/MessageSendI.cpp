//
//  MessageSendI.cpp
//  IpGame
//
//  Created by 孙宏利 on 14-4-7.
//
//

#include "MessageSendI.h"
IMPLEMENT_DYNCRT_BASE(MessageSendI)
IMPLEMENT_DYNCRT_CLASS(MessageSendI)
int MessageSendI::sequenceCode = 0;
MessageSendI::MessageSendI()
:headBufferee(NULL)
,messageID(0)
{
    sequenceCode = sequenceCode == INT32_MAX ? 0 : ++sequenceCode;
}
MessageSendI::~MessageSendI()
{
    delete headBufferee;
    headBufferee = NULL;
}
ByteStream* MessageSendI::encodingData()
{
    headBufferee = new ByteStream(1024);
    headBufferee->putInt(0);

    return headBufferee;
}
ByteStream* MessageSendI::encodingData(int msgID)
{
    MessageSendI::encodingData();
    headBufferee->putInt(msgID);
    headBufferee->putInt(sequenceCode);
    this->messageID = msgID;
    return headBufferee;
}

int MessageSendI::getMessageID()
{
    if(messageID == 0)
    {
        int m_pos = this->headBufferee->position();
        headBufferee->setPosition(0);
        headBufferee->getInt();
        this->messageID = headBufferee->getInt();
        headBufferee->setPosition(m_pos);
    }
    return this->messageID;
}