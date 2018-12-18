//
//  FinderHeroListLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/25.
//
//

#include "FinderHeroListLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../message/Decoding/market/FindHeroListMsg/FindHeroListMsg.h"
#include "../../../message/Decoding/market/ChoseFinderMsg/FindChoseFinderMsg.h"
#include "../MarketLayer.h"
#include "../marketData/marketFindDataManager.h"
#include "../../generals/generalsCard/GeneralsCard_Layer.h"
#include "../../generals/data/CardDataManager.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
FinderHeroListLayer::FinderHeroListLayer()
:listBg(NULL)
,TAG_TABLEVIEW(3)
,_tableView(NULL)
,m_findId(0)
{
    heroList=new Vector<MarketFinderList*>();
    
}

FinderHeroListLayer:: ~ FinderHeroListLayer()
{
    heroList->clear();
    CC_SAFE_DELETE(heroList);
}

bool FinderHeroListLayer::init(int findId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        m_findId = findId;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG,Point::ZERO,true);
        setBg();
        
        requestListMsg();
        bref = true;
    } while (false);
    return bref;
}

FinderHeroListLayer* FinderHeroListLayer::create(int findId)
{
    FinderHeroListLayer* list = new FinderHeroListLayer();
    if(list && list->init(findId))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void FinderHeroListLayer::show(int idx)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    FinderHeroListLayer* layer = FinderHeroListLayer::create(idx);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void FinderHeroListLayer::onEnter()
{
    BaseLayer::onEnter();
}
void FinderHeroListLayer::onExit()
{
    BaseLayer::onExit();
}
void FinderHeroListLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
void FinderHeroListLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumOkLookFor);
}

void FinderHeroListLayer::setBg()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1);
    this->setContentSize(listBg->getContentSize());

    //按钮
//    const char* pathList[3] = {IMG_PUBLIC_LABEL_LEVE2_FIRST,IMG_PUBLIC_LABEL_MASS2_FIRST,IMG_PUBLIC_LABEL_PRESTIGE2_FIRST};
//    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 16, CC_CALLBACK_1(FinderHeroListLayer::onTopComboBoxClick, this));
//    for (int i = 0; i<3; i++) {
//        boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_FRIST1, IMG_PUBLIC_COMBOBOX_FRIST2, pathList[i]);
//    }
//    boxBtn->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(boxBtn);
//    boxBtn->setPosition(10*sx  ,listBg->getContentSize().height);
//    boxBtn->getButtonAt(0)->selected();
//    this->addChild(boxBtn,1);
    
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listBg2);
    listBg2->setPosition(listBg->getPositionX()+15*sx,listBg->getPositionY()+450*sx);
    this->addChild(listBg2,3);
    
    const char* pathList[3] = {IMG_PUBLIC_LABEL_LEVEL,IMG_PUBLIC_LABEL_QUALITY,IMG_PUBLIC_LABEL_PRESTIGE};
    const char* pathList2[3] = {IMG_PUBLIC_LABEL_LEVEL1,IMG_PUBLIC_LABEL_QUALITY1,IMG_PUBLIC_LABEL_PRESTIGE1};
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(FinderHeroListLayer::onTopComboBoxClick, this));
    for (int i = 0; i<3; i++) {
        boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathList[i], pathList2[i]);
    }
    boxBtn->setAnchorPoint(Point::ZERO);
    boxBtn->setPosition(10*sx,(listBg2->getContentSize().height/sx-boxBtn->getContentSize().height)/2+5*sx);
    boxBtn->getButtonAt(0)->selected();
    listBg2->addChild(boxBtn,3);
}

void FinderHeroListLayer::createTableView()
{
//    listBg->removeChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3-100;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(32,50);
    _tableView->reloadData();
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
}


