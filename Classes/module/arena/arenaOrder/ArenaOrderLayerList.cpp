//
//  ArenaOrderLayerList.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/9.
//
//

#include "ArenaOrderLayerList.hpp"
//
//  RankPriceLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/6.
//
//

#include "../../rank/RankPriceLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../userWealth/UserWealthLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../commonData/dictData/DictLegendRank/DictLegendRankManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../avatar/hero/Hero.h"
#include "../../tips/TipsLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/dictData/DictItemBook/DictItemBookManager.h"
#include "../../../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
#include "../../../commonData/dictData/DictItemHero/DictItemHeroManager.h"
#include "../../../commonData/dictData/DictItemMater/DictItemMaterManager.h"
#include "../../../commonData/dictData/DictItem/DictItemManager.h"
#include "../../../commonData/dictData/DictResource/DictResourceManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../arenaData/ArenaDataManager.hpp"
#include "../../../message/Decoding/arena/ArenaRankMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "ArenaOtherDetailsLayer.hpp"
ArenaOrderLayerList::ArenaOrderLayerList()
:_tableView(NULL)
,TAG_TABLEVIEW(1)
,TAG_PERDETAILBG(2)
,m_myRank(0)
,m_tableView(Point::ZERO)
{
    
} 
ArenaOrderLayerList::~ ArenaOrderLayerList()
{
    
}
void ArenaOrderLayerList::onExit()
{
    BaseLayer::onExit();
}
void ArenaOrderLayerList::onEnter()
{
    BaseLayer::onEnter();
}
void ArenaOrderLayerList::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void ArenaOrderLayerList::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
    requestRankMsg();
//    createTable();
//    this->setTopData();
}
bool ArenaOrderLayerList::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
    
        this->isAnimation = false;
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG,Point::ZERO,false);
        this->createLayer();
        
        bref = true;
    } while (false);
    return bref;
}
ArenaOrderLayerList* ArenaOrderLayerList::create()
{
    ArenaOrderLayerList* layer = new ArenaOrderLayerList();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}

void ArenaOrderLayerList::createLayer()
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
   
    
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    listBg2->setPosition(layerbg->getPositionX()+15,layerbg->getPositionY()+450);
    layerbg->addChild(listBg2,3);
    
    //饿哦的排行
//    Button* qianwangBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE, "", CC_CALLBACK_1(ArenaOrderLayerList::onSeeMeClick, this));
//    qianwangBtn->setAnchorPoint(Point::ZERO);
//    qianwangBtn->setPosition(listBg2->getContentSize().width-qianwangBtn->getContentSize().width-20,listBg2->getContentSize().height/2-qianwangBtn->getContentSize().height/2+10);
//    listBg2->addChild(qianwangBtn,1);
//    
//    Sprite* seeSpr = Sprite::create(IMG_PUBLIC_LABEL_MYRANK);
//    seeSpr->setAnchorPoint(Point::ZERO);
//    seeSpr->setPosition(Point::ZERO);
//    qianwangBtn->addChild(seeSpr,4);
    
    
}
void ArenaOrderLayerList::setTopData(int _rank,int _fightPowe,int _honer,long _fightTimes,long _time)
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
        
        //    Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(value).c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
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
    topNode->addChild(raceCountNode, 0);
    topNode->setPosition(30 ,  this->getContentSize().height/GlobalInfo::getInstance()->screenScaleX - curOrderNode->getContentSize().height - 36 );
    
}
Node* ArenaOrderLayerList::getTopNode(const char* titlePath,int value)
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
//-----------------------------------------------tableView------------------------------------------------------//
void ArenaOrderLayerList::createTable()
{
    Sprite* tablebg = (Sprite*)this->getChildByTag(TAG_BG);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        m_tableView = cp;
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3-5;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(32,53);
    _tableView->reloadData();
    tablebg->addChild(_tableView,2,TAG_TABLEVIEW);
    m_tableView = _tableView->getContentOffset();
}

