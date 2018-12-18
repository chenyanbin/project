//
//  LineupCheerLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/23.
//
//

#include "LineupCheerLayer.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../protocol/UserCustomEvent.h"
#include "../userWealth/UserHeadLayer.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "wujiangList/LineupAllHeroLayer.h"
#include "../../message/Decoding/lineup/LineupSetRespMsg/LineupSetRespMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/TouchSprite/Button.h"
#include "../userWealth/UserEquipLayer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../../commonData/dictData/DictLineupAuxiliary/DictLineupAuxiliaryManager.h"
#include "../../common/noticeManager/NoticeManager.h"
LineupCheerLayer::LineupCheerLayer()
:TAG_CONTAINER(1)
,m_lineupNo(1)
,TAG_JIACHENG(2)
,isHide(true)
,m_leader(0)
,TAG_LABEL(10)
{
    cheerList=new Vector<LineupPageData*>();

}
LineupCheerLayer::~LineupCheerLayer()
{
    log("~StageLayer ~StageLayer");
//    cheerList->clear();
//    CC_SAFE_DELETE(cheerList);
}

bool LineupCheerLayer::init(int nowPage)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        m_lineupNo = nowPage;
        setBackGround();
       
        bref = true;
    } while (false);
    return bref;
}

LineupCheerLayer* LineupCheerLayer::create(int nowPage)
{
    LineupCheerLayer* list = new LineupCheerLayer();
    if(list && list->init(nowPage))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void LineupCheerLayer::setBackGround()
{

    Sprite* Bg = Sprite::create(IMG_LINEUP_CHEERBG);
    Bg->setAnchorPoint(Point::ZERO);
    this->addChild(Bg, 1, TAG_BG);
    Bg->setOpacity(255);
    Size size = Bg->getContentSize();
    Bg->setPosition(Point::ZERO);
    this->setContentSize(Bg->getContentSize());
    
}
void LineupCheerLayer::onEnter()
{
    BaseLayer::onEnter();
}
void LineupCheerLayer::onExit()
{
    BaseLayer::onExit();
}
void LineupCheerLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    
}
void LineupCheerLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumHelpPosition1);
}

void LineupCheerLayer::setCheerHero()
{
    this->removeChildByTag(TAG_CONTAINER);
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    TouchSprite* node = NULL;
    UserHeadLayer* userHead = NULL;
    for(int i = 0; i < cheerList->size(); i++)
    {
        if (cheerList->at(i)->heroDictId == 0)
        {
            node = TouchSprite::createWithPic(IMG_LINEUP_HEAD,this, callfuncN_selector(LineupCheerLayer::onClick));
            node->setAnchorPoint(Point::ZERO);
            node->setScale(0.8);
            node->setPosition(120 + i * (node->getContentSize().width+100),10);
            container->addChild(node,3,i+1);
            
            Sprite* add = Sprite::create(IMG_LINEUP_ADD);
            add->setAnchorPoint(Point::ZERO);
            add->setScale(1.5);
            add->setPosition(3,3);
            node->addChild(add,1);
            if( i == 0)
            {
                GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumHelpPosition1, node);
            }
        }
        else
        {
            DictHero* dictHero = DictHeroManager::getInstance()->getData(cheerList->at(i)->heroDictId);
            if (dictHero) {
                userHead = UserHeadLayer::create(dictHero->resource.c_str(),cheerList->at(i)->quality);
                userHead->setHeadInfo(cheerList->at(i)->level, 1);
                userHead->setAnchorPoint(Point::ZERO);
                userHead->setScale(0.8);
                userHead->setPosition(120 + i * (userHead->getContentSize().width+100), 10);
                container->addChild(userHead,2,i+1);
                userHead->addTouchBegainCallBack(this, callfuncN_selector(LineupCheerLayer::onClick));
            }
        }
    }
    this->addChild(container,1,TAG_CONTAINER);
}
void LineupCheerLayer::jiachengData()
{
    this->removeChildByTag(TAG_LABEL);
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    Label* timesLabel = NULL;
    Label* label = NULL;
    ssize_t len = cheerList->size();
    for (int i = 0; i < len; i++) {
        int m_Num = 0;
        string name = "";
        if (i == 0) {
            name = "生命";
            label = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),24,false,false);
            m_Num = cheerList->at(i)->hp;
            string Card = StringUtils::format("+%d",m_Num);
            timesLabel = PublicShowUI::getLabel(Card.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),24,false,false);
        }else if (i == 1){
            name = "攻击";
            label = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),24,false,false);
            m_Num = cheerList->at(i)->attack;
            string Card = StringUtils::format("+%d",m_Num);
            timesLabel = PublicShowUI::getLabel(Card.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),24,false,false);
        }else if (i == 2){
            name = "防御";
            label = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE_YELLOW),24,false,false);
            m_Num = cheerList->at(i)->defend;
            string Card = StringUtils::format("+%d",m_Num);
            timesLabel = PublicShowUI::getLabel(Card.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE_YELLOW),24,false,false);
        }
        label->setAnchorPoint(Point(0.5,0));
        container->addChild(label,1);
        label->setPosition(270+i*220,50);
        
        timesLabel->setAnchorPoint(Point(0.5,0));
        container->addChild(timesLabel,1);
        timesLabel->setPosition(270+i*220,20);
    }
    this->addChild(container,1,TAG_LABEL);
}

void LineupCheerLayer::onClick(Node* psender)
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumHelpPosition))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    int index = psender->getTag();
    
    //玩家等级
    int userLevel = GlobalInfo::getInstance()->gameRole->level;
     //开启等级
    int openlelve = 0;
    DictLineupAuxiliary* data = DictLineupAuxiliaryManager::getInstance()->getData(index);
    if (data) {
        openlelve =  data->openLevel;
        log("助阵位开启%d",openlelve);
    }
    
    if (userLevel<openlelve) {
        string str = StringUtils::format("等级%d开启",openlelve);
        NoticeManager::getInstance()->showNotice(str.c_str());
        return;
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumHelpPosition1);
    LineupAllHeroLayer::show(m_lineupNo,2,index,m_leader);
    
}
void LineupCheerLayer::requestLineupSetMsg(int lineupNo,int heroType, int location, int heroId)//选择英雄
{
    log("==================requestLineupSetMsg===============");
    LineupSetRespMsg* msg = new LineupSetRespMsg(lineupNo,heroType,location,heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LineupCheerLayer::onHeroList(EventCustom* msg)//接受消息，更新HeroPos，接收当前页
{
    cheerList = (Vector<LineupPageData*>*)msg->getUserData();
    setCheerHero();
    jiachengData();
}
void LineupCheerLayer::onlineupNo(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_lineupNo = inter->getValue();

}
void LineupCheerLayer::onlingdaoli(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_leader = inter->getValue();
    
}
void LineupCheerLayer::addEventListener()//添加监听
{
    addUserMsg(CUSTOM_CHANGE_TEAMPAGE, CC_CALLBACK_1(LineupCheerLayer::onlineupNo, this));
    addUserMsg(CUSTOM_LINEUP_ZHUZHENWUJIANG, CC_CALLBACK_1(LineupCheerLayer::onHeroList, this));
    addUserMsg(CUSTOM_LINEUP_LEADERSHIP, CC_CALLBACK_1(LineupCheerLayer::onlingdaoli, this));
    
}
void LineupCheerLayer::removeEventListener()//清除监听
{
    BaseLayer::removeEventListener();
}
