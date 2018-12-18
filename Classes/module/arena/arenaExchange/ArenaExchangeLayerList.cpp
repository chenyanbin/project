//
//  ArenaExchangeLayerList.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/10.
//
//

#include "ArenaExchangeLayerList.hpp"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/arena/ArenaExchangeMsg.hpp"
#include "../../../message/Decoding/arena/ExchangeOneMsg.hpp"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../arenaData/ArenaExchangeDataManager.hpp"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../userWealth/UserEquipLayer.h"
ArenaExchangeLayerList::ArenaExchangeLayerList()
:_tableView(NULL)
,TAG_TABLEVIEW(1)
,TAG_TOPNODE(2)
,m_ownGloy(0)
,m_index(0)
,m_baselist(NULL)
,m_isUpdata(false)
,m_custHonnor(0)
,m_currentRank(0)
,m_combatPower(0)
{
    m_baselist = new Vector<BaseTypeData*>();
}
ArenaExchangeLayerList::~ ArenaExchangeLayerList()
{
    m_baselist->clear();
    CC_SAFE_DELETE(m_baselist);
    m_baselist = NULL;
}
bool ArenaExchangeLayerList::init()
{
    bool bref = false;
    do{
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG,Point::ZERO,false);
        this->createLayer();
//        this->createTable();
        
        bref = true;
    }while (false);
    return bref;
}
ArenaExchangeLayerList* ArenaExchangeLayerList::create()
{
    ArenaExchangeLayerList* layer = new ArenaExchangeLayerList();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void ArenaExchangeLayerList::onExit()
{
    BaseLayer::onExit();
}
void ArenaExchangeLayerList::onEnter()
{
    BaseLayer::onEnter();
}
void ArenaExchangeLayerList::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void ArenaExchangeLayerList::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestExchangeMsg(2);
}
void ArenaExchangeLayerList::createLayer()
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    listBg2->setPosition(layerbg->getPositionX()+15,layerbg->getPositionY()+450);
    layerbg->addChild(listBg2,3);
    
    Button* qianwangBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(ArenaExchangeLayerList::onUpdataBtn, this));
    qianwangBtn->setAnchorPoint(Point::ZERO);
    qianwangBtn->setPosition(listBg2->getContentSize().width-qianwangBtn->getContentSize().width-20,listBg2->getContentSize().height/2-qianwangBtn->getContentSize().height/2+10);
    listBg2->addChild(qianwangBtn,1);

    Sprite* seeSpr = Sprite::create(IMG_VIP_BLACKSHOP_SHUAXIN);
    seeSpr->setAnchorPoint(Point::ZERO);
    seeSpr->setPosition(Point::ZERO);
    qianwangBtn->addChild(seeSpr,4);

    
//    Button* serch = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(ArenaExchangeLayerList::onUpdataBtn, this));
//    serch->setAnchorPoint(Point::ZERO);
//    serch->setPosition(listBg2->getContentSize().width-serch->getContentSize().width-20,listBg2->getContentSize().height/2-serch->getContentSize().height/2+10);
//    listBg2->addChild(serch,5);
//    
//    Sprite* serchSpr = Sprite::create(IMG_VIP_BLACKSHOP_SHUAXIN);
//    serchSpr->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(serchSpr);
//    serchSpr->setPosition(layerbg->getContentSize().width-serchSpr->getContentSize().width-30,layerbg->getPositionY()+475);
//    listBg2->addChild(serchSpr,7);
}
void ArenaExchangeLayerList::onUpdataBtn(Ref* pSender)
{
    if(m_custHonnor>m_ownGloy)
    {
        NoticeManager::getInstance()->showNotice("当前荣誉值不够");
        return;
    }
    m_isUpdata = true;
    requestExchangeMsg(1);
}
void ArenaExchangeLayerList::setTopData(int _rank,int _fightPowe,int _honer)
{
    Node* topNode = this->getChildByTag(TAG_TOPNODE);
    if(topNode)
    {
        this->removeChildByTag(TAG_TOPNODE);
    }
    topNode = Node::create();
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
//    topNode->setPosition(30 ,  this->getContentSize().height/GlobalInfo::getInstance()->screenScaleX - curOrderNode->getContentSize().height - 36 );
    
    //刷新消耗的荣誉
    Sprite* reHonnor = Sprite::create(IMG_ICON_HONER);
    reHonnor->setAnchorPoint(Point::ZERO);
    reHonnor->setScale(0.7);
    reHonnor->setPosition(nowHonor->getPositionX()  + nowHonor->getContentSize().width+20,-10);
    topNode->addChild(reHonnor, 0);
    Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(m_custHonnor).c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(nowHonor->getPositionX()  + nowHonor->getContentSize().width + reHonnor->getContentSize().width-30,0);
    topNode->addChild(label);
    topNode->setPosition(30 ,  this->getContentSize().height/GlobalInfo::getInstance()->screenScaleX - curOrderNode->getContentSize().height - 36 );
    
    
}
Node* ArenaExchangeLayerList::getTopNode(const char* titlePath,int value)
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
void ArenaExchangeLayerList::createTable()
{
    Sprite* tablebg = (Sprite*)this->getChildByTag(TAG_BG);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+_size.height/2-5;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(32,48);
    _tableView->reloadData();
    tablebg->addChild(_tableView,2,TAG_TABLEVIEW);
    
}

