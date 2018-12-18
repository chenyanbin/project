//
//  MoneyDrawing.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/14.
//
//

#include "MoneyDrawing.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../Signin_Scene.h"
#include "../../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../../common/commonEffect/CommonEffect.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../message/Decoding/signin/SigninLuckyMsg.h"
#include "../../../../message/Decoding/signin/SiginLuckyStartMsg.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../protocol/Protocal.h"
#include "MoneyDrawingDataManager.h"
#include "MoneyDrawingGiftLayer.h"
#include "../../../../common/noticeManager/NoticeManager.h"
MoneyDrawing::MoneyDrawing()
:sx(1)
,m_totalCount(0)
,m_todayCount(0)
,m_todayTotalCount(0)
,m_status(0)
,m_remainingTimes(0)
,label(NULL)
,TAG_TODAYTIME(10)
,TAG_ALLTODAY(11)
,TAG_DAOJISHI(12)
,TAG_RECUITIME(13)
{
    
}
MoneyDrawing::~MoneyDrawing()
{
    MoneyDrawingDataManager::getInstance()->destroyInstance();
}

void MoneyDrawing::onExit()
{
    BaseLayer::onExit();
}
void MoneyDrawing::onEnter()
{
    BaseLayer::onEnter();
    this->createLayer();
}
void MoneyDrawing::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void MoneyDrawing::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    requestLuckyMsg();
}
bool MoneyDrawing::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
//        this->setBackground(IMG_SIGNIN_LUXURY_LABEL2);
//        this->createLayer();
        
        
        this->isAbleGuiding = true;
        bref = true;
    } while (false);
    return bref;
}
MoneyDrawing* MoneyDrawing::create()
{
    MoneyDrawing* layer = new MoneyDrawing();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void MoneyDrawing::createLayer()
{
    
    Sprite* bg=Sprite::create(IMG_SIGNIN_MONEYDRAW_BG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg,true,true);
    bg->setTag(TAG_BG);
    this->addChild(bg);
    
    Sprite* top=Sprite::create(IMG_SIGNIN_MONEYDRAW_TOP);
    top->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(top);
    top->setPosition(0,VisibleRect::top().y-70*sx-top->getContentSize().height);
    this->addChild(top);
    
    Sprite* bottom=Sprite::create(IMG_SIGNIN_MONEYDRAW_BOTTOM);
    bottom->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bottom);
    this->addChild(bottom);
    
    CommonEffect* commonEffect4 = CommonEffect::create("dishangyuanbao",true,false);
    commonEffect4->setAnchorPoint(Point::ZERO);
    commonEffect4->setPosition(33,173);
    bottom->addChild(commonEffect4,2);
    
    CommonEffect* commonEffect5 = CommonEffect::create("dishangyuanbao",true,false);
    commonEffect5->setAnchorPoint(Point::ZERO);
    commonEffect5->setPosition(120,124);
    bottom->addChild(commonEffect5,2);
    
    CommonEffect* commonEffect6 = CommonEffect::create("dishangyuanbao",true,false);
    commonEffect6->setAnchorPoint(Point::ZERO);
    commonEffect6->setPosition(228,112);
    bottom->addChild(commonEffect6,2);
    
    CommonEffect* commonEffect7 = CommonEffect::create("dishangyuanbao",true,false);
    commonEffect7->setAnchorPoint(Point::ZERO);
    commonEffect7->setPosition(749,158);
    bottom->addChild(commonEffect7,2);
    
    CommonEffect* commonEffect8 = CommonEffect::create("dishangyuanbao",true,false);
    commonEffect8->setAnchorPoint(Point::ZERO);
    commonEffect8->setPosition(851,153);
    bottom->addChild(commonEffect8,2);
    
    CommonEffect* commonEffect9 = CommonEffect::create("dishangyuanbao",true,false);
    commonEffect9->setAnchorPoint(Point::ZERO);
    commonEffect9->setPosition(888  ,50);
    bottom->addChild(commonEffect9,2);

//    Sprite* draw = Sprite::create(IMG_SIGNIN_MONEYDRAW_USE);
//    draw->setAnchorPoint(Point::ZERO);
//    draw->setPosition(273*sx,47*sx);
//    PublicShowUI::setTargetScale(draw);
//    this->addChild(draw);
    
    
    CommonEffect* commonEffect2 = CommonEffect::create("qifu",true,false);
    commonEffect2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(commonEffect2);
    commonEffect2->setPosition(273*sx,47*sx);
    this->addChild(commonEffect2,1);
    
    //祈福
    Button* person = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(MoneyDrawing::onPersonClick, this)); //
    person->setAnchorPoint(Point::ZERO);
    person->setPosition(500*sx,80*sx);
    PublicShowUI::setTargetScale(person);
    this->addChild(person,2);
    Sprite* drawWord = Sprite::create(IMG_SIGNIN_MONEYDRAW_DRAWWORD);
    drawWord->setAnchorPoint(Point::ZERO);
    drawWord->setPosition(Point::ZERO);
    person->addChild(drawWord,5);
    
   // 查看
    Button* btnsee = Button::create(IMG_MUSOU_SEE, IMG_MUSOU_SEE, CC_CALLBACK_1(MoneyDrawing::onseeClick, this)); //
    btnsee->setAnchorPoint(Point::ZERO);
    btnsee->setPosition(710*sx,30*sx);
    PublicShowUI::setTargetScale(btnsee);
    this->addChild(btnsee,2);
    

    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumPrayerButton, person);
    Sprite* totalLabel=Sprite::create(IMG_SIGNIN_MONEYDRAW_TOTAL);
    totalLabel->setAnchorPoint(Point::ZERO);
    totalLabel->setPosition(596*sx,336*sx);
    PublicShowUI::setTargetScale(totalLabel);
    this->addChild(totalLabel,3);
    
    Sprite* _label=Sprite::create(IMG_SIGNIN_MONEYDRAW_LABEL);
    _label->setAnchorPoint(Point::ZERO);
    _label->setPosition(36*sx,354*sx);
    PublicShowUI::setTargetScale(_label);
    this->addChild(_label);
    
    CommonEffect* commonEffect3 = CommonEffect::create("jianchanqifu",true,false);
    commonEffect3->setAnchorPoint(Point::ZERO);
    commonEffect3->setPosition(0,70-commonEffect3->getContentSize().height/2);
    _label->addChild(commonEffect3,2);
    
    
    
    
    Sprite* toadyFinish=Sprite::create(IMG_SIGNIN_MONEYDRAW_TODAYFINISH);
    toadyFinish->setAnchorPoint(Point::ZERO);
    toadyFinish->setPosition(454*sx,50*sx);
    PublicShowUI::setTargetScale(toadyFinish);
    this->addChild(toadyFinish);
    Size size=bg->getContentSize();
    this->setContentSize(size);

    
