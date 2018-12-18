//
//  RankDayLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#include "RankDayLayer.hpp"
#include "RankPriceLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/ranking/RankingDayMsg.hpp"
#include "../../common/Dialog/Dialog.h"
#include "rankingdata/RankingDataManager.hpp"
#include "../../protocol/Protocal.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../userWealth/UserEquipLayer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../../commonData/dictData/DictLegendRank/DictLegendRankManager.h"
#include "../../commonData/dictData/DictItemHero/DictItemHeroManager.h"
#include "RankAddFriendLayer.hpp"
RankDayLayer::RankDayLayer()
:TAG_TABLEVIEW(1)
,TAG_PERSONBG(2)
,m_legendName("")
,m_activityStartTimes(1)
,m_activityEndTimes(1)
,m_scoreTotal(1)
,m_rank(1)
,m_combatPower(1)
,m_roleLevel(1)
{
    
}
RankDayLayer::~ RankDayLayer()
{
    
}
bool RankDayLayer::init()
{
    setPersonBg();
    requestDayRankingMsg();
    return true;
    
}
RankDayLayer* RankDayLayer::create()
{
    RankDayLayer* layer = new RankDayLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void RankDayLayer::onEnter()
{
    BaseLayer::onEnter();
    
}
void RankDayLayer::onExit()
{
    BaseLayer::onExit();
}
void RankDayLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void RankDayLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
//    setTableView();
//    setperdetail();
    
}


void RankDayLayer::setPersonBg()
{
    Sprite* bossBg = Sprite::create(IMG_RANK_PERSON);
    bossBg->setAnchorPoint(Point::ZERO);
    this->addChild(bossBg,2,TAG_PERSONBG);
    Button* button = Button::create(IMG_PUBLIC_BUTTON_FOUR_RED, IMG_PUBLIC_BUTTON_FOUR_RED, CC_CALLBACK_1(RankDayLayer::onPriceClick, this));
    button->setAnchorPoint(Point::ZERO);
    button->setPosition(100,125);
    bossBg->addChild(button,1);
    
    Sprite* spr = Sprite::create(IMG_RANK_AWARDWORD);
    spr->setAnchorPoint(Point::ZERO);
    spr->setPosition(Point::ZERO);
    button->addChild(spr,4);
}
void RankDayLayer::onPriceClick(Ref* pSender)
{
    RankPriceLayer::show();
}
void RankDayLayer::setperdetail()
{
    Sprite* perdetailbg = (Sprite*)this->getChildByTag(TAG_PERSONBG);
    
    //活动名称
    string nameAcative = "综合大排名";
    Label* acativeLabel = PublicShowUI::getLabel(m_legendName.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_YELLOW),26,false,false);
    acativeLabel->setAnchorPoint(Point::ZERO);
    acativeLabel->setPosition(perdetailbg->getContentSize().width/2 - acativeLabel->getContentSize().width/2,375);
    perdetailbg->addChild(acativeLabel,3);
    
    
    //开始时间
    struct tm *l=localtime(&m_activityStartTimes);
    char buf[128];
    snprintf(buf,sizeof(buf),"%02d-%02d/%02d:%02d",l->tm_mon+1,l->tm_mday,l->tm_hour,l->tm_min);
    string start(buf);
    start = start + " - ";
    Label* activityStartTimeslabel = PublicShowUI::getLabel(start.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),16,false,false);
    activityStartTimeslabel->setAnchorPoint(Point::ZERO);
    activityStartTimeslabel->setPosition(55,acativeLabel->getPositionY()-activityStartTimeslabel->getContentSize().height);
    perdetailbg->addChild(activityStartTimeslabel,3);
    
    
    //结束时间
    l = localtime(&m_activityEndTimes);
    snprintf(buf,sizeof(buf),"%02d-%02d/%02d:%02d",l->tm_mon+1,l->tm_mday,l->tm_hour,l->tm_min);
    string end(buf);
    Label* endTimeslabel = PublicShowUI::getLabel(end.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),16,false,false);
    endTimeslabel->setAnchorPoint(Point::ZERO);
    endTimeslabel->setPosition(activityStartTimeslabel->getPositionX()+activityStartTimeslabel->getContentSize().width,activityStartTimeslabel->getPositionY());
    perdetailbg->addChild(endTimeslabel,3);
    
    
    //奖励英雄头像
    DictLegendRank* data = DictLegendRankManager::getInstance()->getData(1);
    const char* path = PublicShowUI::getGoods(data->item1Type, data->itemId1);
    if (path) {
        DictItemHero* dataitemhero = DictItemHeroManager::getInstance()->getData(data->itemId1);
        int  m_qulity = dataitemhero->quality;
        UserHeadLayer* userHead=UserHeadLayer::create(path,m_qulity,false);
        userHead->setHeadInfo(1, data->hero1Prestige);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setPosition(110,215);
        perdetailbg->addChild(userHead,3);
        //        userHead->addTouchBegainCallBack(this, callfuncN_selector(RankSynLayer::onHeroHeadClick));
        
        //奖品名称
        string nameprice = dataitemhero->name;
        Label* priceLabel = PublicShowUI::getLabel(nameprice.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),22,false,false);
        priceLabel->setAnchorPoint(Point::ZERO);
        priceLabel->setPosition(perdetailbg->getContentSize().width/2 - priceLabel->getContentSize().width/2,175);
        perdetailbg->addChild(priceLabel,3);
    }
    Sprite* no1prive = Sprite::create( IMG_RANK_NOONEPRIVE);
    no1prive->setAnchorPoint(Point::ZERO);
    no1prive->setPosition(190,200);
    perdetailbg->addChild(no1prive,5);
    
    //分数
    string scorestr = StringUtils::format("%d",m_scoreTotal);
    Label* scorelabel = PublicShowUI::getLabel(scorestr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),20,false,false);
    scorelabel->setAnchorPoint(Point::ZERO);
    scorelabel->setPosition(perdetailbg->getContentSize().width/2,78);
    perdetailbg->addChild(scorelabel,3);
    
    //排名
    string rankingstr = StringUtils::format("第%d名",m_rank);
    Label* rankinglabel = PublicShowUI::getLabel(rankingstr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,false);
    rankinglabel->setAnchorPoint(Point::ZERO);
    rankinglabel->setPosition(perdetailbg->getContentSize().width/2-40,42);
    perdetailbg->addChild(rankinglabel,3);
    
    //B格
    string fightstr = StringUtils::format("B格：%d",m_combatPower);
    Label* fightlabel = PublicShowUI::getLabel(fightstr.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),18,false,false);
    fightlabel->setAnchorPoint(Point::ZERO);
    fightlabel->setPosition(15,18);
    perdetailbg->addChild(fightlabel,3);
    
    //等级
    string levelstr = StringUtils::format("Lv：%d",m_roleLevel);
    Label* levelabel = PublicShowUI::getLabel(levelstr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
    levelabel->setAnchorPoint(Point::ZERO);
    levelabel->setPosition(170,18);
    perdetailbg->addChild(levelabel,3);
}

