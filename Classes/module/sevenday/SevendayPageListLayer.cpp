//
//  SevendayPageListLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/12.
//
//

#include "SevendayPageListLayer.hpp"

#include "everyBoon/EveryDayBoonLayer.hpp"
#include "halfPrice/HalfPriceLayer.hpp"
#include "../../commonData/dictData/DictWeekTag/DictWeekTagManager.h"
#include "everytask/EveryTaskLayer.hpp"
#include "../../protocol/UserCustomEvent.h"
#include "sevendayData/SevendayRedPointDataManager.hpp"
SevendayPageListLayer::SevendayPageListLayer()
:m_day(1)
,sx(0)
,m_pageindex(1)
,m_isTeskOne(false)
,boxBtn(NULL)
,m_index(1)
{
    
    
}

SevendayPageListLayer:: ~ SevendayPageListLayer()
{
   
}

bool SevendayPageListLayer::init(int day)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        sx = GlobalInfo::getInstance()->screenScaleX;
        this->isAnimation = false;
        m_day = day;
        this->setBackground(IMG_SEVEENDAY_MODULEBG,Point::ZERO,true);
        setBg();
        
        bref = true;
    } while (false);
    return bref;
}

SevendayPageListLayer* SevendayPageListLayer::create(int day)
{
    SevendayPageListLayer* list = new SevendayPageListLayer();
    if(list && list->init(day))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void SevendayPageListLayer::onEnter()
{
    BaseLayer::onEnter();
}
void SevendayPageListLayer::onExit()
{
    BaseLayer::onExit();
}
void SevendayPageListLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
void SevendayPageListLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void SevendayPageListLayer::setBg()
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
    Sprite* word = Sprite::create(IMG_SEVEENDAY_HAPPYWORD);
    word->setAnchorPoint(Point::ZERO);
    word->setPosition(layer->getContentSize().width/sx/2 - word->getContentSize().width/2,layer->getContentSize().height/sx-80);
    layer->addChild(word);
    
    DictWeekTag* data = DictWeekTagManager::getInstance()->getData(m_day);
    
    const string pathun1 = PublicShowUI::getResImgPath(IMG_SEVEENDAY_UNTITLE, PublicShowUI::numberToString(data->tag1Id).c_str());
    const string path1 = PublicShowUI::getResImgPath(IMG_SEVEENDAY_TITLE, PublicShowUI::numberToString(data->tag1Id).c_str());
    
    const string pathun2 = PublicShowUI::getResImgPath(IMG_SEVEENDAY_UNTITLE, PublicShowUI::numberToString(data->tag2Id).c_str());
    const string path2 = PublicShowUI::getResImgPath(IMG_SEVEENDAY_TITLE, PublicShowUI::numberToString(data->tag2Id).c_str());
    
    const char* pathlist1[] = {IMG_SEVEENDAY_EVERYDAYUN,pathun1.c_str(),pathun2.c_str(),IMG_SEVEENDAY_HALFBUYUN };
    const char* pathlist2[] = {IMG_SEVEENDAY_EVERYDAY,path1.c_str(),path2.c_str(),IMG_SEVEENDAY_HALFBUY};
    
    boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(SevendayPageListLayer::onTopComboBoxClick, this));
    for (int i = 0; i<4; i++) {
        
        boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathlist1[i], pathlist2[i]);
    }
    for (int i = 0; i < 4; i++) {
        SevendayRedPointDataManager::getInstance()->setModulePot(boxBtn->getChildByTag(i),Point(-5,-5),m_day,i+1);
    }
    
    boxBtn->setAnchorPoint(Point::ZERO);
    boxBtn->setPosition(layer->getContentSize().width/sx/2-boxBtn->getContentSize().width/2,layer->getContentSize().height/sx-boxBtn->getContentSize().height-10);
    layer->addChild(boxBtn);
    boxBtn->getButtonAt(0)->selected();
    this->everyBoonLayer(TAG_BOON);
}
void SevendayPageListLayer::onTopComboBoxClick(Ref* pSender)
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
    Node* target = (Node*)pSender;
    log("%d",target->getTag());
    if (m_pageindex == target->getTag()) {
        return;
    }else{
        layer->removeChildByTag(m_pageindex);
    }
    
    switch (target->getTag()) {
        case 0:
            everyBoonLayer(TAG_BOON);
            break;
        case 1:
            m_isTeskOne = true;
             setTaskLayer(TAG_TESKTYPEONE);
            
            break;
        case 2:
            m_isTeskOne = false;
             setTaskLayer(TAG_TESKTYPETWO);
            break;
        case 3:
             setHalfPriceLayer(TAG_HALF);
            break;
        default:
            break;
    }
    
}
void SevendayPageListLayer::everyBoonLayer(int tag)
{
    
    m_pageindex = tag;
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
    EveryDayBoonLayer* everyLayer = EveryDayBoonLayer::create(m_day);
    everyLayer->setAnchorPoint(Point::ZERO);
    everyLayer->setPosition(Point::ZERO);
    layer->addChild(everyLayer,1,m_pageindex);
    
    
}

void SevendayPageListLayer::setHalfPriceLayer(int tag)
{
    m_pageindex = tag;
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
    HalfPriceLayer* everyLayer = HalfPriceLayer::create(m_day);
    everyLayer->setAnchorPoint(Point::ZERO);
    everyLayer->setPosition(Point::ZERO);
    layer->addChild(everyLayer,1,m_pageindex);
}
void SevendayPageListLayer::setTaskLayer(int tag)
{
    int page = 1;
    m_pageindex = tag;
    DictWeekTag* data = DictWeekTagManager::getInstance()->getData(m_day);
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    if(m_isTeskOne == true)
    {
        page = data->tag1Id;
    }else{
        page = data->tag2Id;
    }
    EveryTaskLayer* everyLayer = EveryTaskLayer::create(m_day,page);
    everyLayer->setAnchorPoint(Point::ZERO);
    everyLayer->setPosition(Point::ZERO);
    layer->addChild(everyLayer,1,m_pageindex);
    
}

void SevendayPageListLayer::refreshModuleRedPot()
{

//    int tag_index = m_pageindex+1;
//    if (tag_index == 1) {
//        SevendayRedPointDataManager::getInstance()->setModulePot(boxBtn->getChildByTag(0), Point::ZERO,m_day, 1);
//    }else if (tag_index == 2)
//    {
//        SevendayRedPointDataManager::getInstance()->setModulePot(boxBtn->getChildByTag(1), Point::ZERO,m_day, 2);
//    }else if (tag_index == 3)
//    {
//        SevendayRedPointDataManager::getInstance()->setModulePot(boxBtn->getChildByTag(2), Point::ZERO,m_day, 3);
//    }else if (tag_index == 4)
//    {
//        SevendayRedPointDataManager::getInstance()->setModulePot(boxBtn->getChildByTag(3), Point::ZERO,m_day, 4);
//    }
    for(int i = 0; i<4;i++)
    {
        SevendayRedPointDataManager::getInstance()->setModulePot(boxBtn->getChildByTag(i), Point(-5,-5),m_day, i+1);
    }
}
void SevendayPageListLayer::addEventListener()
{
    
    this->addUserMsg(CUSTOM_SEVENDAY_MODULE_REDPOINT, CC_CALLBACK_0(SevendayPageListLayer::refreshModuleRedPot, this));
    
}
void SevendayPageListLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
