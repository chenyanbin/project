//
//  ArenaTeamLayer.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/10.
//
//

#include "ArenaTeamLayer.hpp"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../common/ImagePath.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../message/Decoding/arena/ArenaTeamMsg.hpp"
#include "../arenaData/ArenaLineupDataManager.hpp"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../userWealth/UserHeadLayer.h"
#include "../../lineup/LineupLayer.h"
#include "../../../message/Decoding/lineup/lineupFightMsg/LineupFightMsg.h"
ArenaTeamLayer::ArenaTeamLayer()
:TAG_TABLEVIEW(1)
,m_index(0)
,m_oldIndex(0)
{
    
}
ArenaTeamLayer::~ArenaTeamLayer()
{
    
}
bool ArenaTeamLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG,Point::ZERO,false);
        
        Sprite* node = Sprite::create(IMG_PUBLIC_LAYER_LISTBGTITLEBG);
        node->setAnchorPoint(Point::ZERO);
        node->setPosition(18 ,  this->getContentSize().height - node->getContentSize().height - 20);
        this->addChild(node,1);
        
//        setTopData();
        setChangeBtn();
        bref = true;
    } while (false);
    return bref;
}
ArenaTeamLayer* ArenaTeamLayer::create()
{
    ArenaTeamLayer* layer = new ArenaTeamLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}

void ArenaTeamLayer::setTopData(int _rank,int _fightPowe,int _honer,int _fightTimes,long _time)
{
    Node* topNode = Node::create();
    topNode->setAnchorPoint(Point::ZERO);
    this->addChild(topNode,4);
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
    bgeNode->setPositionX(curOrderNode->getPositionX()  + curOrderNode->getContentSize().width + 6);
    topNode->addChild(bgeNode, 0);
    
    //当前荣誉
    Node* nowHonor = this->getTopNode(IMG_ARENA_NOWHONOR, _honer);
    nowHonor->setPositionX(bgeNode->getPositionX()  + bgeNode->getContentSize().width + 6);
    topNode->addChild(nowHonor, 0);
    
    //竞技次数
    Node* raceCountNode = this->getTopNode(IMG_ARENA_COUNTVALUE, _fightTimes);
    raceCountNode->setPositionX(nowHonor->getPositionX()  + nowHonor->getContentSize().width + 6);
    topNode->addChild(raceCountNode                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     , 0);
    
    
    topNode->setPosition(30 ,  this->getContentSize().height/GlobalInfo::getInstance()->screenScaleX - curOrderNode->getContentSize().height - 36 );
    
}
Node* ArenaTeamLayer::getTopNode(const char* titlePath,int value)
{
    Sprite* node = Sprite::create(titlePath);
    node->setAnchorPoint(Point::ZERO);
    Size size = node->getContentSize();
    Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(value).c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(size.width + 5, (size.height - label->getContentSize().height)/2);
    node->addChild(label);
    
    size.width = label->getPositionX() + label->getContentSize().width;
    node->setContentSize(size);
    return node;
    
}
void ArenaTeamLayer::setChangeBtn()
{
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(ArenaTeamLayer::onChangeBtnClick, this));
    btn->addTitle(IMG_ARENALIST_CHANGETITLE, "");
}
void ArenaTeamLayer::onChangeBtnClick(Ref* pSender)
{
    
}

void ArenaTeamLayer::setTableView()
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
void ArenaTeamLayer::onEnter()
{
    BaseLayer::onEnter();
}
void ArenaTeamLayer::onExit()
{
    BaseLayer::onExit();
}
void ArenaTeamLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void ArenaTeamLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestLineupMsg();
//    setTableView();
//    setTopData();
}


void ArenaTeamLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
TableViewCell* ArenaTeamLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
    cell->setContentSize(node->getContentSize());
    cell->setTag((int)idx);
    
    return cell;
}
ssize_t ArenaTeamLayer::numberOfCellsInTableView(TableView *table)
{
    return ArenaLineupDataManager::getInstance()->lineupList->size();
}
void ArenaTeamLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
Size ArenaTeamLayer::tableCellSizeForIndex(TableView *table,ssize_t idx)
{
    if(cellSize.height == 0)
    {
        cellSize = Sprite::create(IMG_FAMOUSE_HEROITEMBG)->getContentSize();
    }
    return cellSize;
}
Sprite* ArenaTeamLayer::singleList(size_t idx)
{
    Sprite* cellbg = Sprite::create(IMG_ARENATEAM_ITEMBG);
    
    UserHeadLayer* head = NULL;
    ArenaLineupData* data = ArenaLineupDataManager::getInstance()->lineupList->at(idx);
    
    //阵容数
    string strNum = PublicShowUI::numberToString((int)idx+1);
    Label* NumLabel = PublicShowUI::getLabel(strNum.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),28,false,false);
    NumLabel->setAnchorPoint(Point::ZERO);
    cellbg->addChild(NumLabel,3);
    NumLabel->setPosition(110,70);
    
    //逼格
    string str = PublicShowUI::numberToString(data->lineupPower);
    Label* powerLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),20,false,false);
    powerLabel->setAnchorPoint(Point::ZERO);
    cellbg->addChild(powerLabel,3);
    powerLabel->setPosition(70,35);
    
    for(int i = 0 ;i  < data->herolist.size(); i++)
    {
        DictHero* dictHero = DictHeroManager::getInstance()->getData(data->herolist.at(i).heroDictId);
        if (dictHero) {
            head = UserHeadLayer::create(dictHero->resource.c_str(),data->herolist.at(i).heroQuality);
            //        head = UserHeadLayer::create("zhaoyun",3,true);
            head->setAnchorPoint(Point::ZERO);
            head->setHeadInfo(data->herolist.at(i).heroLevel, data->herolist.at(i).prestige);
            cellbg->addChild(head,1);
            head->setPosition(198 + (head->getContentSize().width + 15) * i,(cellbg->getContentSize().height - head->getContentSize().height)/2);
        }
        
    }
    
    CustomButton* editBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(ArenaTeamLayer::onEditBtnClick, this));
    editBtn->addTitle(IMG_ARENATEAM_EDIT, IMG_ARENATEAM_EDIT);
    editBtn->setPosition(cellbg->getContentSize().width - editBtn->getContentSize().width/2 - 10, cellbg->getContentSize().height / 2 + 26);
    cellbg->addChild(editBtn, 3,idx);
    
    if (data->isdefault == 0) {
        CustomButton* selectedBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_RED, "", CC_CALLBACK_1(ArenaTeamLayer::onSelectedBtnClick, this));
        selectedBtn->addTitle(IMG_ARENATEAM_SELECTED, IMG_ARENATEAM_SELECTED);
        selectedBtn->setPosition(editBtn->getPositionX(), cellbg->getContentSize().height/2 - 26);
        if (data->herolist.size()<=0) {
            selectedBtn->setEnabled(false);
        }
        cellbg->addChild(selectedBtn, 3,idx);
    }else if(data->isdefault == 1)
    {
        m_oldIndex = idx;
        string str = "上阵阵容";
        Label* powerLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_RED),24,false,false);
        powerLabel->setAnchorPoint(Point::ZERO);
        cellbg->addChild(powerLabel,3);
        powerLabel->setPosition(editBtn->getPositionX()-45, cellbg->getContentSize().height/2 - 35);
    }

    return cellbg;
}
void ArenaTeamLayer::onEditBtnClick(Ref* pSender)
{
    Node* node = (Node*)pSender;
    int tag = node->getTag();
    LineupLayer::show(SCENE_TAG_MAINUI,tag+1,0);
}
void ArenaTeamLayer::onSelectedBtnClick(Ref* pSender)
{
    Node* node = (Node*)pSender;
    m_index = node->getTag();
    requestChoseMsg(m_index+1);
}
//-----------------------------------------------请求服务器-------------------------------------------------------//
void ArenaTeamLayer::requestLineupMsg()
{
    Dialog::showServerLoading();
    ArenaTeamMsg* msg = new ArenaTeamMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;

}
void ArenaTeamLayer::onLineupMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    ArenaLineupDataManager::getInstance()->destroyInstance();
    if(message->messageID == SCENSE_CLIENT_ARENA_ArenaLineupHeroPageResp)
    {
        if(message->state)//返回成功
        {
            
            int currentRank = message->byteStream->getInt();//当前排名
            int combatPower = message->byteStream->getInt();//战斗力
            int currentHonor = message->byteStream->getInt();//当前荣誉之
            int arenaCount = message->byteStream->getInt();//可以挑战次数
            long countDown = message->byteStream->getLong();//多长时间恢复挑战
            int lineupSize = message->byteStream->getByte();
            for (int i = 0; i < lineupSize; i ++)
            {
                ArenaLineupData* data = new ArenaLineupData();
                data->autorelease();
                data->lineupPower = message->byteStream->getInt();
                data->isdefault = message->byteStream->getByte();
                int lineupHeroSize = message->byteStream->getByte();
                for (int j = 0; j<lineupHeroSize; j++) {
                    struct heroDesc _herolist = {0,0,0,0};
                    _herolist.heroDictId=message->byteStream->getInt();
                    _herolist.heroLevel=message->byteStream->getInt();
                    _herolist.heroQuality = message->byteStream->getInt();
                    _herolist.prestige = message->byteStream->getInt();
                    data->herolist.push_back(_herolist);
                }
                ArenaLineupDataManager::getInstance()->addData(data);
            }
            setTableView();
            setTopData(currentRank,combatPower,currentHonor,arenaCount,countDown);
        }
    }

}

void ArenaTeamLayer::requestChoseMsg(int lineupNo)//选中
{
    LineupFightMsg* msg = new LineupFightMsg(lineupNo);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ArenaTeamLayer::onFightMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_LINEUP_LineupSetDefaultResp)
    {
        if(message->state)//创建成功
        {
            string numCard = StringUtils::format("已将阵容%d设为出战阵容",m_index+1);
//            setTableView();
            NoticeManager::getInstance()->showNotice(numCard.c_str());
            ArenaLineupDataManager::getInstance()->lineupList->at(m_index)->isdefault = 1;
            ArenaLineupDataManager::getInstance()->lineupList->at(m_oldIndex)->isdefault = 0;
            setTableView();
            
        }
    }
}
void ArenaTeamLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupSetDefaultResp).c_str(), CC_CALLBACK_1(ArenaTeamLayer::onFightMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaLineupHeroPageResp).c_str(), CC_CALLBACK_1(ArenaTeamLayer::onLineupMsgProcess, this));
}