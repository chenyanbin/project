//
//  SevenActivity_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/19.
//
//

#include "SevenActivity_Layer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../protocol/UserCustomEvent.h"
//#include "../Signin_Scene.h"
#include "SevenDayGiftLayer.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../protocol/Protocal.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/sevenday/WeekOpenDayMsg.h"
#include "weekrewarddata/WeekRewardPageDatamanager.h"
#include "../../../message/Decoding/sevenday/WeekRewardPageMsg.h"
#include "../../../message/Decoding/sevenday/WeekHalfPageMsg.h"
#include "weekrewarddata/WeekHalfGiftDataManager.h"
#include "../../../common/noticeManager/NoticeManager.h"
SevenActivity_Layer::SevenActivity_Layer()
:sx(1)
,TAG_SEVENDAY(10)
,TAG_BOXBTN(11)
,m_day(1)
{
    
}
SevenActivity_Layer::~SevenActivity_Layer()
{
    WeekRewardPageDatamanager::getInstance()->destroyInstance();
    WeekHalfGiftDataManager::getInstance()->destroyInstance();
}

void SevenActivity_Layer::onExit()//
{
    BaseLayer::onExit();
}
void SevenActivity_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void SevenActivity_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    
    
}
void SevenActivity_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestWeekDayMsg();
}
bool SevenActivity_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_GENERALS_SEVENACTIVITY_BG);
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
SevenActivity_Layer* SevenActivity_Layer::create()
{
    SevenActivity_Layer* layer = new SevenActivity_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void SevenActivity_Layer::createLayer()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    
//    Sprite* bg2=Sprite::create(IMG_GENERALS_SEVENACTIVITY_BG2);
//    bg2->setAnchorPoint(Point::ZERO);
//    bg2->setPosition(13,20);
//    bg->addChild(bg2,1);
    
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(SevenActivity_Layer::onComboBoxBtnClick, this),ComboBoxBtn::ALIGN::ALIGN_UP);
    for (int i = 0; i<7; i++) {
        char stt[100]="";
        sprintf(stt,IMG_GENERALS_SEVENACTIVITY_DAY,i+1);
        if (i==6) {
            boxBtn->addBtn(IMG_GENERALS_SEVENACTIVITY_SEVENDAYBG1, IMG_GENERALS_SEVENACTIVITY_SEVENDAYBG2, stt);
        }else
        {
            boxBtn->addBtn(IMG_GENERALS_SEVENACTIVITY_DAYBG1, IMG_GENERALS_SEVENACTIVITY_DAYBG2, stt);
        }
        
    }
    boxBtn->setPosition(20,390);
    bg->addChild(boxBtn,2,TAG_BOXBTN);
}
void SevenActivity_Layer::onComboBoxBtnClick(Ref* psender)
{
    if(m_day == -1)
    {
        return;
    }
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    if (tag+1>m_day) {
        ComboBoxBtn* boxBtn = (ComboBoxBtn*)this->getChildByTag(TAG_BG)->getChildByTag(TAG_BOXBTN);
        if (boxBtn) {
            boxBtn->resetAllBtn();
            boxBtn->getButtonAt(m_someDay-1)->selected();
            NoticeManager::getInstance()->showNotice("未开启");
        }
        return;
    }
    m_someDay = tag+1;
    requestWeekRewardPage(tag+1);
    requestWeekHalfPricePage(tag+1);
    
}

//-----------------------------------------------------------访问服务器-------------------------------------------------------//

void SevenActivity_Layer::requestWeekDayMsg()//第几天
{
    Dialog::showServerLoading();
    WeekOpenDayMsg* msg = new WeekOpenDayMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void SevenActivity_Layer::onWeekDayMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekOpenDayResp)
    {
        if(message->state)//返回成功
        {
            m_day = message->byteStream->getByte();
            if (m_day < 1) {
                NoticeManager::getInstance()->showNotice("活动已结束");
                return;
            }
            m_someDay = m_day;
            ComboBoxBtn* boxBtn = (ComboBoxBtn*)this->getChildByTag(TAG_BG)->getChildByTag(TAG_BOXBTN);
            if (boxBtn) {
                 boxBtn->getButtonAt(m_someDay-1)->selected();
            }
            requestWeekRewardPage(m_someDay);
            requestWeekHalfPricePage(m_someDay);
        }
    }
    
}

