//
//  RefreshDot.cpp
//  FightPass
//
//  Created by 超 顾 on 16/3/3.
//
//

#include "RefreshDot.h"
#include "../../commonData/GlobalInfo.h"
#include "../../common/Dialog/Dialog.h"
#include "../../message/Decoding/dot/RequestDotMsg.h"
#include "../../net/NetworkDataProcessing.h"
RefreshDot* RefreshDot::_instance = NULL;

RefreshDot::RefreshDot()
: m_target(NULL)
,m_point(0,0)
,m_bol(false)
,m_functionID1(0)
,m_functionID2(0)
,m_functionID3(0)
{
    addEventListener();
}
RefreshDot::~RefreshDot()
{
    removeEventListener();
}
RefreshDot* RefreshDot::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new RefreshDot();
    }
    return _instance;
}
void RefreshDot::requestMsg(Node* target,Point point,bool bol, int functionId1 ,int functionId2 ,int functionId3)
{
    Dialog::showServerLoading();
    m_target = target;
    m_point=point;
    m_bol=bol;
    m_functionID1 = functionId1;
    m_functionID2 = functionId2;
    m_functionID3 = functionId3;
    
    RequestDotMsg* msg = new RequestDotMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void RefreshDot::onRedMsgBack(EventCustom* msg)
{
    
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_ACCOUNT_RedPointResp)
    {
        string redPointStr = message->byteStream->getUTF8();//红点 
        GlobalInfo::getInstance()->initDotList(redPointStr);
        PublicShowUI::setDot(m_target, m_point, m_bol,m_functionID1,m_functionID2,m_functionID3);
    }
}
void RefreshDot::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_RedPointResp).c_str(), CC_CALLBACK_1(RefreshDot::onRedMsgBack, this));
}
void RefreshDot::removeEventListener()
{
    BaseLayer::removeEventListener();
}