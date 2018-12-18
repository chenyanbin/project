//
//  MessageReceivedManagement.h
//
//  消息接收类接口
//
//  Created by 孙宏利 on 14-4-4.
//
//

#ifndef __IpGame__MessageReceiveI__
#define __IpGame__MessageReceiveI__

#include "../DynamicallyCreateObj.h"
#include "../../net/bytestream.h"
class MessageReceiveI {
    
    /***********************实现动态反射的宏定义*************************/
    
    DECLEAR_DYNCRT_BASE(MessageReceiveI)
    DECLEAR_DYNCRT_CLASS(MessageReceiveI, MessageReceiveI)
    
public:
    
    MessageReceiveI();~MessageReceiveI();
    
    /***********************继承后必须实现的方法*************************/
    
    virtual bool decodingData();       //解析数据
    virtual void setBuff(void*pbuf);   //数据来源
    virtual void setBuffLen(int len);  //数据长度
    
    void* buff;
    int buflen;
    ByteStream* byteStream;
};

#endif
