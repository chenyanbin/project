//
//  GeneralsEquipStrong_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/25.
//
//

#include "GeneralsEquipStrong_Layer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../message/Decoding/generals/experience/ChooseCardMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/dictData/DictHeroLevel/DictHeroLevelManager.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../../commonData/dictData/DictEquipHardenCost/DictEquipHardenCostManager.h"
#include "../../../commonData/dictData/DictEquipHardenLevel/DictEquipHardenLevelManager.h"
#include "../../../message/Decoding/generals/equip/EquipStartHardenMsg.h"
//#include "../../../c"

GeneralsEquipStrong_Layer::GeneralsEquipStrong_Layer()
:sx(1)
,TAG_LISTBG(1)
,TAG_TABLEVIEW(2)
,TAG_EXPERIENCELABEL(3)
,TAG_EXPUPDATALABEL(4)
,TAG_CURRENTLV(5)
,TAG_UPLEVEL(6)
,TAG_ADDPRESTIGE(7)
,TAG_CONSUME(8)
,cardId(1)
,cardLeve(1)
,getExperience(0)//当前获得经验；
,upgradeExperience(0)//升级所需经验；
,isDownPoint(Point::ZERO)
,isMoveing(false)
,isClose(false)
{
    equipList=new Vector<BaseEquipData*>();
    
    Vector<BaseEquipData*>* tempList=EquipDataManager::getInstance()->getEquipDataList();
    BaseEquipData* presentData=EquipDataManager::getInstance()->getPresentData();
    //排除所需装备和被穿装备和熔炼品质装备不一样的
    for (BaseEquipData* data: *tempList) {
        if (data->equipId!=presentData->equipId and data->heroName=="" and data->quality==presentData->quality) {
            equipList->pushBack(data);
        }
    }
}
GeneralsEquipStrong_Layer::~GeneralsEquipStrong_Layer()
{
    equipList->clear();
    CC_SAFE_DELETE(equipList);
}

void GeneralsEquipStrong_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsEquipStrong_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsEquipStrong_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void GeneralsEquipStrong_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->setClickEnabled(true);
}
bool GeneralsEquipStrong_Layer::init(int cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_GENERALS_EXPERIENCE_LIST_BG);
//        this->isClickClose = true;
        this->setGrayBg();
        this->createLayer();
        
        bref = true;
    } while (false);
    return bref;
}
GeneralsEquipStrong_Layer* GeneralsEquipStrong_Layer::create(int cardId)
{
    GeneralsEquipStrong_Layer* layer = new GeneralsEquipStrong_Layer();
    if(layer && layer->init(cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void GeneralsEquipStrong_Layer::createLayer()
{
    //确定
    Button* startBtn=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(GeneralsEquipStrong_Layer::onStartExperience, this));
    PublicShowUI::setTargetScale(startBtn);
    startBtn->setAnchorPoint(Point::ZERO);
    startBtn->setPosition(this->getContentSize().width/2+startBtn->getContentSize().width+20*sx,0);
    this->addChild(startBtn,3);
    
    Sprite* startLabel=Sprite::create(IMG_PUBLIC_LABEL_DETERMINE);
    startLabel->setAnchorPoint(Point::ZERO);
    startLabel->setPosition((startBtn->getContentSize().width/sx-startLabel->getContentSize().width)/2,(startBtn->getContentSize().height/sx-startLabel->getContentSize().height)/2);
    startBtn->addChild(startLabel,3);
    
    Sprite* label1=Sprite::create(IMG_GENERALS_SMELT_LABEL1);
    label1->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(label1);
    label1->setPosition((this->getContentSize().width-label1->getContentSize().width)/2,this->getContentSize().height-label1->getContentSize().height-15*sx);
    this->addChild(label1);
    
    Sprite* label2=Sprite::create(IMG_GENERALS_SMELT_LABEL2);
    label2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(label2);
    label2->setPosition(35*sx,23*sx);
    this->addChild(label2);
    
    this->initTableView();
}
void GeneralsEquipStrong_Layer::onStartExperience(Ref* psender)
{
    EquipDataManager::getInstance()->clearCardList();
    int listSize=(int)equipList->size();
    for (int i=0; i<listSize; i++) {
        BaseEquipData* equipData=equipList->at(i);
        if (equipData->cardOldLocation>0) {
            EquipDataManager::getInstance()->addData(equipData);
        }
        equipData->cardLocation=equipData->cardOldLocation;
    }
    this->broadMsg(CUSTOM_CHOOSE_CARD_OVER_FUN);
}

//--------------------------------列表部分-------------------------------------------------------//
void GeneralsEquipStrong_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3-43;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition(40*sx,102*sx);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(0*sx,86*sx);
    this->addChild(shade,3);
    
}
TableViewCell* GeneralsEquipStrong_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<5; i++) {
        int tag=(int)idx*5+i;
        if (equipList->size()>tag) {
            UserEquipLayer* userHead=UserEquipLayer::create(equipList->at(tag)->resource,equipList->at(tag)->quality);
            userHead->setHeadNumber(equipList->at(tag)->cardLocation);
            userHead->setHeadInfo(equipList->at(tag)->equipLevel);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(GeneralsEquipStrong_Layer::onUserClick));
            userHead->setPosition(5+136*i,5);
            cell->addChild(userHead,1,tag);
        }
    }
    return cell;
}

