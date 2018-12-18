//
//  generalsHeroList_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/17.
//
//

#include "GeneralsHeroList_Layer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/data/FunctionOpenManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../data/CardDataManager.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../message/Decoding/generals/letter/LetterPageMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/heroListMsg/heroListMsg.h"
#include "../generalsCard/GeneralsCard_Layer.h"
#include "../data/CardDataManager.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../Generals_Sell_Layer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
GeneralsHeroList_Layer::GeneralsHeroList_Layer()
:TAG_TABLEVIEW(1)
,TAG_LATTERNUM(2)
,TAG_LISTBG(3)
,sx(1)
,titleCount(0)
,isDownPoint(Point::ZERO)
,isMoveing(false)
,sortMode("level")
,maxHero(0)
,equipNumLabel(NULL)
,isTouchHero(false)
{
    
}
GeneralsHeroList_Layer::~GeneralsHeroList_Layer()
{
    
}
GeneralsHeroList_Layer* GeneralsHeroList_Layer::create()
{
    GeneralsHeroList_Layer* layer = new GeneralsHeroList_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
bool GeneralsHeroList_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx= GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG);
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
void GeneralsHeroList_Layer::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void GeneralsHeroList_Layer::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void GeneralsHeroList_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
void GeneralsHeroList_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumGeneralsHead);
}
void GeneralsHeroList_Layer::createLayer()
{
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    if (listBg) {

        
        Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
        listBg2->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(listBg2);
        listBg2->setPosition(listBg->getPositionX()+15*sx,listBg->getPositionY()+450*sx);
        this->addChild(listBg2,3);
        
        const char* pathList[3] = {IMG_PUBLIC_LABEL_LEVEL,IMG_PUBLIC_LABEL_QUALITY,IMG_PUBLIC_LABEL_PRESTIGE};
        const char* pathList2[3] = {IMG_PUBLIC_LABEL_LEVEL1,IMG_PUBLIC_LABEL_QUALITY1,IMG_PUBLIC_LABEL_PRESTIGE1};
        ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(GeneralsHeroList_Layer::onTopComboBoxClick, this));
        for (int i = 0; i<3; i++) {
            //        boxBtn->addBtn(pathList[i], pathList2[i], "");
            boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathList[i], pathList2[i]);
        }
        boxBtn->setAnchorPoint(Point::ZERO);
        boxBtn->setPosition(10*sx,(listBg2->getContentSize().height/sx-boxBtn->getContentSize().height)/2 + 5*sx);
        boxBtn->getButtonAt(0)->selected();
        listBg2->addChild(boxBtn,3);

        Sprite* equipNumSprite=Sprite::create(IMG_PUBLIC_LABEL_ALLHERO);
        equipNumSprite->setAnchorPoint(Point::ZERO);
        equipNumSprite->setPosition(620,(listBg2->getContentSize().height/sx-equipNumSprite->getContentSize().height)/2+5);
        listBg2->addChild(equipNumSprite);
        
        string numStr="0/0";
        equipNumLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
        equipNumLabel->setAnchorPoint(Point::ZERO);
        equipNumLabel->setPosition(equipNumSprite->getContentSize().width+equipNumSprite->getPositionX()+10,(listBg2->getContentSize().height/sx-equipNumLabel->getContentSize().height)/2+5);
        listBg2->addChild(equipNumLabel,1);
        
