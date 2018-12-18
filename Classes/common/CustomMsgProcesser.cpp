//
//  CustomMsgProcesser.cpp
//  SuiTang
//
//  Created by 刘作双 on 14-11-28.
//
//

#include "CustomMsgProcesser.h"
#include "../protocol/CustomProtocal.hpp"
#include "../commonData/GlobalInfo.h"
#include "../commonData/dictData/DictFunction/DictFunctionManager.h"
#include "../common/noticeManager/NoticeManager.h"
#include "../module/newPlayerGuide/NewPlayerGuild.h"
#include "../module/usersPopUp/UserPopUp.hpp"
bool sizeSorting(CustomMsg* n1, CustomMsg* n2)
{
    return n1->messageID < n2->messageID;
//    int num1 = CustomMsgProcesser::getInstance()->getMessageIdSize(n1);
//    int num2 = CustomMsgProcesser::getInstance()->getMessageIdSize(n2);
//    return num1 > num2;
}
//获取消息id的优先级
int  CustomMsgProcesser::getMessageIdSize(MessageReceive* n1)
{
  
    
    return 7;
}
CustomMsgProcesser* CustomMsgProcesser::_instance = NULL;

void CustomMsgProcesser::addMessage(int customMsgID,int messageValue)
{
    if(!GlobalInfo::getInstance()->gameRole || GlobalInfo::getInstance()->gameRole->level < 1)
    {
        return;
    }
    CustomMsg* msg = new CustomMsg();
    msg->autorelease();
    msg->messageID = customMsgID;
    msg->messageValue = messageValue;
    msgList->pushBack(msg);
    sort(msgList->begin(),msgList->end(),sizeSorting);
    
    Scene* scene = Director::getInstance()->getRunningScene();
    if(!scene->getChildByTag(SCENE_TAG_BATTLE) && !scene->getChildByTag(LAYER_USER_POPUP))
    {
        this->nextMsgListData();
    }
    else if(customMsgID == CUSTOM_PROTOCAL_LEVELUP && scene->getChildByTag(SCENE_TAG_BATTLE))
    {
        
        this->nextMsgListData();
    }
}
CustomMsgProcesser::CustomMsgProcesser()
:hasMsg(false)
{
    msgList = new Vector<CustomMsg*>();
}
CustomMsgProcesser* CustomMsgProcesser::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new CustomMsgProcesser();
	}
	return _instance;
}
CustomMsgProcesser::~CustomMsgProcesser()
{
    CC_SAFE_DELETE(msgList);
    msgList  = NULL;
}
//更新队列信息
void CustomMsgProcesser::updataList()
{
    if(msgList->size() <= 0)
    {
        hasMsg = false;
        return;
    }
    CustomMsg* msg = msgList->at(0);
    hasMsg = true;
    switch (msg->messageID)
    {
        case CUSTOM_PROTOCAL_LEVELUP:
             UserPopUp::showLevel(msg->messageValue);
            break;
        case CUSTOM_PROTOCAL_FUNCTIONOPEN:
            UserPopUp::showNewFunctionOpen(msg->messageValue);
            break;
        default:
            hasMsg = false;
            break;
    }
    
    
    msgList->erase(0);
    msg= NULL;
}
bool CustomMsgProcesser::getIsHasMsg()
{
    return this->hasMsg;
}
//下一个列表数据
void CustomMsgProcesser::nextMsgListData()
{
    updataList();
    if(!hasMsg)
    {
        NewPlayerGuild::getInstance()->showNowGuide();
    }
    else
    {
        NewPlayerGuild::getInstance()->pause();
    }
}
void CustomMsgProcesser::destroyInstance()
{
	if(_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}