//列表大小
Size GeneralsEquipStrong_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,1);
    Sprite* headBox=Sprite::create(stt);
    cellSize.height=headBox->getContentSize().height+5;
    cellSize.width=(headBox->getContentSize().width+15)*5;
    return cellSize;
}
//获取view的长度
ssize_t GeneralsEquipStrong_Layer::numberOfCellsInTableView(TableView *table)
{
    int count = ceil((float)equipList->size()/(float)5);
    return count;
}
//点击cell事件
void GeneralsEquipStrong_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = false;
}
void GeneralsEquipStrong_Layer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
//////////////------------------------------------------------------------------------------//////////////////

void GeneralsEquipStrong_Layer::onUserClick(Node* pSender)
{
    if(isMoveing)
    {
        return;
    }
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=(_size.height*3-10)*sx;
    _size.width=_size.width*sx;
    Rect bb=Rect(_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_size.width, _size.height);
    if (!bb.containsPoint(isDownPoint)) {
        return;
    }
    
    UserEquipLayer* equip=(UserEquipLayer*)pSender;
    int tag=equip->getTag();
    BaseEquipData* equipData=equipList->at(tag);
    if (equipData->cardOldLocation==0) {
        equipData->cardOldLocation=countLeastLocation();
    }else
    {
        equipData->cardOldLocation=0;
    }
    equip->setHeadNumber(equipData->cardOldLocation);
}
int GeneralsEquipStrong_Layer::countLeastLocation()
{
    int listSize=(int)equipList->size();
    for (int i=0; i<6; i++) {
        for (int j=0; j<listSize; j++) {
            if (equipList->at(j)->cardOldLocation==i+1) {
                break;
            }
            if (j+1==listSize) {
                return i+1;
            }
        }
    }
    return 0;
}

bool GeneralsEquipStrong_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{
    Rect rect = this->getBoundingBox();
    this->isClose=true;
    if(rect.containsPoint(touch->getLocation()) == true)
    {
        this->isClose=false;
    }
    
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void GeneralsEquipStrong_Layer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if (touch->getDelta().x>10 or touch->getDelta().y>10) {
        isMoveing=true;
    }
}
void GeneralsEquipStrong_Layer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
    if (this->isClose) {
        Rect rect = this->getBoundingBox();
        if(rect.containsPoint(touch->getLocation()) == false)
        {
            int listSize=(int)equipList->size();
            for (int i=0; i<listSize; i++) {
                BaseEquipData* equipData=equipList->at(i);
                equipData->cardOldLocation=equipData->cardLocation;
            }
            this->removeFromParent();
            
        }
    }
    
}


void GeneralsEquipStrong_Layer::addEventListener()
{
//    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroMaterialSelPageResp).c_str(), CC_CALLBACK_1(GeneralsEquipStrong::onMsgProcess, this));
}
void GeneralsEquipStrong_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}