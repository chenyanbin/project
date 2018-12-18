//
//  ArenaListLayer.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/9.
//
//

#include "ArenaListLayer.hpp"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../common/ImagePath.h"
#include "ChallengeNode.hpp"
#include "../../../message/Decoding/arena/ArenaListMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../arenaData/ArenaDataManager.hpp"
#include "../../../protocol/UserCustomEvent.h"
#include "BuyTimeLayer.hpp"
#include "../../../message/Decoding/arena/BeginFightMsg.hpp"
#include "../../battleTest/PlayerDataManager.hpp"
ArenaListLayer::ArenaListLayer()
:TAG_TABLEVIEW(1)
,m_countDown(0)
,TAG_LEFTTIME(100)
,TAG_TOPNODE(101)
,TAG_NODELETTLE(102)
,m_arenaCount(0)
,m_buyCount(0)
,m_buyCDTimeGold(0)
,m_buyCounyGlod(0)
,m_index(0)
,m_isRefresh(false)
{
    
}
ArenaListLayer::~ArenaListLayer()
{
    
}
bool ArenaListLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG,Point::ZERO,false);
        
        Sprite* node = Sprite::create(IMG_PUBLIC_LAYER_LISTBGTITLEBG);
        node->setAnchorPoint(Point::ZERO);
        node->setPosition(18 ,  this->getContentSize().height - node->getContentSize().height - 20);
        this->addChild(node,1);

        
        setChangeBtn();
        bref = true;
    } while (false);
    return bref;
}
ArenaListLayer* ArenaListLayer::create()
{
    ArenaListLayer* layer = new ArenaListLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void ArenaListLayer::show()
{
    ArenaListLayer* layer = ArenaListLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_LAYER_ZORDER);
    Director::getInstance()->replaceScene(scene);
}
void ArenaListLayer::setTopData(int _rank,int _fightPowe,int _honer,int _allFreeTimes,int _freeTimes)
{
    Node* topNode = Node::create();
    topNode->setAnchorPoint(Point::ZERO);
    this->addChild(topNode,4,TAG_TOPNODE);
    //当前排名
    Node* curOrderNode = Node::create();
    if (_rank>0) {
        curOrderNode = this->getTopNode(IMG_ARENA_CURORDER, _rank);
    }else{
        Sprite* spr = Sprite::create(IMG_ARENA_CURORDER);
        spr->setAnchorPoint(Point::ZERO);
        curOrderNode->addChild(spr);
        Size size = spr->getContentSize();
        string numStr = "未上榜";
    
        Label* label = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),20,false,false);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(size.width + 5, (size.height - label->getContentSize().height)/2);
        spr->addChild(label);
        size.width = label->getPositionX() + label->getContentSize().width;
        curOrderNode->setContentSize(size);
    }
    
    topNode->addChild(curOrderNode, 0);

    //B格
    Node* bgeNode = this->getTopNode(IMG_ARENA_BGE, _fightPowe);
    bgeNode->setScale(0.9);
    bgeNode->setPositionX(curOrderNode->getPositionX()  + curOrderNode->getContentSize().width );
    topNode->addChild(bgeNode, 0);

    
    //竞技次数
    Node* raceCountNode = this->getTopNode(IMG_ARENA_COUNTVALUE, _allFreeTimes,_freeTimes);
    raceCountNode->setPositionX(bgeNode->getPositionX()  + bgeNode->getContentSize().width );
    topNode->addChild(raceCountNode, 0);
    
    
    topNode->setPosition(30 ,  this->getContentSize().height/GlobalInfo::getInstance()->screenScaleX - curOrderNode->getContentSize().height - 36 );
    
}

Node* ArenaListLayer::getTopNode(const char* titlePath,int value,int freeTime)
{
    Sprite* node = Sprite::create(titlePath);
    node->setAnchorPoint(Point::ZERO);
    Size size = node->getContentSize();
    
    string numStr = "";
    if (freeTime == 100) {
        numStr = StringUtils::format("%d",value);
    }else
    {
        numStr = StringUtils::format("%d/%d",freeTime,value);
    }
    
    Label* label = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),20,false,false);
    
