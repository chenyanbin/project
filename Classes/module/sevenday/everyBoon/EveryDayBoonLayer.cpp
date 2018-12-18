//
//  EveryDayBoonLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/13.
//
//

#include "EveryDayBoonLayer.hpp"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../protocol/Protocal.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/sevenday/WeekOpenDayMsg.h"
#include "../../../message/Decoding/sevenday/WeekRewardPageMsg.h"
#include "../../../message/Decoding/sevenday/WeekHalfPageMsg.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../sevendayData/BoonDataManager.hpp"
#include "../../userWealth/UserEquipLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../tips/TipsLayer.h"
#include "ChoseHeroLayer.hpp"
#include "../../../message/Decoding/sevenday/WeekReceiveMsg.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../data/BaseTypeData.h"
#include "../../vip/VipLayer.h"
EveryDayBoonLayer::EveryDayBoonLayer()
:m_day(1)
,sx(0)
,TAG_FREEBTN(10)
,TAG_GLODBTN(11)
,m_freeStatus(2)
,m_glodStatus(3)
,m_numhero(1)
{
    
    
}

EveryDayBoonLayer:: ~ EveryDayBoonLayer()
{
    
}

bool EveryDayBoonLayer::init(int day)
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

EveryDayBoonLayer* EveryDayBoonLayer::create(int day)
{
    EveryDayBoonLayer* list = new EveryDayBoonLayer();
    if(list && list->init(day))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void EveryDayBoonLayer::onEnter()
{
    BaseLayer::onEnter();
}
void EveryDayBoonLayer::onExit()
{
    BaseLayer::onExit();
}
void EveryDayBoonLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestWeekRewardPage(m_day);
    
}
void EveryDayBoonLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->removeEventListener();
}
void EveryDayBoonLayer::setBackground()
{
    Sprite* layerBg = Sprite::create(IMG_SEVEENDAY_EVERYBOON);
    layerBg->setAnchorPoint(Point::ZERO);
    layerBg->setPosition(Point::ZERO);
    this->addChild(layerBg);
    
    Size size = layerBg->getContentSize();
    this->setContentSize(size);
}
void EveryDayBoonLayer::setItemPrice()
{
   
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    size_t len = BoonDataManager::getInstance()->rewardlList->size();
    int m_tagfree = 0;
    int m_tagglod = 0;
    const char* resource = "";
    UserEquipLayer* head = NULL;
    UserHeadLayer* userHead = NULL;
    for (int i = 0; i<len; i++)
    {
            BoonData* data = BoonDataManager::getInstance()->rewardlList->at(i);
            int m_quality = data->itemQuality;
            if (m_quality == 0)
            {
                m_quality = 1;
            }
            
            if(  data->itemType == DictItemTypeEnumItemHero)
            {
                resource = PublicShowUI::getGoods(data->itemType, data->itemId);
                userHead=UserHeadLayer::create(resource,m_quality,false);
                userHead->setHeadInfo(1, 3);
                userHead->setAnchorPoint(Point::ZERO);
                userHead->setScale(0.6);
                node->addChild(userHead,2,i);
                userHead->addTouchBegainCallBack(this, callfuncN_selector(EveryDayBoonLayer::onitemClick));
                if (data->rewardType == 0) {
                    userHead->setPosition(100 + m_tagfree*(userHead->getContentSize().width-10),140);
                    m_tagfree ++;
                }else{
                    userHead->setPosition(100 + m_tagglod*(userHead->getContentSize().width-10),30);
                    m_tagglod ++;
                }
                
            }
            else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType ==DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
            {
                resource = PublicShowUI::getGoods(data->itemType, data->itemId);
                head = UserEquipLayer::create(resource,m_quality,false);
                head->setAnchorPoint(Point::ZERO);
                if (data->itemType == 4) {
                    head->setFragment();
                }else if (data->itemType == 3)
                {
                    head->setLetterFragment();
                }
                head->setScale(0.6);
                node->addChild(head,2,i);
                head->addTouchBegainCallBack(this, callfuncN_selector(EveryDayBoonLayer::onitemClick));
                if (data->rewardType == 0) {
                    head->setPosition(95 + m_tagfree*(head->getContentSize().width-10),135);
                    m_tagfree ++;
                }else{
                    head->setPosition(95 + m_tagglod*(head->getContentSize().width-10),25);
                    m_tagglod ++;
                }
                
            }
            
            string countstr = StringUtils::format("x%d",data->itemCount);
            Label* countLabel = PublicShowUI::getLabel(countstr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),16,false,false);
            countLabel->setAnchorPoint(Point::ZERO);
            node->addChild(countLabel,20);
            if (head) {
                if (data->rewardType == 0) {
                    countLabel->setPosition(172+(m_tagfree-1) * (head->getContentSize().width-12),140);
                }else{
                    countLabel->setPosition(172+(m_tagglod-1) * (head->getContentSize().width-12),30);
                }
            }else{
                if (data->rewardType == 0) {
                    countLabel->setPosition(172+(m_tagfree-1) * (userHead->getContentSize().width-12),140);
                }else{
                    countLabel->setPosition(172+(m_tagglod-1) * (userHead->getContentSize().width-12),30);
                }
                
            }
    }
    this->addChild(node,3);

}
void EveryDayBoonLayer::onitemClick(Node* pSender)
{
    BoonData* data = BoonDataManager::getInstance()->rewardlList->at(pSender->getTag());
    TipsLayer::show(data->itemType, data->itemId, data->itemCount);
}
void EveryDayBoonLayer::setMoney()
{
    WeekDescData* data = BoonDataManager::getInstance()->desclList->at(1);
    string countstr = StringUtils::format("%d",data->targetValue);
    Label* countLabel = PublicShowUI::getLabel(countstr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),16,false,false);
    countLabel->setAnchorPoint(Point::ZERO);
    countLabel->setPosition(172,105);
    this->addChild(countLabel);
    
    
    countstr = StringUtils::format("%d/%d",data->finishValue,data->targetValue);
    Label* countLabelall = PublicShowUI::getLabel(countstr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),16,false,false);
    countLabelall->setAnchorPoint(Point::ZERO);
    countLabelall->setPosition(400,105);
    this->addChild(countLabelall);
}
void EveryDayBoonLayer::setBg()
{
    Button* btn = (Button*)this->getChildByTag(TAG_FREEBTN);
    if (btn) {
        btn->removeFromParent();
    }
    Button* btnglod = (Button*)this->getChildByTag(TAG_GLODBTN);
    if (btnglod) {
        btnglod->removeFromParent();
    }
    m_freeStatus = BoonDataManager::getInstance()->desclList->at(0)->status;
    m_glodStatus = BoonDataManager::getInstance()->desclList->at(1)->status;
    Button* freeBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(EveryDayBoonLayer::onClick, this));
    freeBtn->setAnchorPoint(Point::ZERO);
    freeBtn->setPosition(this->getContentSize().width/2-freeBtn->getContentSize().width/2 + 160,this->getContentSize().height/2-freeBtn->getContentSize().height/2-20);
    this->addChild(freeBtn,1,TAG_FREEBTN);
    if(m_freeStatus == 1){
        Sprite* freeGlod = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
        freeGlod->setAnchorPoint(Point::ZERO);
        freeGlod->setPosition(Point::ZERO);
        freeBtn->addChild(freeGlod,5);
        PublicShowUI::setDot(freeGlod,Point::ZERO,false,DictFunctionEnumSevenDay);
    }
    else if(m_freeStatus == 2)
    {
        Sprite* freeGlod = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
        freeGlod->setAnchorPoint(Point::ZERO);
        freeGlod->setPosition(Point::ZERO);
        freeBtn->addChild(freeGlod,5);
        freeBtn->setEnabled(false);
    }else{
        Sprite* freeGlod = Sprite::create(IMG_PUBLIC_LABEL_ISLINGQU);
        freeGlod->setAnchorPoint(Point::ZERO);
        freeGlod->setPosition(Point::ZERO);
        freeBtn->addChild(freeGlod,5);
        freeBtn->setEnabled(false);
    }
    
    if(m_glodStatus == 1 || m_glodStatus == 3)
    {
        Button* glodBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(EveryDayBoonLayer::onGoldClick, this));
        glodBtn->setAnchorPoint(Point::ZERO);
        glodBtn->setPosition(freeBtn->getPositionX(),freeBtn->getPositionY() - glodBtn->getContentSize().height - 80);
        this->addChild(glodBtn,1,TAG_GLODBTN);
        if(m_glodStatus == 1){
            Sprite* sprglod = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
            sprglod->setAnchorPoint(Point::ZERO);
            sprglod->setPosition(Point::ZERO);
            glodBtn->addChild(sprglod,5);
            PublicShowUI::setDot(sprglod,Point::ZERO,false,DictFunctionEnumSevenDay);
        }
        else if(m_glodStatus == 3)
        {
            Sprite* sprglod = Sprite::create(IMG_PUBLIC_LABEL_ISLINGQU);
            sprglod->setAnchorPoint(Point::ZERO);
            sprglod->setPosition(Point::ZERO);
            glodBtn->addChild(sprglod,5);
            glodBtn->setEnabled(false);
        }
    }else if (m_glodStatus == 2)
    {
        Button* glodBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_RED, IMG_PUBLIC_BUTTON_TWO_RED, CC_CALLBACK_1(EveryDayBoonLayer::onChargeClick, this));
        glodBtn->setAnchorPoint(Point::ZERO);
        glodBtn->setPosition(freeBtn->getPositionX(),freeBtn->getPositionY() - glodBtn->getContentSize().height - 80);
        this->addChild(glodBtn,1);
        Sprite* sprglod = Sprite::create(IMG_PUBLIC_LABEL_RECHARGE);
        sprglod->setAnchorPoint(Point::ZERO);
        sprglod->setPosition(Point::ZERO);
        glodBtn->addChild(sprglod,5);
    }
    
}