Sprite* ArenaExchangeLayerList::singleList(int idx)
{
    
    ArenaExchangeData* data = ArenaExchangeDataManager::getInstance()->exchangeList->at(idx);
    Sprite* cellbg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    
    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
    UserEquipLayer* head = UserEquipLayer::create(resource,data->quality,false);
    head->setAnchorPoint(Point::ZERO);
    if (data->itemType == 4) {
        head->setFragment();
    }else if (data->itemType == 3)
    {
        head->setLetterFragment();
    }
    head->setTag(idx);
    head->setPosition(22,26);
    cellbg->addChild(head,1);
    head->addTouchBegainCallBack(this, callfuncN_selector(ArenaExchangeLayerList::onitemClick));
    
    //名字背景
    Sprite* namebg = Sprite::create(IMG_PUBLIC_EQUIP_NAMEBG);
    namebg->setAnchorPoint(Point::ZERO);
    namebg->setPosition(150,110);
    cellbg->addChild(namebg,1);
    string sellnameStr = data->itemName;
    Label* sellnameLabel = PublicShowUI::getLabel(sellnameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),18,false,false);
    sellnameLabel->setAnchorPoint(Point::ZERO );
    sellnameLabel->setPosition(10,2);
    namebg->addChild(sellnameLabel,4);
    //荣誉值
    string gloy = StringUtils::format("荣誉值：%d",data->gloy);
    Label* gloyLabel = PublicShowUI::getLabel(gloy.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    gloyLabel->setAnchorPoint(Point::ZERO);
    gloyLabel->setPosition(sellnameLabel->getPositionX() + sellnameLabel->getContentSize().width +20,sellnameLabel->getPositionY());
    namebg->addChild(gloyLabel,2);
    //内容
    string str =  data->itemDes;
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_BLUE_FLOUR),16,false,false);
    nameLabel->setAnchorPoint(Point(0,1));
    nameLabel->setMaxLineWidth(255);
    nameLabel->setPosition(150,cellbg->getContentSize().height/2+21);
    cellbg->addChild(nameLabel,2);
    
    
//    //今日购买次数
//    string strtime =  "今日购买次数：";
//    Label* timeLabel = PublicShowUI::getLabel(strtime.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),16,false,false);
//    timeLabel->setAnchorPoint(Point::ZERO);
//    timeLabel->setMaxLineWidth(250);
//    timeLabel->setPosition(150,30);
//    cellbg->addChild(timeLabel,2);
//    
//    int timesss = 5;
//    string times = StringUtils::format("%d",timesss);
//    Label* timessLabel = PublicShowUI::getLabel(times.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),16,false,false);
//    timessLabel->setAnchorPoint(Point::ZERO);
//    timessLabel->setPosition(timeLabel->getPositionX()+timeLabel->getContentSize().width,timeLabel->getPositionY());
//    cellbg->addChild(timessLabel,2);
    
    //按钮
    if(data->status == 0)
    {
    Button* qianwangBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(ArenaExchangeLayerList::onExchangeClick, this));
    qianwangBtn->setAnchorPoint(Point::ZERO);
    qianwangBtn->setPosition(cellbg->getContentSize().width-qianwangBtn->getContentSize().width-20,cellbg->getContentSize().height/2-qianwangBtn->getContentSize().height/2-40);
    cellbg->addChild(qianwangBtn,1,idx);
    Sprite* seeSpr = Sprite::create(IMG_PUBLIC_LABEL_EXCHANGE);
    seeSpr->setAnchorPoint(Point::ZERO);
    seeSpr->setPosition(Point::ZERO);
    qianwangBtn->addChild(seeSpr,4);
    }else if (data->status == 1)
    {
        string openlevelStr = "已兑换";
        Label* openlevel = PublicShowUI::getLabel(openlevelStr.c_str(),PublicShowUI::getColor3b(COLOR_LOW_RED),20,false,false);
        openlevel->setAnchorPoint(Point::ZERO);
        openlevel->setPosition(cellbg->getContentSize().width-openlevel->getContentSize().width-20,cellbg->getContentSize().height/2-openlevel->getContentSize().height/2-40);
        cellbg->addChild(openlevel,4);
    }
    
    return cellbg;
}
void ArenaExchangeLayerList::onitemClick(Node* pSender)
{
    
}
void ArenaExchangeLayerList::onExchangeClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    int tag = target->getTag();
    m_index = tag;
    ArenaExchangeData* data = ArenaExchangeDataManager::getInstance()->exchangeList->at(tag);
    int _gloy = data->gloy;
    if (_gloy > m_ownGloy) {
        NoticeManager::getInstance()->showNotice("您当前的荣誉值不够");
        return;
    }
    requestOneExchangeMsg(data->itemId);
}

