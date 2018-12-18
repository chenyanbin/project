//
//  generalsEquip_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/21.
//
//

#include "GeneralsEquip_Layer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/generals/equip/EquipListMsg.h"
#include "../data/EquipDataManager.h"
#include "GeneralsEquip_Scene.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../Generals_Sell_Layer.h"
#include "../../../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
GeneralsEquip_Layer::GeneralsEquip_Layer()
:TAG_TABLEVIEW(1)
,TAG_LATTERNUM(2)
,TAG_LISTBG(3)
,sx(1)
,titleCount(0)
,maxListSize(0)
,isDownPoint(Point::ZERO)
,isMoveing(false)
,equipNumLabel(NULL)
,isTouchEquip(false)
{
}
GeneralsEquip_Layer::~GeneralsEquip_Layer()
{
   
    
}
GeneralsEquip_Layer* GeneralsEquip_Layer::create()
{
    GeneralsEquip_Layer* layer = new GeneralsEquip_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
bool GeneralsEquip_Layer::init()
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
void GeneralsEquip_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsEquip_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsEquip_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
    this->setClickEnabled(true);
}
void GeneralsEquip_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumBelongEquipButton);
}
void GeneralsEquip_Layer::createLayer()
{
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    if (listBg) {
      
        Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
        listBg2->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(listBg2);
        listBg2->setPosition(listBg->getPositionX()+15*sx,listBg->getPositionY()+450*sx);
        this->addChild(listBg2,3);
        
        const char* pathList[3] = {IMG_PUBLIC_LABEL_LEVEL,IMG_PUBLIC_LABEL_QUALITY,IMG_PUBLIC_LABEL_EQUIPMENT};
        const char* pathList2[3] = {IMG_PUBLIC_LABEL_LEVEL1,IMG_PUBLIC_LABEL_QUALITY1,IMG_PUBLIC_LABEL_EQUIPMENT1};
        ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(GeneralsEquip_Layer::onTopComboBoxClick, this));
        for (int i = 0; i<3; i++) {
            //        boxBtn->addBtn(pathList[i], pathList2[i], "");
            boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathList[i], pathList2[i]);
        }
        boxBtn->setAnchorPoint(Point::ZERO);
        boxBtn->setPosition(10*sx,(listBg2->getContentSize().height/sx-boxBtn->getContentSize().height)/2+5*sx);

        boxBtn->getButtonAt(0)->selected();
        listBg2->addChild(boxBtn,3);
        
        Sprite* equipNumSprite=Sprite::create(IMG_PUBLIC_LABEL_ALLEQUIP);
        equipNumSprite->setAnchorPoint(Point::ZERO);
        equipNumSprite->setPosition(520,(listBg2->getContentSize().height/sx-equipNumSprite->getContentSize().height)/2+5);
        listBg2->addChild(equipNumSprite);
        
        string numStr="0/0";
        equipNumLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
        equipNumLabel->setAnchorPoint(Point::ZERO);
        equipNumLabel->setPosition(equipNumSprite->getContentSize().width+equipNumSprite->getPositionX()+10,(listBg2->getContentSize().height/sx-equipNumLabel->getContentSize().height)/2+5);
        listBg2->addChild(equipNumLabel,1);
        
        //出售
        Button* sellBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsEquip_Layer::onSellBtnClick, this));
        sellBtn->setPosition(listBg2->getContentSize().width/sx-sellBtn->getContentSize().width/2 - 30 ,listBg2->getContentSize().height/sx/2+10);
        listBg2->addChild(sellBtn,1);
        
        Sprite* sellLabel=Sprite::create(IMG_PUBLIC_LABEL_SELL);
        sellBtn->addChild(sellLabel,2);
    }
}
void GeneralsEquip_Layer::updataCreate()
{
    string numStr=PublicShowUI::numberToString((int)EquipDataManager::getInstance()->getEquipDataList()->size())+"/"+PublicShowUI::numberToString(maxListSize);
    equipNumLabel->setString(numStr);
}