Sprite* ArenaOrderLayerList::singleList(int idx)
{
    Sprite* cellbg = Sprite::create(IMG_PUBLIC_LAYER_RANKCELLBG);
    
    ArenaListData* data = ArenaDataManager::getInstance()->arenaList->at(idx);
    
    DictHero* dictMonster = DictHeroManager::getInstance()->getData(data->heroDictId);
    const char* path = dictMonster ? dictMonster->headResource.c_str() : "zhaoyun";
    path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,path);
    Sprite* head = Sprite::create(path);
    if (head) {
//        head->setAnchorPoint(Point::ZERO);
//        cellbg->addChild(head,1);
//        head->setPosition(37,(cellbg->getContentSize().height - head->getContentSize().height)/2);
       
        Sprite* headbg = Sprite::create(IMG_ARENALIST_HEADBG);
        headbg->setAnchorPoint(Point::ZERO);
        cellbg->addChild(head,1);
        head->setPosition(37,(cellbg->getContentSize().height - head->getContentSize().height)/2);
        
        head->setAnchorPoint(Point::ZERO);
        cellbg->addChild(head,2);
        head->setPosition(37,(cellbg->getContentSize().height - head->getContentSize().height)/2);
        
        Sprite* headbox = Sprite::create(IMG_ARENALIST_HEADBOX);
        headbox->setAnchorPoint(Point::ZERO);
        headbox->setScale(0.9);
        cellbg->addChild(headbox,3);
        headbox->setPosition(37,(cellbg->getContentSize().height - head->getContentSize().height)/2);
    }
    
    
    
    
    
    //名字背景
    Sprite*titlebg = Sprite::create(IMG_PUBLIC_LAYER__CELLTITLEBG);
    titlebg->setAnchorPoint(Point::ZERO);
    titlebg->setPosition(177,cellbg->getContentSize().height - titlebg->getContentSize().height-10);
    cellbg->addChild(titlebg,1);
    
    //名字
    string str =  data->roleName;//"是开发公司哪个快乐是哪个";
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(5,2);
    titlebg->addChild(nameLabel,2);
    
    //boss等级
    str = "LV " + PublicShowUI::numberToString(data->roleLevel);
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),20,false,false);
    label->setAnchorPoint(Point::ZERO);
    titlebg->addChild(label,3);
    label->setPosition(200,nameLabel->getPositionY());
    titlebg->addChild(label,1);
    
    //排名
    Sprite* rank = Sprite::create(IMG_ARENALIST_RANK);
    rank->setAnchorPoint(Point::ZERO);
    rank->setScale(1.1);
    rank->setPosition(label->getPositionX() + label->getContentSize().width+10,label->getPositionY());
    titlebg->addChild(rank);
    string numStr = StringUtils::format("%d",idx+1);
    Label* ranklabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),20,false,false);
    ranklabel->setAnchorPoint(Point::ZERO);
    ranklabel->setPosition(rank->getPositionX() + rank->getContentSize().width+10,label->getPositionY());
    titlebg->addChild(ranklabel,5);
    
    
    //战斗力
    Sprite* fight = Sprite::create(IMG_ARENA_BGE);
    fight->setAnchorPoint(Point::ZERO);
    fight->setPosition(180,40);
    cellbg->addChild(fight);
    string powerStr = StringUtils::format(" %d",data->power);
    Label* powerLabel = PublicShowUI::getLabel(powerStr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),22,false,false);
    powerLabel->setAnchorPoint(Point::ZERO);
    powerLabel->setPosition(fight->getPositionX() + fight->getContentSize().width,fight->getPositionY());
    cellbg->addChild(powerLabel,2);
    
    //排名北京
//    Sprite* rankbg = Sprite::create(IMG_ARENALIST_RANKBG);
//    rankbg->setAnchorPoint(Point::ZERO);
//    rankbg->setPosition(100,10);
//    cellbg->addChild(rankbg,5);
    //排名奖励
