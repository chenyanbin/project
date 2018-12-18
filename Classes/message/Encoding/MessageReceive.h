//
//  MessageReceive.h
//  SuiTang
//
//  Created by mac on 14-6-4.
//
//

#ifndef __SuiTang__MessageReceive__
#define __SuiTang__MessageReceive__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "../DynamicallyCreateObj.h"
#include "../../net/bytestream.h"
class MessageReceive:public Ref
{
public:
    MessageReceive();
    ~MessageReceive();
    ByteStream* byteStream;
    int messageID;
    int retCode;
    bool state;//协议状态
    
    string errorMsg;//显示提示信息
    string debugMsg;//错误调试信息
    
    int colorFlag;//颜色值
    int sequenceCode;
private:
    
};

#endif /* defined(__SuiTang__MessageReceive__) */