void GeneralsEquip_Layer::initTableView()
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
        _tableView->setPosition(listBg->getPositionX()+30*sx,listBg->getPositionY()+53*sx);
    }
    
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(6*sx,40*sx);
    this->addChild(shade,3);
}
void GeneralsEquip_Layer::onTopComboBoxClick(Ref* psender)
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
            tempStr="status";
            break;
        default:
            break;
    }
    this->sortList(tempStr);
}
void GeneralsEquip_Layer::onHeadClick(Ref* pSender)
{
    
    isTouchEquip=true;
    Sprite* node=(Sprite*)pSender;
    int tag=node->getTag();
    
    
        EquipDataManager::getInstance()->setPresentData(EquipDataManager::getInstance()->getEquipDataByIndex(tag));
   
   
}
void GeneralsEquip_Layer::onSellBtnClick(Ref* psender)
{
    Generals_Sell_Layer* layer=Generals_Sell_Layer::create(0);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
    Scene* scene=Director::getInstance()->getRunningScene();
    scene->addChild(layer);
}


//-------------------------------------------------TableView部分-------------------------------------------------//
//单个列表内容
Button* GeneralsEquip_Layer::singleList(ssize_t idx)
{
    BaseEquipData* data =EquipDataManager::getInstance()->getEquipDataList()->at(idx);
    
    Button*layerBg = Button::create(IMG_PUBLIC_LAYER_TWO_CELLBG,IMG_PUBLIC_LAYER_TWO_CELLBG,CC_CALLBACK_1(GeneralsEquip_Layer::onHeadClick, this));
    layerBg->setAnchorPoint(Point::ZERO);
    layerBg->getTouchListener()->setSwallowTouches(false);
    layerBg->setTag((int)idx);
    
    if(data->redCanHarden == 1)
    {
        PublicShowUI::setDot(layerBg, Point(10,10),false,DictFunctionEnumEquipHarden);
    }
    
    int m_quality = PublicShowUI::getItemColorIndexByQuality(data->equipDictId, data->quality);
    //装备
    UserEquipLayer* userEquip=UserEquipLayer::create(data->resource,m_quality,true,false);
    userEquip->setHeadInfo(data->equipLevel);
    userEquip->setAnchorPoint(Point::ZERO);
    userEquip->setPosition(22,24);
    layerBg->addChild(userEquip,2);
    if(idx == 0)
    {
         GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumBelongEquipButton, userEquip);
    }
   
    
    Sprite* nameBg=Sprite::create(IMG_PUBLIC_EQUIP_NAMEBG);
    nameBg->setAnchorPoint(Point::ZERO);
    nameBg->setPosition(152,110);
    layerBg->addChild(nameBg,2);
    
    string name= data->equipName;
    Label* nameLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(10,(nameBg->getContentSize().height-nameLabel->getContentSize().height)/2);
    nameBg->addChild(nameLabel);
    
    int size=(int)data->propertyList.size();
    for (int i=0; i<size; i++) {
        int num= data->propertyList.at(i).propertyType;
        string str=PublicShowUI::getEquipProerty(num);
        
        string proStr=PublicShowUI::numberToString(data->propertyList.at(i).propertyNum);
        Label* propertyLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
        propertyLabel->setAnchorPoint(Point::ZERO);
        propertyLabel->setPosition(160,78-i*31);
        layerBg->addChild(propertyLabel,2);
        
        Label* propertyLabel2 = PublicShowUI::getLabel(proStr.c_str(),PublicShowUI::getColor3b(COLOR_DARK_GREEN),20,false,false);
        propertyLabel2->setAnchorPoint(Point::ZERO);
        propertyLabel2->setPosition(propertyLabel->getPositionX() + propertyLabel->getContentSize().width+10,78-i*31);
        layerBg->addChild(propertyLabel2,2);
    }
    //穿戴武将名字
    string nameStr=data->heroName;
//    Color3B color = PublicShowUI::getNameColor(DictItemTypeEnumItem, data->quality);
    Label* equipName=PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),16,false,false);
    equipName->setAnchorPoint(Point::ZERO);
    equipName->setPosition(340,18);
    layerBg->addChild(equipName,3);
    if (nameStr!="") {
        Sprite* dress=Sprite::create(IMG_PUBLIC_LAYER_DRESS);
        dress->setScale(0.9);
        dress->setAnchorPoint(Point::ZERO);
        dress->setPosition(343,42);
        layerBg->addChild(dress,2);
    }
    return layerBg;
}
//--------------------------------列表部分-------------------------------------------------------//
TableViewCell* GeneralsEquip_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<2; i++) {
        if (idx*2+i<EquipDataManager::getInstance()->getEquipDataList()->size()) {
            Button* list=singleList(idx*2+i);
            list->setPosition(i*(list->getContentSize().width+8),0);
            cell->addChild(list,1);
        }
    }
    return cell;
}