//        //出售
//        Button* sellBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsHeroList_Layer::onSellBtnClick, this));
//        sellBtn->setPosition(listBg2->getContentSize().width/sx-sellBtn->getContentSize().width/2-30,listBg2->getContentSize().height/sx/2+10);
//        listBg2->addChild(sellBtn,1);
//        
//        Sprite* sellLabel=Sprite::create(IMG_PUBLIC_LABEL_SELL);
//        sellBtn->addChild(sellLabel,2);
    }
}
void GeneralsHeroList_Layer::updataCreat()
{
    string numStr=PublicShowUI::numberToString((int)CardDataManager::getInstance()->getHeroDataList()->size())+"/"+PublicShowUI::numberToString(maxHero);
    equipNumLabel->setString(numStr);
}
void GeneralsHeroList_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    //
    if(_tableView)
    {
        _tableView->reloadData();
        return;
    }
    
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+_size.height/2-35;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    if (listBg) {
        _tableView->setPosition(listBg->getPositionX()+30*sx,listBg->getPositionY()+60*sx);
    }
    this->addChild(_tableView,2,TAG_TABLEVIEW);

    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(6*sx,40*sx);
    this->addChild(shade,3);
    
}
void GeneralsHeroList_Layer::onTopComboBoxClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    switch (tag) {
        case 0:
            sortMode="level";
            break;
        case 1:
            sortMode="quality";
            break;
        case 2:
            sortMode="prestige";
            break;
        default:
            break;
    }
    this->sortList(sortMode);
}
void GeneralsHeroList_Layer::onHeadClick(Ref* pSender)
{
    if (isMoveing) {
        return;
    }
        Node* target = (Node*)pSender;
    int index = target->getTag();
    log("%d",index);
    CardDataManager::getInstance()->setPresentData(CardDataManager::getInstance()->getHeroDataList()->at(index));
    
    bool openBol= FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumEquip) ;
    

    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_tableView->getContentSize().width;
    _size.width=_tableView->getContentSize().height;
//    isDownPoint.x = isDownPoint.x/GlobalInfo::getInstance()->screenScaleX;
//    isDownPoint.y = isDownPoint.y/GlobalInfo::getInstance()->screenScaleX;
    
    log("%f,%f,%f,%f",_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_tableView->getContentSize().width,_tableView->getContentSize().height);
    log("%f,%f",isDownPoint.x,isDownPoint.y);
    log("%f,%f",GlobalInfo::getInstance()->screenScaleX,GlobalInfo::getInstance()->screenScaleY);
    
    Rect bb=Rect(_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_size.width, _size.height);
    if (bb.containsPoint(isDownPoint) || openBol ) {
        GeneralsCard_Layer::show(SCENE_TAG_MAINUI, DictFunctionEnumEquip,sortMode);
    }
    
    
//    isTouchHero=true;
//    Sprite* node=(Sprite*)pSender;
//    int tag=node->getTag();
//    CardDataManager::getInstance()->setPresentData(CardDataManager::getInstance()->getHeroDataList()->at(tag));
//    bool openBol= FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumEquip) ;
//    if (isTouchHero and openBol) {
//        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumGeneralsHead);
//        GeneralsCard_Layer::show(SCENE_TAG_MAINUI, DictFunctionEnumEquip,sortMode);
//    }
//    isTouchHero=false;
}
void GeneralsHeroList_Layer::onSellBtnClick(Ref* psender)
{
    Generals_Sell_Layer* layer=Generals_Sell_Layer::create(1);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
    Scene* scene=Director::getInstance()->getRunningScene();
    scene->addChild(layer);
    
}

