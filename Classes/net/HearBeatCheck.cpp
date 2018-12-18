#include "HearBeatCheck.h"
#include "NetworkDataProcessing.h"
#include "../common/Dialog/Dialog.h"

HeartBeatCheck* HeartBeatCheck::m_instance = NULL;

HeartBeatCheck::HeartBeatCheck():lostCount(0)
{
    addListener();
}
HeartBeatCheck::~HeartBeatCheck()
{
    destoryInstance();
}
HeartBeatCheck* HeartBeatCheck::getInstance()
{
    if(!m_instance)
    {
        m_instance = new HeartBeatCheck();
        
    }
    return m_instance;
}
void HeartBeatCheck::destoryInstance()
{
    if(m_instance)
    {
        delete m_instance;
        m_instance = NULL;
    }
}
//开始心跳检测
void HeartBeatCheck::start()
{
    stop();
    Director::getInstance()->getScheduler()->schedule(schedule_selector(HeartBeatCheck::sendMsg),
                                                                  this,
                                                                   HEARTBEAT_CHECK_INTERVAL,
                                                      false);
    
}

void HeartBeatCheck::checkReturn(float dt)
{
     if(GlobalInfo::getInstance()->isReceivedDataEnabled)
     {
         Dialog::hideLoading();
         Dialog::showServerLoading(0,false);
         Director::getInstance()->getScheduler()->unschedule(schedule_selector(HeartBeatCheck::checkReturn),this);
     }
    lostCount ++;
    if(lostCount >= 4)
    {
        offLineReConnect();
    }
}
void HeartBeatCheck::offLineReConnect()
{
    lostCount = 0;
    NetworkDataProcessing::sharedNet()->reConnectNet();

}
void HeartBeatCheck::stop()
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(HeartBeatCheck::sendMsg),
                                                        this);
    
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(HeartBeatCheck::checkReturn),this);
}
void HeartBeatCheck::addListener()
{
}
void HeartBeatCheck::onMsgProcess(EventCustom* event)
{
    log("返回心跳协议");
    lostCount = 0;
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(HeartBeatCheck::checkReturn),this);
}
void HeartBeatCheck::sendMsg(float dt)
{
}