//    size.height=size.height+person->getPositionY()*sx;
//    Sprite* headBox=Sprite::create(IMG_SIGNIN_EVERYDAY_CELL_BG);
//    cellSize.height=headBox->getContentSize().height-4;
//    cellSize.width=headBox->getContentSize().width;
    
    
}
void MoneyDrawing::setLuckytime()
{
    
    string todaytime = StringUtils::format("%d",m_totalCount);
    todaytime = todaytime + "次";
    Label* todaytimeLabel = (Label*)this->getChildByTag(TAG_TODAYTIME);
    if (todaytimeLabel) {
        todaytimeLabel->setString(todaytime);
    }else{
        todaytimeLabel = PublicShowUI::getLabel(todaytime.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),30,false,false);
        todaytimeLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(todaytimeLabel);
        this->addChild(todaytimeLabel,5,TAG_TODAYTIME);
    }
    todaytimeLabel->setPosition(795*sx, 425*sx);
    
    
    string alltodaytime = StringUtils::format("%d/%d",m_todayCount,m_todayTotalCount);
    Label* alltodaytimeLabel = (Label*)this->getChildByTag(TAG_ALLTODAY);
    if (alltodaytimeLabel) {
        alltodaytimeLabel->setString(alltodaytime);
    }else{
        alltodaytimeLabel = PublicShowUI::getLabel(alltodaytime.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),26,false,false);
        alltodaytimeLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(alltodaytimeLabel);
        this->addChild(alltodaytimeLabel,5,TAG_ALLTODAY);
    }
    alltodaytimeLabel->setPosition(590*sx,50*sx);
    
    if(m_status == 1)
    {
        this->removeChildByTag(TAG_DAOJISHI);
        this->removeChildByTag(TAG_RECUITIME);
    }else if(m_status == 2)
    {
        this->removeChildByTag(TAG_DAOJISHI);
        this->removeChildByTag(TAG_RECUITIME);
        
        string recuittimeword = "下次祈福倒计时：";
        Label* labelword = PublicShowUI::getLabel(recuittimeword.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,false);
        labelword->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(labelword);
        labelword->setPosition(435*sx,20*sx);
        this->addChild(labelword,10,TAG_DAOJISHI);
        
        string recuittime=StringUtils::format("%02ld:%02ld:%02ld",m_remainingTimes/3600, m_remainingTimes%3600/60,m_remainingTimes%60);
        label = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,false);
        label->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(label);
        this->addChild(label,10,TAG_RECUITIME);
        label->setPosition(labelword->getPositionX()+labelword->getContentSize().width,20*sx);
        schedule(schedule_selector(MoneyDrawing::update2),1);
        
    }else if (m_status == 3)
    {
        this->removeChildByTag(TAG_DAOJISHI);
        this->removeChildByTag(TAG_RECUITIME);
        
        string recuittimeword = "今日祈福次数已用尽，请明日再来";
        Label* labelword = PublicShowUI::getLabel(recuittimeword.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,false);
        labelword->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(labelword);
        labelword->setPosition(420*sx,20*sx);
        this->addChild(labelword,10,TAG_DAOJISHI);
    }
}

