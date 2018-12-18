//
//  FindCellLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/16.
//
//

#include "FindCellLayer.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../marketData/marketFindDataManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/TouchSprite/Button.h"
#include "FindAccelerationLayer.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/market/marketFindMsg/MarketFindPageMsg.h"
#include "../../../avatar/hero/Hero.h"
#include "../../../common/Dialog/Dialog.h"
FindCellLayer::FindCellLayer()
:TAG_SHANGJAITIME(10)
,m_shangjiatimess(1)
,m_shangjiatimeLabel(NULL)
,m_idx(1)
,m_tag(1)
,TAG_MAP(10)
,TAG_HERO(11)
{
    
}

FindCellLayer::~ FindCellLayer()
{
   
}


bool FindCellLayer::init(int idx)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_idx = idx;
        this->isAnimation = false;
        shangjiaCellBackGround(idx);
        bref = true;
    } while (false);
    return bref;
}

FindCellLayer* FindCellLayer::create(int idx)
{
    FindCellLayer* list = new FindCellLayer();
    if(list && list->init(idx))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void FindCellLayer::onEnter()
{
    BaseLayer::onEnter();
}
void FindCellLayer::onExit()
{
    BaseLayer::onExit();
}
void FindCellLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void FindCellLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FindCellLayer::shangjiaCellBackGround(int idx)
{
    if (idx > marketFindDataManager::getInstance()->findList->size()) {
        return;
    }

    MarketFindData* data = marketFindDataManager::getInstance()->findList->at(idx);
    Sprite* map2=Sprite::create(IMG_MARKET_MARKETFIND_MAP);
    map2->setAnchorPoint(Point::ZERO);
    map2->setPosition(Point::ZERO);
    this->addChild(map2,1,TAG_MAP);
    
    Sprite* inxunfang = Sprite::create(IMG_MARKET_MARKETFIND_INXUNFANG);
    inxunfang->setAnchorPoint(Point::ZERO);
    inxunfang->setPosition(0,map2->getContentSize().height-inxunfang->getContentSize().height);
    map2->addChild(inxunfang,1);
    
    Sprite* lasttime = Sprite::create(IMG_MARKET_MARKETFIND_LASTTIMESPR);
    lasttime->setAnchorPoint(Point::ZERO);
    lasttime->setPosition(map2->getContentSize().width-lasttime->getContentSize().width-250,10);
    map2->addChild(lasttime,1);
    
    //倒计时
    m_shangjiatimess = data->remainingTime;
    string recuittime=StringUtils::format("%02ld:%02ld:%02ld",m_shangjiatimess/3600, m_shangjiatimess%3600/60,m_shangjiatimess%60);
    m_shangjiatimeLabel = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),18,false,false);
    m_shangjiatimeLabel->setAnchorPoint(Point::ZERO);
    map2->addChild(m_shangjiatimeLabel,1);
    m_shangjiatimeLabel->setTag(TAG_SHANGJAITIME);
    m_shangjiatimeLabel->setPosition(lasttime->getPositionX()+80,lasttime->getPositionY() + 1);
    this->schedule(schedule_selector(FindCellLayer::Updata),1);
    
    const char* jiasupath = PublicShowUI::getResImgPath(IMG_MARKET_MARKETFIND_XUNFANG, PublicShowUI::numberToString(2).c_str());
    Button* jiasuxunfangSpr=Button::create(jiasupath, "", CC_CALLBACK_1(FindCellLayer::onjiasuClick, this));
    jiasuxunfangSpr->setAnchorPoint(Point::ZERO);
    jiasuxunfangSpr->setPosition(470,25);
    map2->addChild(jiasuxunfangSpr,5,idx);
    DictHero* dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
    if(!dictHero)
    {
        log("heroDictId======%d",data->heroDictId);
        Dialog::show("数据异常");
    }
//    if(data->heroDictId == 0)
//    {
//        Dialog::show("武将被吞噬");
//    }
    else
    {
        DictHero* dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
        AnimationData* animationData = ArmatureDataManager::getInstance()->getAnimationData(dictHero->resource.c_str());
        if(animationData)
        {
            onHeroLoaded();
        }

    }
        this->setContentSize(map2->getContentSize());
}
//加速寻访
void FindCellLayer::onjiasuClick(Ref* psender)
{
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    FindAccelerationLayer::show(target->getTag());
}

void FindCellLayer::Updata(float delta)
{
    m_shangjiatimess -= 1;
    if (m_shangjiatimess <= 0) {
        m_shangjiatimess =0;
        log("%ld",m_shangjiatimess);
        againRequestListMsg();
        unschedule(schedule_selector(FindCellLayer::Updata));
    }
    char*mtime = new char[10];
    //显示小时，分钟，秒
    sprintf(mtime," %02ld:%02ld:%02ld",m_shangjiatimess/3600, m_shangjiatimess%3600/60,m_shangjiatimess%60);
    m_shangjiatimeLabel->setString(mtime);
}
void FindCellLayer::againRequestListMsg()//请求列表信息
{
    MarketFindPageMsg* msg = new MarketFindPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FindCellLayer::onHeroLoaded()
{
    log("ddddddddddd");
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_MAP);
    if(cardBg->getChildByTag(TAG_HERO))
    {
        return;
    }
    Hero* cardHero=Hero::create(marketFindDataManager::getInstance()->findList->at(m_idx)->heroDictId);
    if (!cardHero) {
        log("%d",marketFindDataManager::getInstance()->findList->at(m_idx)->heroDictId);
        Dialog::show("数据异常");

    }else{
        cardHero->setScale(0.5);
        cardHero->setPosition(20, 30);
        cardBg->addChild(cardHero,3,TAG_HERO);
        cardHero->walkWithDirection(Point(0,0),true);
        
        MoveTo* move = MoveTo::create(4, Point(670,60));
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(FindCellLayer::returnFirstPoint, this));
        Sequence* seq = Sequence::create(move, callBack, NULL);
        RepeatForever* rep = RepeatForever::create(seq);
        cardHero->runAction(rep);
    }
    
}
void FindCellLayer::onHeroLoadedPreogress(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    int idx = inter->getValue();
    if (idx == 1) {
        onHeroLoaded();
    }
    
}
void FindCellLayer::returnFirstPoint(){
    Hero* hero = (Hero*)this->getChildByTag(TAG_MAP)->getChildByTag(TAG_HERO);
    hero->setPosition(20, 30);
}


void FindCellLayer::onSpeedMsgProcess(EventCustom* msg)//加速跑
{
//    __Integer* inter = (__Integer*)msg->getUserData();
//    m_tag = inter->getValue();
//    
//    Hero* cardHero = (Hero*)this->getChildByTag(TAG_MAP)->getChildByTag(TAG_HERO);
//    if (cardHero) {
//        cardHero->setPosition(20, 60);
//        MoveTo* move = MoveTo::create(2, Point(520,60));
//        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(FindCellLayer::onSureRunSucceed, this));
//        Sequence* seq = Sequence::create(move, callBack, NULL);
//        cardHero->runAction(seq);
//    }
}

void FindCellLayer::onSureRunSucceed()//加速跑完成
{
//    broadMsg(CUSTOM_MARKER_JIASUWANCHENG,__Integer::create(m_tag));
}

void FindCellLayer::addEventListener()
{
    this->addUserMsg(CUSTOM_MARKER_HEROLOADED, CC_CALLBACK_1(FindCellLayer::onHeroLoadedPreogress, this));
}
void FindCellLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
