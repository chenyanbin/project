//
//  HalfPriceLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/13.
//
//

#include "HalfPriceLayer.hpp"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../protocol/Protocal.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/sevenday/WeekHalfPageMsg.h"
#include "../../../message/Decoding/sevenday/WeekHalfBuyMsg.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../sevendayData/HalfPriceDataManager.hpp"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../tips/TipsLayer.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../protocol/UserCustomEvent.h"
HalfPriceLayer::HalfPriceLayer()
:m_day(1)
,sx(0)
,TAG_BUYBTN(2)
{
    
    
}

HalfPriceLayer:: ~ HalfPriceLayer()
{
    
}

bool HalfPriceLayer::init(int day)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        sx = GlobalInfo::getInstance()->screenScaleX;
        this->isAnimation = false;
        m_day = day;
        this->setBackground();
        
        
        bref = true;
    } while (false);
    return bref;
}

HalfPriceLayer* HalfPriceLayer::create(int day)
{
    HalfPriceLayer* list = new HalfPriceLayer();
    if(list && list->init(day))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void HalfPriceLayer::onEnter()
{
    BaseLayer::onEnter();
}
void HalfPriceLayer::onExit()
{
    BaseLayer::onExit();
}
void HalfPriceLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestWeekHalfPricePage(m_day);
    
}
void HalfPriceLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void HalfPriceLayer::setBackground()
{
    Sprite* layerBg = Sprite::create(IMG_SEVEENDAY_HALFPRIVEBG);
    layerBg->setAnchorPoint(Point::ZERO);
    layerBg->setPosition(Point::ZERO);
    this->addChild(layerBg);
    
    Size size = layerBg->getContentSize();
    this->setContentSize(size);
}
void HalfPriceLayer::sethalfPrive()
{
    if (HalfPriceDataManager::getInstance()->halfpriceList->size()<1) {
        return;
    }
    HalfPriceData* data = HalfPriceDataManager::getInstance()->halfpriceList->at(0);
    
    //现价
    string timesStr=StringUtils::format("%d",data->price);
    timesStr = timesStr + "元宝";
    Label* timesLabel = PublicShowUI::getLabel(timesStr.c_str(),PublicShowUI::getColor3b(COLOR_BLACK_BROWN),24,false,false);
    timesLabel->setAnchorPoint(Point::ZERO);
    this->addChild(timesLabel,10);
    timesLabel->setPosition(110,65);
    
    //原价
    string oleStr=StringUtils::format("%d",data->priceOri);
    oleStr = oleStr + "元宝";
    Label* oldpriceLabel = PublicShowUI::getLabel(oleStr.c_str(),PublicShowUI::getColor3b(COLOR_BLACK_BROWN),24,false,false);
    oldpriceLabel->setAnchorPoint(Point::ZERO);
    this->addChild(oldpriceLabel,10);
    oldpriceLabel->setPosition(290,45);
    Sprite* line = Sprite::create(IMG_VIP_LIBAO_LINE);
    line->setAnchorPoint(Point::ZERO);
    line->setPosition(oldpriceLabel->getPositionX()-20, oldpriceLabel->getPositionY()+5);
    this->addChild(line,15);
    
//    //购买人数
//    string allPerStr=StringUtils::format("%d",data->sellCount);
//    Label* allPerLabel = PublicShowUI::getLabel(allPerStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),24,false,false);
//    allPerLabel->setAnchorPoint(Point::ZERO);
//    this->addChild(allPerLabel,10);
//    allPerLabel->setPosition(90,37);
//    
//    //购买人数
//    string perStr=StringUtils::format("%d",data->selledCount);
//    Label* perLabel = PublicShowUI::getLabel(perStr.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),24,false,false);
//    perLabel->setAnchorPoint(Point::ZERO);
//    this->addChild(perLabel,10);
//    perLabel->setPosition(330,35);
    
    int m_quality = data->itemQuality;
    if (m_quality == 0)
    {
        m_quality = 1;
    }
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
        UserHeadLayer* userHead=UserHeadLayer::create(resource,m_quality,false);
        userHead->setHeadInfo(1, 1);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setPosition(445,170);
        this->addChild(userHead,2);
        userHead->addTouchBegainCallBack(this, callfuncN_selector(HalfPriceLayer::onhalfitemClick));
        
    }
    else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType ==DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
    {
        const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
        UserEquipLayer* head = UserEquipLayer::create(resource,m_quality,false);
        head->setAnchorPoint(Point::ZERO);
        if (data->itemType == 4) {
            head->setFragment();
        }else if (data->itemType == 3)
        {
            head->setLetterFragment();
        }
        head->setPosition(445,170);
        this->addChild(head,2);
        head->addTouchBegainCallBack(this, callfuncN_selector(HalfPriceLayer::onhalfitemClick));
    }
    
    string namestr = data->itemName;
    namestr = namestr + "x" + PublicShowUI::numberToString(data->itemCount);
    Label* nameLabel = PublicShowUI::getLabel(namestr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    nameLabel->setAnchorPoint(Point(0.5,0));
    this->addChild(nameLabel,20);
    nameLabel->setPosition(500,140);
    
    
    if (data->status == 1) {
        Button* buybtn = Button::create(IMG_BUTTON_REDBTN, IMG_BUTTON_REDBTN, CC_CALLBACK_1(HalfPriceLayer::onBuyClick, this));
        buybtn->setAnchorPoint(Point::ZERO);
        buybtn->setPosition(440,40);
        this->addChild(buybtn,2,TAG_BUYBTN);
        Sprite* buyspr = Sprite::create(IMG_PUBLIC_LABEL_BUYWORD);
        buyspr->setAnchorPoint(Point::ZERO);
        buyspr->setPosition(Point::ZERO);
        buybtn->addChild(buyspr,5);
        PublicShowUI::setDot(buybtn,Point::ZERO,false,DictFunctionEnumSevenDay);
        
    }else if(data->status == 2){
        string  str = "已购买";
        Label* strLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_BLUE),26,false,false);
        strLabel->setAnchorPoint(Point::ZERO);
        strLabel->setPosition(460,60);
        this->addChild(strLabel,20);
    }
    else if(data->status == 3){
        string  str = "已售完";
        Label* strLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_BLUE),26,false,false);
        strLabel->setAnchorPoint(Point::ZERO);
        strLabel->setPosition(460,60);
        this->addChild(strLabel,20);
    }
    
    
}
void HalfPriceLayer::onBuyClick(Ref* pSender)
{
    if(HalfPriceDataManager::getInstance()->halfpriceList->at(0)->status == 2)
    {
        NoticeManager::getInstance()->showNotice("已购买");
        return;
    }
    if (GlobalInfo::getInstance()->userGold < HalfPriceDataManager::getInstance()->halfpriceList->at(0)->price) {
        NoticeManager::getInstance()->showNotice("元宝不足，不可购买");
    }else{
        requesthalfBuyMsg(m_day);
    }
}
void HalfPriceLayer::onhalfitemClick(Node* pSender)
{
    HalfPriceData* data = HalfPriceDataManager::getInstance()->halfpriceList->at(0);
    TipsLayer::show(data->itemType, data->itemId, data->itemCount);
}