void MoneyDrawing::update2(float delta)
{
    m_remainingTimes -= 1;
    if (m_remainingTimes <= 0){
        m_remainingTimes =0;
        unschedule(schedule_selector(MoneyDrawing::update2));
        requestLuckyMsg();
        return;
    }
    char*mtime = new char[10];
    //显示小时，分钟，秒
    sprintf(mtime,"%02ld:%02ld:%02ld",m_remainingTimes/3600, m_remainingTimes%3600/60,m_remainingTimes%60);
    label->setString(mtime);
}

void MoneyDrawing::onPersonClick(Ref* pSender)
{
    

    if (m_status == 1)
    {
        requestItemGiftMsg();
    }else if (m_status == 2 && m_totalCount != 7)
    {
        NoticeManager::getInstance()->showNotice("两次祈福间隔太短，请稍后继续");
        return;
    }else if (m_status == 3)
    {
        NoticeManager::getInstance()->showNotice("今日祈福已次数已用尽，请明日再来");
        return;
    }else{
        requestItemGiftMsg();
    }
    
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumPrayerButton);
}

void MoneyDrawing::onseeClick(Ref* pSender)
{
    if (m_status == 1 && m_totalCount != 7) {
        NoticeManager::getInstance()->showNotice("祈福之后才可以查看");
        return;
    }
    requestItemGiftMsg();
}
void MoneyDrawing::removeEventListener()
{
    BaseLayer::removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumPrayerButton);
}

void MoneyDrawing::requestLuckyMsg()//请求
{
    Dialog::showServerLoading();
    SigninLuckyMsg* msg = new SigninLuckyMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MoneyDrawing::onLuckyMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_LUCKY_LuckyPageResp)
    {
        if(message->state)//返回成功
        {
            m_totalCount = message->byteStream->getByte();
            m_todayCount = message->byteStream->getByte();
            m_todayTotalCount = message->byteStream->getByte();
            m_status = message->byteStream->getByte();
            m_remainingTimes = message->byteStream->getInt();
            setLuckytime();
        }
    }
}
void MoneyDrawing::requestItemGiftMsg()//请求祈福
{
    Dialog::showServerLoading();
    SiginLuckyStartMsg* msg = new SiginLuckyStartMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MoneyDrawing::onItemGiftMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    MoneyDrawingDataManager::getInstance()->cleargiftList();
    if(message->messageID == SCENSE_CLIENT_LUCKY_LuckyGoResp)
    {
        if(message->state)//返回成功
        {
            int gifsize = message->byteStream->getByte();
            for (int i = 0; i<gifsize; i++) {
                MoneyDrawingData* data = new MoneyDrawingData;
                data->autorelease();
                
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemCount = message->byteStream->getByte();
                data->itemQuality = message->byteStream->getByte();
                data->itemName = message->byteStream->getUTF8();
                string labelcount = StringUtils::format("%d",data->itemCount);
                broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumLucky));
            }
            
            int canReceive = message->byteStream->getByte();
            int totalRewardSize = message->byteStream->getByte();
            for (int i = 0; i<totalRewardSize; i++) {
                MoneyDrawingData* data = new MoneyDrawingData;
                data->autorelease();
                
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemCount = message->byteStream->getByte();
                data->itemQuality = message->byteStream->getByte();
                data->itemName = message->byteStream->getUTF8();
                MoneyDrawingDataManager::getInstance()->addData(data);
                
            }
            if(gifsize<=0)
            {
                MoneyDrawingGiftLayer::show(canReceive);
            }
            
            requestLuckyMsg();

        }
    }
}

void MoneyDrawing::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LUCKY_LuckyPageResp).c_str(), CC_CALLBACK_1(MoneyDrawing::onLuckyMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LUCKY_LuckyGoResp).c_str(), CC_CALLBACK_1(MoneyDrawing::onItemGiftMsgProcess, this));
}