void EveryDayBoonLayer::onClick(Ref* pSender)//免费领取
{
    m_type = 0;
    if (m_day == 7) {
        ChoseHeroLayer::show(0);
    }else{
        requestBoonRewardMsg(m_day,2,0,m_numhero);
    }
}
void EveryDayBoonLayer::onGoldClick(Ref* pSender)//chonghi领取
{
    m_type = 1;
    requestBoonRewardMsg(m_day,1,0,m_numhero);
}

void EveryDayBoonLayer::onChargeClick(Ref* pSender)//前往充值
{
    VipLayer::show(SCENE_TAG_MAINUI);
}

void EveryDayBoonLayer::onChoseHeroProcess(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_numhero = inter->getValue();
    requestBoonRewardMsg(m_day,2,0,m_numhero);
}

/*----------------------------------------------访问服务器--------------------------------------*/
void EveryDayBoonLayer::requestWeekRewardPage(int _day)//第几天内容
{
    Dialog::showServerLoading();
    WeekRewardPageMsg* msg = new WeekRewardPageMsg(_day);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void EveryDayBoonLayer::onWeekRewardProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekRewardPageResp)
    {
        if(message->state)//返回成功
        {
            BoonDataManager::getInstance()->clearMailList();
            for (int i = 0; i < 2; i ++)
            {
                WeekDescData* datadesc = new WeekDescData;
                datadesc->autorelease();
                datadesc->status = message->byteStream->getByte();
                datadesc->targetValue = message->byteStream->getInt();
                datadesc->finishValue = message->byteStream->getInt();
                BoonDataManager::getInstance()->adddescData(datadesc);
                int rewardSize = message->byteStream->getByte();
                for (int j = 0; j<rewardSize; j++) {
                    BoonData* data = new BoonData;
                    data->autorelease();
                    data->rewardType = i;
                    data->itemType = message->byteStream->getByte();
                    data->itemId = message->byteStream->getInt();
                    data->itemCount = message->byteStream->getInt();
                    data->itemName = message->byteStream->getUTF8();
                    data->itemDesc = message->byteStream->getUTF8();
                    data->itemQuality = message->byteStream->getByte();
                    BoonDataManager::getInstance()->addData(data);
                }
            }
            setBg();
            setItemPrice();
            setMoney();
        }
        
    }

}

