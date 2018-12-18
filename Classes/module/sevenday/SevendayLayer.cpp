//
//  SevendayLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/12.
//
//

#include "SevendayLayer.hpp"
#include "../userWealth/UserWealthLayer.h"
#include "SevendayPageListLayer.hpp"
#include "../../common/Dialog/Dialog.h"
#include "../../protocol/Protocal.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/sevenday/WeekOpenDayMsg.h"
#include "../../message/Decoding/sevenday/WeekRewardPageMsg.h"
#include "../../message/Decoding/sevenday/WeekHalfPageMsg.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "sevendayData/SevendayRedPointDataManager.hpp"
#include "../../protocol/UserCustomEvent.h"
#include "../../message/Decoding/sevenday/WeekRedPotmsg.hpp"
SevendayLayer::SevendayLayer()
:sx(0)
,boxBtn(NULL)
,m_dayIndex(0)
,m_realDay(1)
{
   
}
SevendayLayer::~ SevendayLayer()
{
}
bool SevendayLayer::init(int day)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx= GlobalInfo::getInstance()->screenScaleX;
        this->setBackBtn(0,15*sx);
        m_dayIndex = day;
        createLayer();
        topLayer();
        
        setRightBtn();
        bref = true;
    } while (false);
    return bref;
}
void SevendayLayer::onEnter()
{
    BaseLayer::onEnter();
    
}
void SevendayLayer::onExit()
{
    BaseLayer::onExit();
}
void SevendayLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
    
    requestWeekRedPotPage();
    requestWeekDayMsg();
    
}
void SevendayLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->removeEventListener();
    
}
SevendayLayer* SevendayLayer::create(int day)
{
    SevendayLayer* layer = new SevendayLayer();
    if(layer && layer->init(day))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void SevendayLayer::show(int fromeScene,int day)
{
    Director::getInstance()->purgeCachedData();
    SevendayLayer* layer = SevendayLayer::create(day);
    layer->setFromScene(fromeScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_GENERALS);
    Director::getInstance()->replaceScene(scene);
}
void SevendayLayer::createLayer()
{
    Sprite* bg=Sprite::create(IMG_SEVEENDAY_BG);
    PublicShowUI::setTargetScale(bg,true);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);
    
    Sprite* bgSprgray = Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
    PublicShowUI::setTargetScale(bgSprgray,true);
    bgSprgray->setAnchorPoint(Point::ZERO);
    bgSprgray->setPosition(Point::ZERO);
    this->addChild(bgSprgray,0);
    
    Sprite* spr = Sprite::create(IMG_GENERALS_SEVENACTIVITY_PERSONAE);
    spr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(spr);
    spr->setPosition(VisibleRect::center().x-spr->getContentSize().width/2-350*sx,VisibleRect::center().y-spr->getContentSize().height/2);
    this->addChild(spr,1);
    
//    Sprite* sprlabel = Sprite::create(IMG_GENERALS_SEVENACTIVITY_LABEL);
//    sprlabel->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(sprlabel);
//    sprlabel->setPosition(VisibleRect::center().x-sprlabel->getContentSize().width/2-350*sx,VisibleRect::center().y-sprlabel->getContentSize().height/2-200*sx);
//    this->addChild(sprlabel,2);
}
void SevendayLayer::topLayer()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,3);
    layer->setTitle(IMG_PUBLIC_SEVENDAY);
}

void SevendayLayer::setRightBtn()
{
    const char* pathlist[] = {IMG_SEVEENDAY_SEVEN, IMG_SEVEENDAY_SIX, IMG_SEVEENDAY_FIVE, IMG_SEVEENDAY_FOUR, IMG_SEVEENDAY_THREE, IMG_SEVEENDAY_TWO, IMG_SEVEENDAY_ONE};
    boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL,10, CC_CALLBACK_1(SevendayLayer::onRightBtnClick, this));
    for (int i =0 ; i < 7; i++) {
        boxBtn->addCustomBtn(IMG_PUBLIC_BUTTON_TWO_RED, IMG_PUBLIC_BUTTON_TWO_ORANGE, pathlist[i],pathlist[i]);
    }