//列表大小
Size GeneralsEquip_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+8;
    cellSize.width = temp->getContentSize().width *2+10;
    return cellSize;
}
//获取view的长度
ssize_t GeneralsEquip_Layer::numberOfCellsInTableView(TableView *table)
{
    titleCount=ceil((float)EquipDataManager::getInstance()->getEquipDataList()->size()/2);
    return titleCount;
}
//点击cell事件
void GeneralsEquip_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    this->isMoveing=false;
    if (this->isTouchEquip) {
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumBelongEquipButton);
        GeneralsEquip_Scene::show(SCENE_TAG_GENERALS_EQUIP, LAYER_EQUIP_STRONG);
    }
    this->isTouchEquip=false;
}
void GeneralsEquip_Layer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
//-------------------------------------------------服务器部分----------------------------------------------------//
void GeneralsEquip_Layer::requestListMsg(EventCustom* evt)
{
    
    EquipListMsg* msg = new EquipListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsEquip_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_EQUIP_EquipListPageResp)
    {
        if (message->state==false) {
            return;
        }
        EquipDataManager::getInstance()->clearEquipList();
        maxListSize=message->byteStream->getShort();
        int _size=message->byteStream->getShort();
        for (int i=0; i<_size; i++) {
            BaseEquipData* data=new BaseEquipData();
            data->autorelease();
            data->equipId=message->byteStream->getInt();
            data->equipDictId=message->byteStream->getInt();
            data->quality=message->byteStream->getByte();
            data->equipLevel=message->byteStream->getInt();
            data->equipMaxLevel=message->byteStream->getInt();
            data->equipName=message->byteStream->getUTF8();
            data->equipParts=message->byteStream->getByte();
            data->heroName=message->byteStream->getUTF8();
            data->equipStatus=message->byteStream->getByte();
//            data->exp=message->byteStream->getInt();
//            data->maxExp=message->byteStream->getInt();
            data->resource=message->byteStream->getUTF8();
            data->redCanHarden=message->byteStream->getByte();
            int propertySize=message->byteStream->getByte();
//            backPackOrder
            DictItemEquip* itemEquip= DictItemEquipManager::getInstance()->getData(data->equipDictId);
            if (itemEquip) {
                data->backPackOrder=itemEquip->backPackOrder;
            }
            for (int i=0; i<propertySize; i++) {
                struct BaseEquipProperty propertyData = {0,0};
                propertyData.propertyType=message->byteStream->getByte();
                propertyData.propertyNum=message->byteStream->getInt();
                data->propertyList.push_back(propertyData);
            }
            EquipDataManager::getInstance()->addEquipData(data);
        }
        this->sortList("level");
        NewPlayerGuild::getInstance()->showNowGuide();
        this->updataCreate();
    }
}
void GeneralsEquip_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_EQUIP_EquipListPageResp).c_str(), CC_CALLBACK_1(GeneralsEquip_Layer::onMsgProcess, this));
    addUserMsg(CUSTOM_SELL_EQUIP,CC_CALLBACK_1(GeneralsEquip_Layer::requestListMsg, this));
}
void GeneralsEquip_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
//状态排序
bool sortOnGeneralsEquipStatus(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->heroName !="" ;
}
bool sortOnGeneralsEquipQualityAscend(BaseEquipData* n1, BaseEquipData* n2)//倒序(从大到小)
{
    return n1->quality > n2->quality;
}
bool sortOnGeneralsEquipQualityDescend(BaseEquipData* n1, BaseEquipData* n2)//倒序(从小到大)
{
    return n1->quality < n2->quality;
}
bool sortOnGeneralsEquipLevel(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->equipLevel > n2->equipLevel;
}
bool sortOnGeneralsEquipPackOrder(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->backPackOrder < n2->backPackOrder;
}
//排序
void GeneralsEquip_Layer::sortList(string name)
{
    if (name=="0") {
        return;
    }
    Vector<BaseEquipData*>* equipList=EquipDataManager::getInstance()->getEquipDataList();
    if(name == "status" )
    {
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipPackOrder);
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipQualityDescend);
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipStatus);
    }
    else if(name == "quality")
    {
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipPackOrder);
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipLevel);
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipQualityAscend);
    }
    else if(name == "level" )
    {
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipPackOrder);
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipQualityDescend);
        stable_sort(equipList->begin(), equipList->end(),sortOnGeneralsEquipLevel);
    }
    this->initTableView();
    
}
bool GeneralsEquip_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{
    isDownPoint=touch->getLocation();
//    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void GeneralsEquip_Layer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
}
void GeneralsEquip_Layer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
}