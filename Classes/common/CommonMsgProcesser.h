//
//  CommonMsgProcesser.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#ifndef __FightPass__CommonMsgProcesser__
#define __FightPass__CommonMsgProcesser__

#include "cocos2d.h"
#include "../message/Encoding/MessageReceive.h"
#include "../protocol/Protocal.h"
class CommonMsgProcesser
{
public:
    static void onMsgProcess(MessageReceive* msg);
    static void onUserLevelUp(int newLevel,int oldLevel);//玩家升级
private:
    static void parseRoleAttribMsg(ByteStream* byteStream);
    static void parseRechargeMsg(ByteStream* byteStream);
    static void parseFunctionOpenMsg(ByteStream* byteStream);
    static void onStartLogin();
    static void parseMarqueeList(ByteStream* byteStream);
    static void parseMarqueeData(ByteStream* byteStream);
};

#endif /* defined(__FightPass__CommonMsgProcesser__) */
