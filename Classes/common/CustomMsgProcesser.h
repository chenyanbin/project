//
//  CustomMsgProcesser.h
//  SuiTang
//
//  Created by 刘作双 on 14-11-28.
//
//针对：主公升级，获得英雄，打劫，获得日常任务奖励，新功能开启，玩家升级，非强制性提示

#ifndef __SuiTang__CustomMsgProcesser__
#define __SuiTang__CustomMsgProcesser__

#include "cocos2d.h"
#include "../message/Encoding/MessageReceive.h"
USING_NS_CC;
using namespace std;
class CustomMsg:public Ref
{
public:
    int messageID;
    int messageValue;
};
class CustomMsgProcesser
{
public:
	~CustomMsgProcesser();
	void destroyInstance();
	static CustomMsgProcesser* getInstance();
    void addMessage(int customMsgID,int messageValue);
    //下一个列表数据
    void nextMsgListData();
    int  getMessageIdSize(MessageReceive* n1);
    bool getIsHasMsg();
private:
	static CustomMsgProcesser* _instance;
    //更新队列信息
    void updataList();
    Vector<CustomMsg*> *msgList;

protected:
	CustomMsgProcesser();
    bool hasMsg;
};

#endif /* defined(__SuiTang__CustomMsgProcesser__) */