/*-----------------------------------------连接服务器------------------------------------------- */
void HalfPriceLayer::requestWeekHalfPricePage(int _day)//第几天半价商品内容
{
    Dialog::showServerLoading();
    WeekHalfPageMsg* msg = new WeekHalfPageMsg(_day);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void HalfPriceLayer::onWeekHalfPriceProcess(EventCustom* msg)
{
        Dialog::hideServerLoading();
        MessageReceive* message = (MessageReceive*)msg->getUserData();
        HalfPriceDataManager::getInstance()->clearhalfpriceList();
        if(message->messageID == SCENSE_CLIENT_WEEK_WeekHalfPageResp)
        {
            if(message->state)//返回成功
            {
                HalfPriceData* data = new HalfPriceData();
                data->autorelease();
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemCount = message->byteStream->getInt();
                data->itemName = message->byteStream->getUTF8();
                data->itemDesc = message->byteStream->getUTF8();
                data->itemQuality = message->byteStream->getByte();
                data->status = message->byteStream->getByte();
                data->priceOri = message->byteStream->getInt();
                data->price = message->byteStream->getInt();
                data->sellCount = message->byteStream->getInt();
                data->selledCount = message->byteStream->getInt();
                HalfPriceDataManager::getInstance()->addData(data);
                
                sethalfPrive();
            }
        }
}
void HalfPriceLayer::requesthalfBuyMsg(int _day)//q请求半价购买领取奖励
{
    Dialog::showServerLoading();
    WeekHalfBuyMsg* msg = new WeekHalfBuyMsg(_day);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void HalfPriceLayer::onhalfBuyProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekHalfBuyResp)
    {
        if(message->state)//返回成功
        {
            NoticeManager::getInstance()->showNotice("购买成功");
        }
        HalfPriceDataManager::getInstance()->halfpriceList->at(0)->status = 2;
        
        
        Vector<BaseTypeData*> *m_basegift = new Vector<BaseTypeData*>();
        m_basegift->clear();
        
        HalfPriceData* data =  HalfPriceDataManager::getInstance()->halfpriceList->at(0);
        BaseTypeData* basedata = new BaseTypeData();
        basedata->autorelease();
        basedata->dataId = data->itemId;
        basedata->dataName = data->itemName;// itemName;
        basedata->dataType = data->itemType;
        basedata->dataQuality = data->itemQuality;
        basedata->dataCount = data->itemCount;
        m_basegift->pushBack(basedata);
        
        AwardBox_Layer* layer=AwardBox_Layer::create(m_basegift);
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
        Scene* scene=Director::getInstance()->getRunningScene();
        scene->addChild(layer);
        Button* buybtn = (Button*)this->getChildByTag(TAG_BUYBTN);
        if (buybtn) {
            buybtn->removeFromParent();
        }
        
        string  str = "已购买";
        Label* strLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_BLUE),26,false,false);
        strLabel->setAnchorPoint(Point::ZERO);
        strLabel->setPosition(460,60);
        this->addChild(strLabel,20);
        broadMsg(CUSTOM_SEVENDAY_REDPOINT);
    }
    
}

void HalfPriceLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekHalfPageResp).c_str(), CC_CALLBACK_1(HalfPriceLayer::onWeekHalfPriceProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekHalfBuyResp).c_str(), CC_CALLBACK_1(HalfPriceLayer::onhalfBuyProcess, this));
}
void HalfPriceLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