//    Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(value).c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(size.width + 5, (size.height - label->getContentSize().height)/2);
    node->addChild(label);
    
    size.width = label->getPositionX() + label->getContentSize().width;
    node->setContentSize(size);
    return node;
    
}
void ArenaListLayer::setTime()
{
     Node* node = this->getChildByTag(TAG_TOPNODE);
    if(m_countDown <= 0)
    {
        this->removeChildByTag(TAG_NODELETTLE);
        return;
    }
    Node* labelnode = (Node*)this->getChildByTag(TAG_NODELETTLE);
    Sprite* spr = NULL;
    if (!labelnode)
    {
        
        labelnode = Node::create();
        labelnode->setAnchorPoint(Point::ZERO);
        this->addChild(labelnode,4,TAG_NODELETTLE);
        
        spr = Sprite::create(IMG_ARENA_FIGHTTIME);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition(480,node->getPositionY());
        labelnode->addChild(spr,4);
    }
    
    string str = PublicShowUI::getTime(this->m_countDown);
    str = "             " + str;
    Label* label = (Label*)labelnode->getChildByTag(TAG_LEFTTIME);
    if(label)
    {
        label->setString(str);
    }
    else
    {
        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE),20,false,false);
        label->setAnchorPoint(Point::ZERO);
        labelnode->addChild(label,9,TAG_LEFTTIME);
        label->setPosition(530,node->getPositionY());
    }
    DelayTime* delay = DelayTime::create(1);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(ArenaListLayer::setTime, this));
    label->runAction(Sequence::create(delay,callBack, NULL));
    m_countDown-= 1000;
}
void ArenaListLayer::setChangeBtn()
{
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(ArenaListLayer::onChangeBtnClick, this));
    btn->addTitle(IMG_ARENALIST_CHANGETITLE, "");
    btn->setPosition(this->getContentSize().width - btn->getContentSize().width , this->getContentSize().height - btn->getContentSize().height - 5);
    this->addChild(btn,4);
}
void ArenaListLayer::onChangeBtnClick(Ref* pSender)
{
    requestFightListMsg(1);
    m_isRefresh = true;
}

void ArenaListLayer::setTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Node* bg = this->getChildByTag(TAG_BG);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3 + 5;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition((bg->getContentSize().width - _size.width) / 2,(bg->getContentSize().height - _size.height)/2 -  15);
    this->addChild(_tableView,1,TAG_TABLEVIEW);
    
}
//-----------------------------------------------tableView-------------------------------------------------------//

TableViewCell* ArenaListLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    if(idx>=ArenaDataManager::getInstance()->arenaList->size())
    {
        return NULL;
    }
    
    Node* node = ChallengeNode::create(idx);
    node->setAnchorPoint(Point::ZERO);
    cell->addChild(node);
    cell->setContentSize(node->getContentSize());
    cell->setTag((int)idx);
    
    return cell;
}
ssize_t ArenaListLayer::numberOfCellsInTableView(TableView *table)
{
    return ArenaDataManager::getInstance()->arenaList->size();
}
void ArenaListLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
Size ArenaListLayer::tableCellSizeForIndex(TableView *table,ssize_t idx)
{
    if(cellSize.height == 0)
    {
        cellSize = Sprite::create(IMG_FAMOUSE_HEROITEMBG)->getContentSize();
    }
    return cellSize;
}