//    for (int i = 0; i < 7; i++) {
//        SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(i),Point::ZERO,7-i);
//    }
    PublicShowUI::setTargetScale(boxBtn);
    boxBtn->setAnchorPoint(Point::ZERO);
    boxBtn->setPosition(VisibleRect::right().x-130*sx,VisibleRect::center().y-boxBtn->getContentSize().height/2);
    this->addChild(boxBtn);
}
void SevendayLayer::onRightBtnClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    log("%d",target->getTag());
//    if (m_dayIndex == target->getTag()) {
//        return;
//    }
    switch (target->getTag()) {
        case 0:
            setPageList(TAG_SEVENDAY);
            break;
        case 1:
            setPageList(TAG_SIXDAY);
            break;
        case 2:
            setPageList(TAG_FIVEDAY);
            break;
        case 3:
            setPageList(TAG_FOURDAY);
            break;
        case 4:
            setPageList(TAG_THREEDAY);
            break;
        case 5:
            setPageList(TAG_TWODAY);
            break;
        case 6:
            setPageList(TAG_ONETAY);
            break;
        default:
            break;
    }
}
void SevendayLayer::setPageList(int day)
{
    if (m_realDay<1) {
        boxBtn->resetAllBtn();
        string str = StringUtils::format("活动已结束");
        NoticeManager::getInstance()->showNotice(str.c_str());
        return;
    }
    if (m_dayIndex == day) {
        return;
    }else if (day>m_realDay)
    {
        boxBtn->resetAllBtn();
        string str = StringUtils::format("第%d天还没开启",day);
        NoticeManager::getInstance()->showNotice(str.c_str());
        return;
    }
    
    SevendayPageListLayer* layer = (SevendayPageListLayer*)this->getChildByTag(m_dayIndex);
    if(layer)
    {
        this->removeChildByTag(m_dayIndex);
    }
    m_dayIndex = day;
    layer =  SevendayPageListLayer::create(m_dayIndex);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPositionX(VisibleRect::center().x-layer->getContentSize().width/2+100*sx);
    layer->setPositionY(VisibleRect::center().y - layer->getContentSize().height/2 -50*sx );
    this->addChild(layer, 2,m_dayIndex);
}

void SevendayLayer::requestWeekDayMsg()//请求是第几天
{
    Dialog::showServerLoading();
    WeekOpenDayMsg* msg = new WeekOpenDayMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void SevendayLayer::onWeekDayMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekOpenDayResp)
    {
        if(message->state)//返回成功
        {
            m_realDay = message->byteStream->getByte();
            m_dayIndex = m_realDay;
            if (m_dayIndex < 1) {
                NoticeManager::getInstance()->showNotice("活动已结束");
                return;
            }
            switch (m_dayIndex) {
                case 1:
                    boxBtn->getButtonAt(6)->selected();
                    break;
                case 2:
                    boxBtn->getButtonAt(5)->selected();
                    break;
                case 3:
                    boxBtn->getButtonAt(4)->selected();
                    break;
                case 4:
                    boxBtn->getButtonAt(3)->selected();
                    break;
                case 5:
                    boxBtn->getButtonAt(2)->selected();
                    break;
                case 6:
                    boxBtn->getButtonAt(1)->selected();
                    break;
                case 7:
                    boxBtn->getButtonAt(0)->selected();
                    break;
                default:
                    break;
            }
          
            SevendayPageListLayer* layer =  SevendayPageListLayer::create(m_dayIndex);
            layer->setAnchorPoint(Point::ZERO);
            layer->setPositionX(VisibleRect::center().x-layer->getContentSize().width/2+100*sx);
            layer->setPositionY(VisibleRect::center().y - layer->getContentSize().height/2 -50*sx );
            this->addChild(layer, 2,m_dayIndex);

        }
    }
    
}

void SevendayLayer::requestWeekRedPotPage()//红点
{
    Dialog::showServerLoading();
    WeekRedPotmsg* msg = new WeekRedPotmsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void SevendayLayer::onWeekRedPotProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekRedPointStatusResp)
    {
        if(message->state)//返回成功
        {
            const char* str = message->byteStream->getUTF8();
//            string str = message->byteStream->getUTF8();
            SevendayRedPointDataManager::getInstance()->addData(str);
            for (int i = 0; i < 7; i++) {
                SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(i),Point(-5,-5),7-i);
            }
            broadMsg(CUSTOM_SEVENDAY_MODULE_REDPOINT);
        }
    }
}

void SevendayLayer::refreshRedPot(EventCustom* msg)
{
    requestWeekRedPotPage();
    
//    __Integer* inter = (__Integer*)msg->getUserData();
//    if(!inter)
//    {
//        return;
//    }
//    int tag_index = inter->getValue();
//    if (tag_index == 1) {
//        SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(6), Point::ZERO, 1);
//    }else if (tag_index == 2)
//    {
//        SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(5), Point::ZERO, 2);
//    }else if (tag_index == 3)
//    {
//        SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(4), Point::ZERO, 3);
//    }else if (tag_index == 4)
//    {
//        SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(3), Point::ZERO, 4);
//    }else if (tag_index == 5)
//    {
//        SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(2), Point::ZERO, 5);
//    }else if (tag_index == 6)
//    {
//        SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(1), Point::ZERO, 6);
//    }else if (tag_index == 7)
//    {
//        SevendayRedPointDataManager::getInstance()->setDayPot(boxBtn->getChildByTag(0), Point::ZERO, 6);
//    }
//    broadMsg(CUSTOM_SEVENDAY_MODULE_REDPOINT);
    
}
void SevendayLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekOpenDayResp).c_str(), CC_CALLBACK_1(SevendayLayer::onWeekDayMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekRedPointStatusResp).c_str(), CC_CALLBACK_1(SevendayLayer::onWeekRedPotProcess, this));
    this->addUserMsg(CUSTOM_SEVENDAY_REDPOINT, CC_CALLBACK_1(SevendayLayer::refreshRedPot, this));
    
}
void SevendayLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