//-------------------------------------------------TableView部分-------------------------------------------------//
//单个列表内容
Button* GeneralsHeroList_Layer::singleList(ssize_t idx)
{
    CardPropertyData* data =CardDataManager::getInstance()->getHeroDataByIndex((int)idx);
    Button*layerBg = Button::create(IMG_PUBLIC_LAYER_TWO_CELLBG,IMG_PUBLIC_LAYER_TWO_CELLBG,CC_CALLBACK_1(GeneralsHeroList_Layer::onHeadClick, this));
    layerBg->setAnchorPoint(Point::ZERO);
    layerBg->getTouchListener()->setSwallowTouches(false);
    layerBg->setTag((int)idx);
   
    //头像
    int tag=(int)idx+10000;
    int temp=data->heroDictId;
    DictHero* dictHero = DictHeroManager::getInstance()->getData(temp);
    if (!dictHero) {
        return NULL;
    }
    UserHeadLayer* head=UserHeadLayer::create(dictHero->resource.c_str(),data->quality);
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(27,30);
    layerBg->addChild(head,2,tag);
    head->setHeadInfo(data->level, data->prestige);
    if(idx == 0)
    {
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumGeneralsHead, head);
    }
    //名字背景
    Sprite* nameBg=Sprite::create(IMG_PUBLIC_EQUIP_NAMEBG);
    nameBg->setAnchorPoint(Point::ZERO);
    nameBg->setPosition(145,(layerBg->getContentSize().height-nameBg->getContentSize().height)-18);
    layerBg->addChild(nameBg,2);
    //名字
    string name="";
    DictHeroQuality* qualityData=DictHeroQualityManager::getInstance()->getData(data->quality);
    name= data->heroName;
    if (qualityData) {
        name=qualityData->name+"  "+data->heroName;
    }
    Label* nameLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(200,(layerBg->getContentSize().height-nameLabel->getContentSize().height)-18);
    layerBg->addChild(nameLabel,2);
    
    //势力heroForce
    char stt[100]="";
    int typeNum =  DictHeroManager::getInstance()->getData(data->heroDictId)->attackType;
    if (typeNum<1) {
        typeNum = 1;
    }
    sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
    Sprite* force=Sprite::create(stt);
    force->setAnchorPoint(Point::ZERO);
    force->setScale(0.7);
    force->setPosition(150,nameLabel->getPositionY()-13);
    layerBg->addChild(force,2);
    
    //列表战力
    Sprite* listMilitary=Sprite::create(IMG_PUBLIC_MILITARY);
    listMilitary->setAnchorPoint(Point::ZERO);
    listMilitary->setPosition(160,23.5);
    layerBg->addChild(listMilitary,2);
    
    //列表战力数值
    int combat= data->combatPower;
    string combatStr=PublicShowUI::numberToString(combat);
    
    Label* combatLabel = PublicShowUI::getLabel(combatStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),16,false,false);
    combatLabel->setAnchorPoint(Point::ZERO);
    combatLabel->setPosition(70,(listMilitary->getContentSize().height-combatLabel->getContentSize().height)/2);
    listMilitary->addChild(combatLabel);
    
    //领导力星星
    Sprite* listStar=Sprite::create(IMG_PUBLIC_LAYER_STAR);
    listStar->setAnchorPoint(Point::ZERO);
    listStar->setPosition(160,(layerBg->getContentSize().height-listStar->getContentSize().height)/2);
    layerBg->addChild(listStar,2);
    //列表领导力
    Sprite* listLead=Sprite::create(IMG_PUBLIC_LAYER_LEAD);
    listLead->setAnchorPoint(Point::ZERO);
    listLead->setPosition(200,(layerBg->getContentSize().height-listLead->getContentSize().height)/2);
    layerBg->addChild(listLead,2);
    //列表领导力数值
    short leader= data->leadership;
    string leaderStr=PublicShowUI::numberToString(leader);
    Label* leaderLabel = PublicShowUI::getLabel(leaderStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    leaderLabel->setAnchorPoint(Point(0.5,0.5));
    leaderLabel->setPosition(listStar->getContentSize().width/2,listStar->getContentSize().height/2);
    listStar->addChild(leaderLabel);
    
    return layerBg;
}
//--------------------------------列表部分-------------------------------------------------------//
TableViewCell* GeneralsHeroList_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<2; i++) {
        if (idx*2+i<CardDataManager::getInstance()->getHeroDataList()->size()) {
            Button* list=singleList(idx*2+i);
            list->setPosition(i*(list->getContentSize().width+8),0);
            cell->addChild(list,1);
        }
    }
    return cell;
}