void RankDayLayer::setTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Node* bossbg = this->getChildByTag(TAG_PERSONBG);
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height * 2 + 60;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition(bossbg->getContentSize().width + 10,5);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    _size.width = _tableView->getPositionX() + _size.width;
    this->setContentSize(_size);
}
Sprite* RankDayLayer::singleList(size_t idx)
{
    if (RankingDataManager::getInstance()->rankingList->size() == 0) {
        return NULL;
    }
    if (idx > RankingDataManager::getInstance()->rankingList->size()) {
        return NULL;
    }
    RankingData* data = RankingDataManager::getInstance()->rankingList->at(idx);
    
    Sprite* cellbg = Sprite::create(IMG_RANK_CELLBG);
    if (idx == 0) {
        Sprite* one  = Sprite::create(IMG_RANK_FIRST);
        one->setAnchorPoint(Point::ZERO);
        one->setPosition(cellbg->getContentSize().width-one->getContentSize().width-30,cellbg->getContentSize().height/2-one->getContentSize().height/2+30);
        cellbg->addChild(one,10);
    }else if (idx == 1) {
        Sprite* one  = Sprite::create(IMG_RANK_SECOND);
        one->setAnchorPoint(Point::ZERO);
        one->setPosition(cellbg->getContentSize().width-one->getContentSize().width-30,cellbg->getContentSize().height/2-one->getContentSize().height/2+30);
        cellbg->addChild(one,10);
    }else if (idx == 2) {
        Sprite* one  = Sprite::create(IMG_RANK_THIRD);
        one->setAnchorPoint(Point::ZERO);
        one->setPosition(cellbg->getContentSize().width-one->getContentSize().width-30,cellbg->getContentSize().height/2-one->getContentSize().height/2+30);
        cellbg->addChild(one,10);
    }else{
        Node* ranklabel = PublicShowUI::getNumbers(idx+ 1,IMG_PUBLIC_NUMBER1);
        ranklabel->setAnchorPoint(Point(0.5,0.5));
        ranklabel->setScale(.7);
        ranklabel->setPosition(cellbg->getContentSize().width-70,cellbg->getContentSize().height/2+30);
        cellbg->addChild(ranklabel,10);
    }
    
    //头像
    DictHero* herodata= DictHeroManager::getInstance()->getData(data->iconHeroDictId);
    string str="";
    if (herodata) {
        str=herodata->headResource;
    }else
    {
        str="caopi";
    }
    const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, str.c_str());
    
    UserEquipLayer* head=UserEquipLayer::create(imgPath,1,false);
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(15, 10);
    cellbg->addChild(head,3);
    
    string scoreStr = StringUtils::format("%d",data->scoreToday);
    Label* scoreLabel = PublicShowUI::getLabel(scoreStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,false);
    scoreLabel->setAnchorPoint(Point::ZERO);
    scoreLabel->setPosition(cellbg->getContentSize().width/2 - scoreLabel->getContentSize().width/2-30,135);
    cellbg->addChild(scoreLabel,3);
    
    string nameAcative = data->roleName;
    Label* acativeLabel = PublicShowUI::getLabel(nameAcative.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_YELLOW),20,false,false);
    acativeLabel->setAnchorPoint(Point::ZERO);
    acativeLabel->setPosition(cellbg->getContentSize().width/2 - acativeLabel->getContentSize().width/2-20,80);
    cellbg->addChild(acativeLabel,3);
    
    //B格
    string fightstr = StringUtils::format("B格：%d",data->combatPowe);
    Label* fightlabel = PublicShowUI::getLabel(fightstr.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),18,false,false);
    fightlabel->setAnchorPoint(Point::ZERO);
    fightlabel->setPosition(150,30);
    cellbg->addChild(fightlabel,3);
    
    //等级
    string levelstr = StringUtils::format("Lv：%d",data->roleLevel);
    Label* levelabel = PublicShowUI::getLabel(levelstr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
    levelabel->setAnchorPoint(Point::ZERO);
    levelabel->setPosition(fightlabel->getPositionX() + fightlabel->getContentSize().width+50,30);
    cellbg->addChild(levelabel,3);
    
    
    Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(RankDayLayer::onfriendclick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->setPosition(cellbg->getContentSize().width-btn->getContentSize().width-20,20);
    cellbg->addChild(btn,3,idx);
    Sprite* addfri  = Sprite::create(IMG_RANK_FRIENDWORD);
    addfri->setAnchorPoint(Point::ZERO);
    addfri->setPosition(Point::ZERO);
    btn->addChild(addfri,5);
    
    return cellbg;
}
void RankDayLayer::onfriendclick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    int index = target->getTag();
    RankingData* data = RankingDataManager::getInstance()->rankingList->at(index);
    RankAddFriendLayer::show(data->userId, data->roleName);
}
TableViewCell* RankDayLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Sprite* node = singleList(idx);
    node->setAnchorPoint(Point::ZERO);
    cell->addChild(node);
    return cell;
}
ssize_t RankDayLayer::numberOfCellsInTableView(TableView *table)
{
    return RankingDataManager::getInstance()->rankingList->size();
}
void RankDayLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
Size RankDayLayer::tableCellSizeForIndex(TableView *table,ssize_t idx)
{
    if(cellSize.height == 0)
    {
        cellSize = Sprite::create(IMG_RANK_CELLBG)->getContentSize();
    }
    return cellSize;
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void RankDayLayer::requestDayRankingMsg()//请求列表信息
{
    Dialog::showServerLoading();
    RankingDayMsg* msg = new RankingDayMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void RankDayLayer::onDayRankingProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    RankingDataManager::getInstance()->clearRankingList();
    if(message->messageID == SCENSE_CLIENT_LEGEND_LegendRankTodayPageResp)
    {
        if(message->state)//返回成功
        {
            m_legendName = message->byteStream->getUTF8();
            m_activityStartTimes = message->byteStream->getLong();
            m_activityStartTimes = message->byteStream->getLong();
            m_scoreTotal = message->byteStream->getInt();
            m_rank = message->byteStream->getInt();
            m_combatPower = message->byteStream->getInt();
            m_roleLevel = message->byteStream->getInt();
            short rangSize = message->byteStream->getShort();
            for (int  i = 0; i < rangSize; i++) {
                RankingData* data = new RankingData();
                data->autorelease();
                data->roleName = message->byteStream->getUTF8();
                data->userId = message->byteStream->getLong();
                data->iconHeroDictId = message->byteStream->getInt();
                data->roleLevel = message->byteStream->getInt();
                data->combatPowe = message->byteStream->getInt();
                data->scoreToday = message->byteStream->getInt();
                RankingDataManager::getInstance()->add(data);
            }
            setperdetail();
            setTableView();
        }
    }
}
void RankDayLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendRankTodayPageResp).c_str(), CC_CALLBACK_1(RankDayLayer::onDayRankingProcess, this));
}

void RankDayLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

