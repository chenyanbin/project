//
//  MessageReceive.cpp
//  SuiTang
//
//  Created by mac on 14-6-4.
//
//

#include "MessageReceive.h"
MessageReceive::MessageReceive()
:byteStream(NULL)
,messageID(0)
,state(false)
,errorMsg("")
,debugMsg("")
,colorFlag(0)
,sequenceCode(0)
,retCode(0)
{
    
}
MessageReceive::~MessageReceive()
{
    CC_SAFE_DELETE(byteStream);
    byteStream = NULL;
}