void SevenActivity_Layer::requestWeekRewardPage(int _day)//第几天内容
{
    Dialog::showServerLoading();
    WeekRewardPageMsg* msg = new WeekRewardPageMsg(_day);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void SevenActivity_Layer::onWeekRewardProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    WeekRewardPageDatamanager::getInstance()->clearMailList();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekRewardPageResp)
    {
        if(message->state)//返回成功
        {
            //免费获得
            WeekDescData* datadesc1 = new WeekDescData;
            datadesc1->autorelease();
            datadesc1->rewardType = 1;
            datadesc1->status = message->byteStream->getByte();
            int targetValue = message->byteStream->getInt();
            datadesc1->desc ="免费领取";
            WeekRewardPageDatamanager::getInstance()->adddescData(datadesc1);
            
            int chargeSize = message->byteStream->getByte();
            for (int i = 0; i < chargeSize; i ++)
            {
                WeekRewardData* data = new WeekRewardData;
                data->autorelease();
                data->rewardType = 1;
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemCount = message->byteStream->getShort();
                data->itemName = message->byteStream->getUTF8();
                data->itemDesc = message->byteStream->getUTF8();
                data->itemQuality = message->byteStream->getByte();
                WeekRewardPageDatamanager::getInstance()->addData(data);
            }
            //充值领取
            WeekDescData* datadesc2 = new WeekDescData;
            datadesc2->autorelease();
            datadesc2->rewardType = 2;
            datadesc2->status = message->byteStream->getByte();
            int freeValue = message->byteStream->getInt();
            datadesc2->desc = StringUtils::format("充值%dRMB即可领取",freeValue);
            WeekRewardPageDatamanager::getInstance()->adddescData(datadesc2);
            int freeSize = message->byteStream->getByte();
            for (int i = 0; i < freeSize; i ++)
            {
                WeekRewardData* data = new WeekRewardData;
                data->autorelease();
                data->rewardType = 2;
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemCount = message->byteStream->getShort();
                data->itemName = message->byteStream->getUTF8();
                data->itemDesc = message->byteStream->getUTF8();
                data->itemQuality = message->byteStream->getByte();
                WeekRewardPageDatamanager::getInstance()->addData(data);
            }
            //花费元宝领取
            WeekDescData* datadesc3 = new WeekDescData;
            datadesc3->autorelease();
            datadesc3->rewardType = 3;
            datadesc3->status = message->byteStream->getByte();
            int glodCount = message->byteStream->getInt();
            datadesc3->desc =StringUtils::format("花费%d元宝即可领取",glodCount);
            WeekRewardPageDatamanager::getInstance()->adddescData(datadesc3);
            int goldSize = message->byteStream->getByte();
            for (int i = 0; i < goldSize; i ++)
            {
                WeekRewardData* data = new WeekRewardData;
                data->autorelease();
                data->rewardType = 3;
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemCount = message->byteStream->getShort();
                data->itemName = message->byteStream->getUTF8();
                data->itemDesc = message->byteStream->getUTF8();
                data->itemQuality = message->byteStream->getByte();
                WeekRewardPageDatamanager::getInstance()->addData(data);
            }
            //任务
            int tastsize = message->byteStream->getByte();
            for (int i = 0; i < tastsize; i ++)
            {
                WeekDescData* datadesc = new WeekDescData;
                datadesc->autorelease();
                datadesc->rewardType = i+4;
                datadesc->desc = message->byteStream->getUTF8();
                datadesc->status = message->byteStream->getByte();
                WeekRewardPageDatamanager::getInstance()->adddescData(datadesc);
                int rewardSize = message->byteStream->getByte();
                for (int j = 0; j<rewardSize; j++) {
                    WeekRewardData* data = new WeekRewardData;
                    data->autorelease();
                    data->rewardType = i+4; 
                    data->itemType = message->byteStream->getByte();
                    data->itemId = message->byteStream->getInt();
                    data->itemCount = message->byteStream->getShort();
                    data->itemName = message->byteStream->getUTF8();
                    data->itemDesc = message->byteStream->getUTF8();
                    data->itemQuality = message->byteStream->getByte();
                    WeekRewardPageDatamanager::getInstance()->addData(data);
                }
            }
            this->removeChildByTag(TAG_SEVENDAY);
            SevenDayGiftLayer* layer = SevenDayGiftLayer::create(m_someDay);
            layer->setAnchorPoint(Point::ZERO);
            layer->setPosition(20,20);
            this->addChild(layer,1,TAG_SEVENDAY);
        }
        
    }
        
}

void SevenActivity_Layer::requestWeekHalfPricePage(int _day)//第几天半价商品内容
{
    Dialog::showServerLoading();
    WeekHalfPageMsg* msg = new WeekHalfPageMsg(_day);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void SevenActivity_Layer::onWeekHalfPriceProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    WeekHalfGiftDataManager::getInstance()->clearhalfpriceList();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekHalfPageResp)
    {
        if(message->state)//返回成功
        {
            WeekHalfGiftData* data = new WeekHalfGiftData;
            data->autorelease();
            data->itemType = message->byteStream->getByte();
            data->itemId = message->byteStream->getInt();
            data->itemCount = message->byteStream->getShort();
            data->itemName = message->byteStream->getUTF8();
            data->itemDesc = message->byteStream->getUTF8();
            data->itemQuality = message->byteStream->getByte();
            data->status = message->byteStream->getByte();
            data->priceOri = message->byteStream->getInt();
            data->price = message->byteStream->getInt();
            data->sellCount = message->byteStream->getInt();
            data->selledCount = message->byteStream->getInt();
            WeekHalfGiftDataManager::getInstance()->addData(data);
        }
    }
}


void SevenActivity_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekOpenDayResp).c_str(), CC_CALLBACK_1(SevenActivity_Layer::onWeekDayMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekRewardPageResp).c_str(), CC_CALLBACK_1(SevenActivity_Layer::onWeekRewardProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekHalfPageResp).c_str(), CC_CALLBACK_1(SevenActivity_Layer::onWeekHalfPriceProcess, this));
}