//    Sprite* orderPrize = Sprite::create(IMG_ARENA_NOWORDERPRIZE);
//    orderPrize->setAnchorPoint(Point::ZERO);
//    orderPrize->setPosition(180, cellbg->getContentSize().height /2 - orderPrize->getContentSize().height/2-15);
//    cellbg->addChild(orderPrize,3);
//    //荣誉值
//    Sprite* glorySpr = Sprite::create(IMG_ARENA_HONOR);
//    glorySpr->setAnchorPoint(Point::ZERO);
//    string strhoner = PublicShowUI::numberToString(data->honor);
//    Label* gloryLabel = PublicShowUI::getLabel(strhoner.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
//    gloryLabel->setAnchorPoint(Point(0,.5));
//    glorySpr->addChild(gloryLabel,3);
//    gloryLabel->setPosition(glorySpr->getContentSize().width, glorySpr->getContentSize().height/2);
//    glorySpr->setPosition(orderPrize->getPositionX() + orderPrize->getContentSize().width, orderPrize->getPositionY());
//    Size size = glorySpr->getContentSize();
//    size.width = gloryLabel->getPositionX() + gloryLabel->getContentSize().width;
//    glorySpr->setContentSize(size);
//    cellbg->addChild(glorySpr,4);
//    //铜钱
//    Sprite* coinSpr = Sprite::create(IMG_ICON_PUBLIC_COIN);
//    coinSpr->setAnchorPoint(Point::ZERO);
//    str = PublicShowUI::numberToString(data->coin);
//    
//    Label* coinLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
//    coinLabel->setAnchorPoint(Point(0,.5));
//    coinSpr->addChild(coinLabel,3);
//    coinLabel->setPosition(coinSpr->getContentSize().width, coinSpr->getContentSize().height/2);
//    coinSpr->setPosition(glorySpr->getPositionX() + glorySpr->getContentSize().width, glorySpr->getPositionY()-13);
//    size = coinSpr->getContentSize();
//    size.width = coinLabel->getPositionX() + coinLabel->getContentSize().width;
//    coinSpr->setContentSize(size);
//    cellbg->addChild(coinSpr,4);
    
    long herosize = data->heroHeadList.size();
    
    for (int i = 0; i<herosize; i++) {
        DictHero* dictMonster = DictHeroManager::getInstance()->getData(data->heroHeadList.at(i).herodict);
        if (dictMonster) {            
            Sprite* headbg = Sprite::create(IMG_ARENALIST_HEADBG);
            headbg->setAnchorPoint(Point::ZERO);
            headbg->setScale(0.6);
            cellbg->addChild(headbg,1);
            headbg->setPosition(340+i*(headbg->getContentSize().width-10),10);
            
            const char* path = dictMonster ? dictMonster->headResource.c_str() : "zhaoyun";
            path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,path);
            Sprite* head = Sprite::create(path);
            head->setAnchorPoint(Point::ZERO);
            head->setScale(0.65);
            head->setPosition(340+i*(headbg->getContentSize().width-10),10);
            cellbg->addChild(head,2);
            
            
            
            Sprite* headbox = Sprite::create(IMG_ARENALIST_HEADBOX);
            headbox->setAnchorPoint(Point::ZERO);
            headbox->setScale(0.6);
            headbox->setPosition(340+i*(headbg->getContentSize().width-10),10);
            cellbg->addChild(headbox,3);

        }
    }
    
    //按钮
    if (idx+1 != m_myRank) {
        Button* qianwangBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_RED, "", CC_CALLBACK_1(ArenaOrderLayerList::onSeeOtherClick, this));
        qianwangBtn->setAnchorPoint(Point::ZERO);
        qianwangBtn->setPosition(cellbg->getContentSize().width-qianwangBtn->getContentSize().width-20,cellbg->getContentSize().height/2-qianwangBtn->getContentSize().height/2-5);
        cellbg->addChild(qianwangBtn,1,idx);
        Sprite* seeSpr = Sprite::create(IMG_PUBLIC_LABEL_SEEOTHER);
        seeSpr->setAnchorPoint(Point::ZERO);
        seeSpr->setPosition(Point::ZERO);
        qianwangBtn->addChild(seeSpr,4);
    }
    
    
    
    return cellbg;
}
void ArenaOrderLayerList::onSeeMeClick(Ref* pSender)
{
    if (m_myRank<3) {
        return;
    }
    _tableView->stopAllActions();
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_RANKCELLBG);
    cellSize.height = temp->getContentSize().height+3.5;
    
    Point cp =  _tableView->getContentOffset();
    cp.y = m_tableView.y + (m_myRank-2)*cellSize.height;
    log("x ======%f, Y =========== %f",cp.x,cp.y);
    _tableView->setContentOffset(cp);
}
void ArenaOrderLayerList::onSeeOtherClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    int tag = target->getTag();
    if (ArenaDataManager::getInstance()->arenaList->at(tag)->roleId == 0) {
        ArenaOtherDetailsLayer::show(2,ArenaDataManager::getInstance()->arenaList->at(tag)->rank);
    }else{
        ArenaOtherDetailsLayer::show(1,ArenaDataManager::getInstance()->arenaList->at(tag)->roleId);
    }
}


