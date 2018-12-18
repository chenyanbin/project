//
//  MainUI.cpp
//  FightPass
//
//  Created by 超 顾 on 15/6/4.
//
//

#include "MainUI.h"
#include "../menuBar/HomeMenuBar.h"
#include "../userHead/UserHead.h"
#include "../../../userWealth/UserWealthLayer.h"
#include "acativeUI/HomeAcativeLayer.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../commonData/enum/DictFunctionEnum.h"
#include "../../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../setup/SetupLayer.h"
#include "../../../../common/noticeManager/Notice_Layer.h"

#include "../../../famousGeneral/famouseBossCome/FamouseBossCome.hpp"
#include "../../../../common/CustomMsgProcesser.h"
#include "../../../marquee/MarqueeManager.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../message/Decoding/notice/NoicePageMsg.h"
MainUI::MainUI()
{
    
}
MainUI::~MainUI()
{
    
}
void MainUI::onExit()
{
    BaseLayer::onExit();
}
void MainUI::onEnter()
{
    BaseLayer::onEnter();
    SoundManager::playBackgroundMusic(MUSIC_MAINSCENE);
}
void MainUI::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GlobalInfo::getInstance()->isFirstEnterMainScene = false;
}
void MainUI::onEnterTransitionDidFinish()
{
    Dialog::hideServerLoading();
    BaseLayer::onEnterTransitionDidFinish();
    GlobalInfo::getInstance()->taskInStageBattle = 0;
    if(GlobalInfo::getInstance()->isFirstEnterMainScene)
    {
        if(GlobalInfo::getInstance()->curHeroCount >= GlobalInfo::getInstance()->maxHeroCount)
        {
            Dialog::show("您的英雄数量已经达到上限，请清理武将或使用英雄扩充令扩充");
        }
        if(GlobalInfo::getInstance()->curEquipCount >= GlobalInfo::getInstance()->equipCountLimit)
        {
            Dialog::show("您的装备数量已经达到上限，请清理装备或使用装备扩充令扩充");
        }
        if(GlobalInfo::getInstance()->isShowGuide)
        {
            if(!NewPlayerGuild::getInstance()->isOpened(DictFunctionEnumStory, 3) && GlobalInfo::getInstance()->gameRole->level <= 1)
            {
                NewPlayerGuild::getInstance()->showGuideContent(DictFunctionEnumStory, 1);
            }
            else
            {
                NewPlayerGuild::getInstance()->onUserLevelUp(GlobalInfo::getInstance()->gameRole->level);
            }
        }
    
       
    }
    else
    {
        if(GlobalInfo::getInstance()->isShowGuide)
        {
            if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->id > 9)
            {
                NewPlayerGuild::getInstance()->showNowGuide();
            }
        }
     
    }
    
    setNotice();
   
    //
//      CustomMsgProcesser::getInstance()->addMessage(1000001,3);
//    CustomMsgProcesser::getInstance()->addMessage(1000002,4);//新功能开启
//    GlobalInfo::getInstance()->famouseBossID = 38;
//    FamouseBossCome::show();
//    MarqueeData* data = new MarqueeData();
//    data->autorelease();
////    data->content = " 恭喜#马博#获得3星武将#mmmmm#！";
//      data->content = " 马博#赵云#5";
//    data->mode = 2;
//    data->marqueeType =1;
//    data->marqueeID = 1;
//    data->op = 1;
//    data->op = data->op <= 0 ? 1 : data->op;
//    data->loopTimes =232;
//    data->loopInterval =1;
//    data->loopCount = 3;
//    data->dictTipsID = 6001005;
//    MarqueeManager::getInstance()->addContent(data);


}
bool MainUI::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        setMask();
        setMenuBar();
        setUserWealth();
         setUserHead();
        setAcativeBtn();
        
        bref = true;
    } while (false);
    return bref;}
void MainUI::show(Node* _parent,int tag)
{
   
    if(_parent->getChildByTag(tag))
    {
        return;
    }
    MainUI* barLayer = MainUI::create();
    barLayer->setAnchorPoint(Point::ZERO);
    _parent->addChild(barLayer,3,tag);
}
void MainUI::setMask()
{
    Sprite* layer = Sprite::create(IMG_PUBLIC_MASK);
    layer->setAnchorPoint(Point::ZERO);
    layer->setOpacity(100);
    PublicShowUI::setTargetScale(layer,true);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
    this->addChild(layer,0);
    
    
    
    Sprite* bgSprgray = Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
    PublicShowUI::setTargetScale(bgSprgray,true);
    bgSprgray->setAnchorPoint(Point::ZERO);
    bgSprgray->setPosition(Point::ZERO);
    bgSprgray->setOpacity(100);
    this->addChild(bgSprgray,1);
}
void MainUI::setMenuBar()
{
    HomeMenuBar* menuBar = HomeMenuBar::create();
    menuBar->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(menuBar);
    menuBar->setPosition(VisibleRect::right().x-menuBar->getContentSize().width,VisibleRect::bottom().y);
    this->addChild(menuBar,2);
    
//    HomeMenuBar::show(this, 2);
}
void MainUI::setUserHead()
{
    UserHead* userHead = UserHead::create();
    userHead->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(userHead);
    userHead->setPositionX(VisibleRect::left().x);
    userHead->setPositionY(VisibleRect::top().y - userHead->getContentSize().height+5 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(userHead,4);

}
void MainUI::setUserWealth()
{
    
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::GENERAL);
    PublicShowUI::setTargetScale(layer);
    layer->setPositionX(VisibleRect::left().x + 340 * GlobalInfo::getInstance()->screenScaleX);
    layer->setPositionY(VisibleRect::top().y - layer->getContentSize().height - 18 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(layer,3);

}
void MainUI::setAcativeBtn()
{
    HomeAcativeLayer* acativelayer = HomeAcativeLayer::create();
    acativelayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(acativelayer);
    acativelayer->setPositionX(370 * GlobalInfo::getInstance()->screenScaleX);
    acativelayer->setPositionY(VisibleRect::top().y - acativelayer->getContentSize().height - 60 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(acativelayer,3);
}
void MainUI::setNotice()
{
    
    if(GlobalInfo::getInstance()->isFirstEnterMainScene)
    {
        this->requestListMsg();
    }
    
}
void MainUI::requestListMsg()
{
    NoicePageMsg* msg = new NoicePageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MainUI::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_ACCOUNT_NoticePageResp)
    {
        int sizeInt=message->byteStream->getByte();
        Vector<NoticeData*> *noticeList=new Vector<NoticeData*>();
        for (int i=0; i<sizeInt; i++) {
            NoticeData* data=new NoticeData();
            data->autorelease();
            data->NoticeName=message->byteStream->getUTF8();
            string dec=message->byteStream->getUTF8();
            data->DescList->push_back(dec);
            noticeList->pushBack(data);
        }
        if (sizeInt>0) {
            Notice_Layer::show(noticeList);
        }
    }
}
void MainUI::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_NoticePageResp).c_str(), CC_CALLBACK_1(MainUI::onMsgProcess, this));
}
void MainUI::removeEventListener()
{
    BaseLayer::removeEventListener();
}