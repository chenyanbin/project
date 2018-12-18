//
//  MessageReceiveI.cpp
//  IpGame
//
//  Created by ����� on 14-4-7.
//
//

#include "MessageReceiveI.h"

IMPLEMENT_DYNCRT_BASE(MessageReceiveI)
IMPLEMENT_DYNCRT_CLASS(MessageReceiveI)

MessageReceiveI::MessageReceiveI()
:buff(NULL)
,byteStream(NULL)
{}
MessageReceiveI::~MessageReceiveI()
{
    buff = NULL;
    if(byteStream)
    {
        delete byteStream;
        byteStream = NULL;
    }
}

bool MessageReceiveI::decodingData(){return true;}
void MessageReceiveI::setBuff(void * pbuf){}
void MessageReceiveI::setBuffLen(int len){}