TableViewCell* ArenaOrderLayerList::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Sprite* list=singleList(idx);
    list->setAnchorPoint(Point::ZERO);
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    return cell;
}

//列表大小
Size ArenaOrderLayerList::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_RANKCELLBG);
    cellSize.height = temp->getContentSize().height+3.5;
    cellSize.width = temp->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t ArenaOrderLayerList::numberOfCellsInTableView(TableView *table)
{
    return ArenaDataManager::getInstance()->arenaList->size();
    
}
//点击cell事件
void ArenaOrderLayerList::tableCellTouched(TableView* table, TableViewCell* cell)
{
 
}
void ArenaOrderLayerList::scrollViewDidScroll(ScrollView* view)
{
}


//-----------------------------------------------访问服务器-------------------------------------------------------//
void ArenaOrderLayerList::requestRankMsg()
{
    Dialog::showServerLoading();
    ArenaRankMsg* msg = new ArenaRankMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;

}
void ArenaOrderLayerList::onRankMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    ArenaDataManager::getInstance()->destroyInstance();
    if(message->messageID == SCENSE_CLIENT_ARENA_ArenaRankPageResp)
    {
        if(message->state)//返回成功
        {
            int currentRank = message->byteStream->getInt();//当前排名
            m_myRank = currentRank;
            int combatPower = message->byteStream->getInt();//战斗力
            int currentHonor = message->byteStream->getInt();//当前荣誉之
            int arenaCount = message->byteStream->getInt();//可以挑战次数
            long countDown = message->byteStream->getLong();//多长时间恢复挑战
            int roleSize = message->byteStream->getInt();
            for (int i = 0; i < roleSize; i ++)
            {
                ArenaListData* data = new ArenaListData;
                data->autorelease();
                data->rank = message->byteStream->getInt();
                data->roleId = message->byteStream->getLong();
                data->heroDictId = message->byteStream->getInt();
                data->roleName = message->byteStream->getUTF8();
                data->power = message->byteStream->getInt();
                data->roleLevel = message->byteStream->getInt();
                data->honor = message->byteStream->getInt();
                data->coin = message->byteStream->getInt();
                int herosize = message->byteStream->getByte();
                for (int i = 0; i < herosize; i ++) {
                    struct HeroHead _heroList = {0};
                    _heroList.herodict = message->byteStream->getInt();
                    data->heroHeadList.push_back(_heroList);
                }
                ArenaDataManager::getInstance()->addData(data);
            }
            createTable();
            setTopData(currentRank,combatPower,currentHonor,arenaCount,countDown);
        }
    }
}
void ArenaOrderLayerList::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaRankPageResp).c_str(), CC_CALLBACK_1(ArenaOrderLayerList::onRankMsgProcess, this));
}
void ArenaOrderLayerList::removeEventListener()
{
    BaseLayer::removeEventListener();
}