Sprite* FinderHeroListLayer::singleList(ssize_t idx)
{
    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    if(idx >=heroList->size())
    {
        return NULL;
    }
    //头像
    DictHero* dictHero = DictHeroManager::getInstance()->getData(heroList->at(idx)->heroDictId);
    if (dictHero) {
        UserHeadLayer* userHead=UserHeadLayer::create(dictHero->resource.c_str(),heroList->at(idx)->quality);
        userHead->setHeadInfo(heroList->at(idx)->leadership, heroList->at(idx)->prestige);
        userHead->setPosition(28,28);
        layerBg->addChild(userHead,2,idx);
        userHead->addTouchBegainCallBack(this, callfuncN_selector(FinderHeroListLayer::onUserClick));
    }
    
    //势力force
    char stt[100]="";
    int typeNum =  DictHeroManager::getInstance()->getData(heroList->at(idx)->heroDictId)->attackType;
    if (typeNum<1) {
        typeNum = 1;
    }
    sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
//    sprintf(stt,IMG_PUBLIC_HEROINFO_FORCE,heroList->at(idx)->force);
    Sprite* force=Sprite::create(stt);
    force->setAnchorPoint(Point::ZERO);
     force->setScale(0.7);
    force->setPosition(150,(layerBg->getContentSize().height-force->getContentSize().height)+10);
    layerBg->addChild(force,2);
    
    //名字
    string name= heroList->at(idx)->heroName;
    Label* nameLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),22,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(200,(layerBg->getContentSize().height-nameLabel->getContentSize().height)-20);
    layerBg->addChild(nameLabel);
    
    //列表战力
    Sprite* listMilitary=Sprite::create(IMG_PUBLIC_MILITARY);
    listMilitary->setAnchorPoint(Point::ZERO);
    listMilitary->setPosition(150,70);
    layerBg->addChild(listMilitary,1);
    //列表战力数值
    int combat= heroList->at(idx)->combatPower;
    string combatStr=PublicShowUI::numberToString(combat);
    Label* combatLabel = PublicShowUI::getLabel(combatStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),16,false,false);
    combatLabel->setAnchorPoint(Point::ZERO);
    combatLabel->setPosition(70,(listMilitary->getContentSize().height-combatLabel->getContentSize().height)/2);
    listMilitary->addChild(combatLabel);
    
    //列表领导力
    Sprite* listLead=Sprite::create(IMG_PUBLIC_LAYER_LEAD);
    listLead->setAnchorPoint(Point::ZERO);
    listLead->setPosition(150,20);
    layerBg->addChild(listLead,1);
    //列表领导力数值
    int leader= heroList->at(idx)->leadership;
    string leaderStr=PublicShowUI::numberToString(leader);
    Label* leaderLabel = PublicShowUI::getLabel(leaderStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    leaderLabel->setAnchorPoint(Point::ZERO);
    leaderLabel->setPosition(92,(listLead->getContentSize().height-leaderLabel->getContentSize().height)/2);
    listLead->addChild(leaderLabel);
    
    Sprite* shangbtn = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    shangbtn->setAnchorPoint(Point::ZERO);
    shangbtn->setPosition(layerBg->getContentSize().width-shangbtn->getContentSize().width-10,20);
    layerBg->addChild(shangbtn,2);
    TouchSprite *shangzhen = TouchSprite::createWithPic(IMG_MARKET_MARKETFIND_FINDWORD,this,callfuncN_selector(FinderHeroListLayer::onxunfangnClick));
    shangzhen->setAnchorPoint(Point::ZERO);
    if(idx == 0)
    {
        GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumOkLookFor);
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumOkLookFor, shangzhen);
    }
    shangzhen->setSwallowTouches(false);
    shangzhen->setPosition(shangbtn->getPositionX(),shangbtn->getPositionY());
    layerBg->addChild(shangzhen,2,heroList->at(idx)->heroId);
    
    
    return layerBg;
}
void FinderHeroListLayer::onUserClick(Node* pSender)
{
//    CardPropertyData* data = new CardPropertyData;
//    data->heroId = heroList->at(pSender->getTag())->heroId;
//    data->heroDictId = heroList->at(pSender->getTag())->heroDictId;
//    CardDataManager::getInstance()->setPresentData(data);
//    GeneralsCard_Layer::show(SCENE_TAG_MARKET, LAYER_WUJIANG_BASE);
}
//选择寻访者
void FinderHeroListLayer::onxunfangnClick(Node* psender)
{
    int heroId = psender->getTag();
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumOkLookFor);
    requestChoseHeroMsg(marketFindDataManager::getInstance()->findList->at(m_findId)->findId,heroId);
}
void FinderHeroListLayer::onTopComboBoxClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    string tempStr="0";
    switch (tag) {
        case 0:
            tempStr="level";
            break;
        case 1:
            tempStr="quality";
            break;
        case 2:
            tempStr="prestige";
            break;
        default:
            break;
    }
    this->sortList(tempStr);
}