void EveryDayBoonLayer::requestBoonRewardMsg(int _day, int _type, int _numPrice, int _numHero)//q请求领取奖励
{
    Dialog::showServerLoading();
    WeekReceiveMsg* msg = new WeekReceiveMsg(_day, _type, _numPrice, _numHero);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void EveryDayBoonLayer::onBoonDayRewardMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekReceiveResp)
    {
        if(message->state)//返回成功
        {
            
            Vector<BaseTypeData*> *m_basegift = new Vector<BaseTypeData*>();
            m_basegift->clear();
            size_t len = BoonDataManager::getInstance()->rewardlList->size();
            for (int i = 0; i<len; i++) {
                BoonData* data =  BoonDataManager::getInstance()->rewardlList->at(i);
                if (data->rewardType == m_type) {
                    if (m_day == 7 && data->rewardType == 0) {
                        if (m_numhero == 1)
                        {
                            m_numhero = i+100;
                        }
                        else if (m_numhero == 2)
                        {
                            m_numhero = i+101;
                        }
                        else if (m_numhero == 3)
                        {
                            m_numhero = i+102;
                        }
                    }else{
                        BaseTypeData* basedata = new BaseTypeData();
                        basedata->autorelease();
                        basedata->dataId = data->itemId;
                        basedata->dataName = data->itemName;// itemName;
                        basedata->dataType = data->itemType;
                        basedata->dataQuality = data->itemQuality;
                        basedata->dataCount = data->itemCount;
                        m_basegift->pushBack(basedata);
                    }
                }
       
            }
            if (m_day == 7 && m_type == 0) {
                BoonData* data =  BoonDataManager::getInstance()->rewardlList->at(m_numhero-100);
                BaseTypeData* basedata = new BaseTypeData();
                basedata->autorelease();
                basedata->dataId = data->itemId;
                basedata->dataName = data->itemName;
                basedata->dataType = data->itemType;
                basedata->dataQuality = data->itemQuality;
                m_basegift->pushBack(basedata);
            }
            AwardBox_Layer* layer=AwardBox_Layer::create(m_basegift);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            BoonDataManager::getInstance()->desclList->at(0)->status = 3;
            setBg();
            broadMsg(CUSTOM_SEVENDAY_REDPOINT);
        }
    }
}

void EveryDayBoonLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekRewardPageResp).c_str(), CC_CALLBACK_1(EveryDayBoonLayer::onWeekRewardProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekReceiveResp).c_str(), CC_CALLBACK_1(EveryDayBoonLayer::onBoonDayRewardMsgProcess, this));
    this->addUserMsg(CUSTOM_WEEK_CHOSE_HERO, CC_CALLBACK_1(EveryDayBoonLayer::onChoseHeroProcess, this));
}
void EveryDayBoonLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}