void ArenaListLayer::onEnter()
{
    BaseLayer::onEnter();
}
void ArenaListLayer::onExit()
{
    BaseLayer::onExit();
}
void ArenaListLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void ArenaListLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
//    setTableView();
    requestFightListMsg(0);
    
}
void ArenaListLayer::ontFightNumMsgProcess(EventCustom* msg)//确认冷时间
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_index = inter->getValue();
    if (m_arenaCount>0 && m_countDown >0)//冷却时间
    {
        BuyTimeLayer::show(2, m_buyCDTimeGold);
    }else if (m_arenaCount <= 0)
    {
        BuyTimeLayer::show(1, m_buyCounyGlod,m_buyCount);
    }else
    {
        requestBeginFightListMsg(m_index + 1);
    }
}
void ArenaListLayer::onSureFightProcess(EventCustom* msg)//购买成功
{
    requestBeginFightListMsg(m_index + 1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
//    log("index========%ld",ArenaDataManager::getInstance()->arenaList->at(m_index)->roleId);
}
//-----------------------------------------------访问服务器-------------------------------------------------------//

void ArenaListLayer::requestFightListMsg(int refresh)//请求列表信息
{
    Dialog::showServerLoading();
    ArenaListMsg* msg = new ArenaListMsg(refresh);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ArenaListLayer::requestBeginFightListMsg(int index)//请求开始挑战
{
    Dialog::showServerLoading();
    BeginFightMsg* msg = new BeginFightMsg(index);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ArenaListLayer::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(msg->messageID == SCENSE_CLIENT_ARENA_ArenaPageResp)
    {
        ArenaDataManager::getInstance()->destroyInstance();
        if(msg->state)//返回成功
        {
            int currentRank = msg->byteStream->getInt();//当前排名
            int combatPower = msg->byteStream->getInt();//战斗力
            int currentHonor = msg->byteStream->getInt();//当前荣誉之
            int totalCount = msg->byteStream->getInt();//免费总挑战次数
            m_arenaCount = msg->byteStream->getInt();//可以挑战次数
            m_buyCount = msg->byteStream->getInt();//可购买的次数
            m_buyCounyGlod = msg->byteStream->getInt();//购买次数所需元宝
            m_buyCDTimeGold = msg->byteStream->getInt();//购买冷却时间所需元宝
            m_countDown = msg->byteStream->getLong();//倒计时 多长时间恢复挑战
//            m_countDown = 1000000;
            int roleSize = msg->byteStream->getByte();
            for (int i = 0; i < roleSize; i ++)
            {
                ArenaListData* data = new ArenaListData;
                data->autorelease();
                data->roleId = msg->byteStream->getLong();
                data->rank = msg->byteStream->getInt();
                data->heroDictId = msg->byteStream->getInt();
                data->roleName = msg->byteStream->getUTF8();
                data->power = msg->byteStream->getInt();
                data->roleLevel = msg->byteStream->getInt();
                int reWardCount = msg->byteStream->getByte();
                for (int j = 0; j < reWardCount; j++)
                {
                    int item = msg->byteStream->getByte();
                    int itemId = msg->byteStream->getInt();
                    int count = msg->byteStream->getShort();
                    if (j == 0) {
                        data->honor = count;
                    }else if (j == 1)
                    {
                        data->coin = count;
                    }
                }
                int herosize = msg->byteStream->getByte();
                for (int i = 0; i < herosize; i ++) {
                    struct HeroHead _heroList = {0};
                    _heroList.herodict = msg->byteStream->getInt();
                    data->heroHeadList.push_back(_heroList);
                }
    
                ArenaDataManager::getInstance()->addData(data);
            }
            setTableView();
            if (!m_isRefresh) {
                setTopData(currentRank,combatPower,currentHonor,totalCount,m_arenaCount);
                setTime();
            }

        }
    }else if(msg->messageID == SCENSE_CLIENT_ARENA_ArenaStartBattleResp)
    {
        log("挑战");
        if(msg->state)
        {
            PlayerDataManager::getInstance()->parseMsg(msg->byteStream);
        }
    }
}

void ArenaListLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaPageResp).c_str(), CC_CALLBACK_1(ArenaListLayer::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaStartBattleResp).c_str(), CC_CALLBACK_1(ArenaListLayer::onMsgProcess, this));
    addUserMsg(CUSTOM_ARENA_FIGHT_INDEX, CC_CALLBACK_1(ArenaListLayer::ontFightNumMsgProcess, this));
    addUserMsg(CUSTOM_ARENA_FIGHT_SUCCEED, CC_CALLBACK_1(ArenaListLayer::onSureFightProcess, this));

        
}
void ArenaListLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumDekaronButton);
}