TableViewCell* FinderHeroListLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
Size FinderHeroListLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+3.5;
    cellSize.width = temp->getContentSize().width *2+10;
    return cellSize;
}
//获取view的长度
ssize_t FinderHeroListLayer::numberOfCellsInTableView(TableView *table)
{
    ssize_t  now_count =ceil(double(heroList->size()) / 2);
    return now_count;
}
//点击cell事件
void FinderHeroListLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
}
//-----------------------------------------------访问服务器-------------------------------------------------------//

void FinderHeroListLayer::requestListMsg()//发送武将列表消息
{
    FindHeroListMsg* msg = new FindHeroListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void FinderHeroListLayer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_FIND_FindHeroSelPageResp)
    {
        short maxSize = message->byteStream->getShort();
        short heroNum=message->byteStream->getShort();
        for (int i =0; i<heroNum; i++) {
            MarketFinderList* data=new MarketFinderList();
            data->autorelease();
            data->heroId=message->byteStream->getInt();
            data->heroDictId=message->byteStream->getInt();
            data->heroName=message->byteStream->getUTF8();
            data->force= message->byteStream->getByte();
            data->prestige=message->byteStream->getShort();
            data->leadership=message->byteStream->getInt();
            data->combatPower=message->byteStream->getInt();
            data->level=message->byteStream->getInt();
            data->quality=message->byteStream->getInt();
            heroList->pushBack(data);
            data->retain();
        }
        createTableView();
        sortList("level");
        NewPlayerGuild::getInstance()->showNowGuide();
    }
}
void FinderHeroListLayer::requestChoseHeroMsg(int findId,int heroId)//选择寻访者
{
    FindChoseFinderMsg* msg = new FindChoseFinderMsg(findId,heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FinderHeroListLayer::onChoseFinderMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_FIND_FindHeroSelResp)
    {
        if(message->state)
        {
            this->removeFromParent();
            
            MarketLayer::show(SCENE_TAG_MAINUI,MarketLayer::TAG_JUXIAN);
            NewPlayerGuild::getInstance()->showNowGuide();
//            broadMsg(CUSTOM_MARKER_FINDERSTART);
        }
    }
}
void FinderHeroListLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIND_FindHeroSelPageResp).c_str(), CC_CALLBACK_1(FinderHeroListLayer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIND_FindHeroSelResp).c_str(), CC_CALLBACK_1(FinderHeroListLayer::onChoseFinderMsgProcess, this));
}
void FinderHeroListLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

//状态排序
bool sortOnChooseCardPrestige(MarketFinderList* n1, MarketFinderList* n2)
{
    return n1->prestige > n2->prestige ;
}
bool sortOnChooseCardQualityAscend(MarketFinderList* n1, MarketFinderList* n2)//倒序(从大到小)
{
    return n1->quality > n2->quality ;
}
bool sortOnChooseCardQualityDescend(MarketFinderList* n1, MarketFinderList* n2)//倒序(从小到大)
{
    return n1->quality < n2->quality;
}
bool sortOnChooseCardLevel(MarketFinderList* n1, MarketFinderList* n2)
{
    return n1->level > n2->level;
}

void FinderHeroListLayer::sortList(string name)
{
    ssize_t len = heroList->size();
    if (len<=1) {
        return;
    }
    if(name == "prestige" )
    {
        sort(heroList->begin(), heroList->end(),sortOnChooseCardQualityDescend);
        int tempNum=0;
        ssize_t len = heroList->size();
        for (int i=1;i<len;i++) {
            if (heroList->at(i)->quality>2) {
                break;
            }
            tempNum=i;
        }
        sort(heroList->begin(),heroList->find(heroList->at(tempNum)),sortOnChooseCardPrestige);
        if(tempNum < len-1)
        {
            sort(heroList->find(heroList->at(tempNum+1)), heroList->end(),sortOnChooseCardPrestige);
        }
    }
    else if(name == "quality")
    {
        sort(heroList->begin(), heroList->end(),sortOnChooseCardQualityAscend);
    }
    else if(name == "level" )
    {
        sort(heroList->begin(), heroList->end(),sortOnChooseCardQualityDescend);
        sort(heroList->begin(), heroList->end(),sortOnChooseCardLevel);
        
        
    }else if(name=="0")
    {
        return;
    }
    this->createTableView();
}