TableViewCell* ArenaExchangeLayerList::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<2; i++) {
        int tag=(int)idx*2+i;
        Sprite* list = singleList(tag);
        if(!list)
        {
            break;
        }
        list->setAnchorPoint(Point::ZERO);
        list->setPositionX(420*i);
        cell->addChild(list);
        cell->setContentSize(list->getContentSize());
        cell->setTag(tag);
    }
    return cell;
}

//列表大小
Size ArenaExchangeLayerList::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+3.5;
    cellSize.width = temp->getContentSize().width*2+10;
    return cellSize;
}
//获取view的长度
ssize_t ArenaExchangeLayerList::numberOfCellsInTableView(TableView *table)
{
    return ceil(double(ArenaExchangeDataManager::getInstance()->exchangeList->size()) / 2);
    
}
//点击cell事件
void ArenaExchangeLayerList::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
void ArenaExchangeLayerList::scrollViewDidScroll(ScrollView* view)
{
}


//-----------------------------------------------访问服务器-------------------------------------------------------//
void ArenaExchangeLayerList::requestExchangeMsg(int refresh)//荣誉商店页
{
    Dialog::showServerLoading();
    ArenaExchangeMsg* msg = new ArenaExchangeMsg(refresh);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}
void ArenaExchangeLayerList::requestOneExchangeMsg(int itemid)//兑换请求
{
   
    Dialog::showServerLoading();
    ExchangeOneMsg* msg = new ExchangeOneMsg(itemid);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ArenaExchangeLayerList::onExchangeMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_ARENA_ArenaGloryShopResp)
    {
        ArenaExchangeDataManager::getInstance()->destroyInstance();
        if(message->state)//返回成功
        {
            m_currentRank = message->byteStream->getInt();//当前排名
            m_combatPower = message->byteStream->getInt();//战斗力
            m_ownGloy = message->byteStream->getInt();//当前荣誉之
            m_custHonnor = message->byteStream->getInt();//刷新所需荣誉值
            int roleSize = message->byteStream->getByte();
            for (int i = 0; i < roleSize; i ++)
            {
                ArenaExchangeData* data = new ArenaExchangeData();
                data->autorelease();
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemCount = message->byteStream->getByte();
                data->itemName = message->byteStream->getUTF8();
                data->gloy = message->byteStream->getInt();
                data->itemDes = message->byteStream->getUTF8();
                data->quality = message->byteStream->getByte();
                data->status = message->byteStream->getByte();
                ArenaExchangeDataManager::getInstance()->addData(data);
            }
            createTable();
            setTopData(m_currentRank,m_combatPower,m_ownGloy);
            if (m_isUpdata == true) {
                NoticeManager::getInstance()->showNotice("刷新成功");
            }
            
        }
    }
    else if (message->messageID == SCENSE_CLIENT_ARENA_ArenaExchangeResp)
    {
        if(message->state)//返回成功
        {
            if(message->state)//返回成功
            {
                m_baselist->clear();
                BaseTypeData* basedata = new BaseTypeData;
                basedata->autorelease();
                basedata->dataType =ArenaExchangeDataManager::getInstance()->exchangeList->at(m_index)->itemType;
                basedata->dataQuality =ArenaExchangeDataManager::getInstance()->exchangeList->at(m_index)->quality;
                basedata->dataName =ArenaExchangeDataManager::getInstance()->exchangeList->at(m_index)->itemName;
                basedata->dataId =ArenaExchangeDataManager::getInstance()->exchangeList->at(m_index)->itemId;
                basedata->dataCount =ArenaExchangeDataManager::getInstance()->exchangeList->at(m_index)->itemCount;
                m_baselist->pushBack(basedata);
                
                AwardBox_Layer* layer = AwardBox_Layer::create(m_baselist);
                layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
                Scene* scene = Director::getInstance()->getRunningScene();
                scene->addChild(layer);
                
                ArenaExchangeDataManager::getInstance()->exchangeList->at(m_index)->status = 1;
                m_ownGloy -= ArenaExchangeDataManager::getInstance()->exchangeList->at(m_index)->gloy ;
                setTopData(m_currentRank,m_combatPower,m_ownGloy);
                createTable();
            }
        }
    }
}

void ArenaExchangeLayerList::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaGloryShopResp).c_str(), CC_CALLBACK_1(ArenaExchangeLayerList::onExchangeMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaExchangeResp).c_str(), CC_CALLBACK_1(ArenaExchangeLayerList::onExchangeMsgProcess, this));
}
void ArenaExchangeLayerList::removeEventListener()
{
    BaseLayer::removeEventListener();
}