//列表大小
Size GeneralsHeroList_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+8;
    cellSize.width = temp->getContentSize().width *2+10;
    return cellSize;
}
//获取view的长度
ssize_t GeneralsHeroList_Layer::numberOfCellsInTableView(TableView *table)
{
    float allList=CardDataManager::getInstance()->getHeroDataList()->size();
    titleCount=ceil(allList/2);
    return titleCount;
}
//点击cell事件
void GeneralsHeroList_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
//    bool openBol= FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumEquip) ;
//    if (isTouchHero and openBol) {
//        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumGeneralsHead);
//        GeneralsCard_Layer::show(SCENE_TAG_MAINUI, DictFunctionEnumEquip,sortMode);
//    }
//    isTouchHero=false;
    isMoveing = false;
}
void GeneralsHeroList_Layer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
  
}
void GeneralsHeroList_Layer::scrollViewDidZoom(ScrollView* view)
{
//    log("dddddddddddddddddddddddddddddd");
}
//-------------------------------------------------服务器部分----------------------------------------------------//
void GeneralsHeroList_Layer::requestListMsg(EventCustom* evt)
{
    
    heroListMsg* msg = new heroListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsHeroList_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_HERO_HeroListPageResp)
    {
        CardDataManager::getInstance()->clearHeroList();
        maxHero=message->byteStream->getShort();
        short heroNum=message->byteStream->getShort();
        for (int i =0; i<heroNum; i++) {
            CardPropertyData* data=new CardPropertyData();
            data->heroId=message->byteStream->getInt();
            data->heroDictId=message->byteStream->getInt();
            data->heroName=message->byteStream->getUTF8();
            data->prestige=message->byteStream->getShort();
            data->leadership=message->byteStream->getInt();
            data->combatPower=message->byteStream->getInt();
            data->level=message->byteStream->getInt();
            data->quality=message->byteStream->getInt();
            data->heroForce=message->byteStream->getByte();
            DictHero* heroData=DictHeroManager::getInstance()->getData(data->heroDictId);
            if (heroData) {
                data->backPackOrder=heroData->seq;
            }
            CardDataManager::getInstance()->addHeroData(data);
        }
        this->sortList(sortMode);
        NewPlayerGuild::getInstance()->showNowGuide();
        this->updataCreat();
    }

}
void GeneralsHeroList_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroListPageResp).c_str(), CC_CALLBACK_1(GeneralsHeroList_Layer::onMsgProcess, this));
    addUserMsg(CUSTOM_CHOOSE_HERO_FUN,CC_CALLBACK_1(GeneralsHeroList_Layer::requestListMsg, this));
    
    addUserMsg(CUSTOM_SELL_HERO,CC_CALLBACK_1(GeneralsHeroList_Layer::requestListMsg, this));
}
void GeneralsHeroList_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
//排序
//状态排序
bool sortOnHeroListPrestige(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->prestige > n2->prestige;
}
bool sortOnHeroListQualityAscend(CardPropertyData* n1, CardPropertyData* n2)//正序(从大到小)
{
    return n1->quality > n2->quality;
}
bool sortOnHeroListQualityDescend(CardPropertyData* n1, CardPropertyData* n2)//倒序(从小到大)
{
    return n1->quality < n2->quality;
}
bool sortOnHeroListLevel(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->level > n2->level;
}
bool sortOnHeroListPackOrder(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->backPackOrder < n2->backPackOrder;
}
//排序
void GeneralsHeroList_Layer::sortList(string name)
{
    Vector<CardPropertyData*>* list=CardDataManager::getInstance()->getHeroDataList();
    if(name == "prestige" )
    {
        stable_sort(list->begin(), list->end(),sortOnHeroListPackOrder);
        stable_sort(list->begin(), list->end(),sortOnHeroListQualityAscend);
        stable_sort(list->begin(), list->end(),sortOnHeroListLevel);
        stable_sort(list->begin(), list->end(),sortOnHeroListPrestige);
    }
    else if(name == "quality")
    {
        stable_sort(list->begin(), list->end(),sortOnHeroListPackOrder);
        stable_sort(list->begin(), list->end(),sortOnHeroListLevel);
        stable_sort(list->begin(), list->end(),sortOnHeroListQualityAscend);
    }
    else if(name == "level" )
    {
        stable_sort(list->begin(), list->end(),sortOnHeroListPackOrder);
        stable_sort(list->begin(), list->end(),sortOnHeroListQualityAscend);
        stable_sort(list->begin(), list->end(),sortOnHeroListLevel);
    }else if (name=="0")
    {
        return;
    }
    this->initTableView();
    
}
bool GeneralsHeroList_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void GeneralsHeroList_Layer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
    
 
}
void GeneralsHeroList_Layer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
}
