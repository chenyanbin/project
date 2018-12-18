//
//  ChooseEquip_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/7.
//
//
#include "ChooseEquip_Layer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../generalsCard/GeneralsCard_Layer.h"
#include "../generalsBase/GeneralsBase_Layer.h"
#include "../../userWealth/UserWealthLayer.h"
#include "../../../message/Decoding/generals/base/ChooseEquipMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../commonData/enum/DictEquipPartsEnum.h"
#include "../../../message/Decoding/generals/base/HeroPutOnMsg.h"
#include "../../../message/Decoding/generals/base/HeroTaskOffMsg.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../data/CardDataManager.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/dictData/DictItem/DictItemManager.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../HeroListBar_Layer.h"
ChooseEquip_Layer::ChooseEquip_Layer()
:sx(1)
,sy(1)
,titleCount(0)
,TAG_LISTBG(1)
,TAG_TABLEVIEW(2)
,TAG_BOTTOMBG(3)
,TAG_BTN(5)
,TAG_EQUIPS(10)
,clickIdx(-1)
,maxHero(0)
,_heroId(1)
,_slot(1)
{
    equipList=new vector<BaseEquipData*>() ;
}
ChooseEquip_Layer::~ChooseEquip_Layer()
{
    equipList->clear();
    CC_SAFE_DELETE(equipList);
    
}
bool ChooseEquip_Layer::init(int heroId ,int slot)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx= GlobalInfo::getInstance()->screenScaleX;
        sy= GlobalInfo::getInstance()->screenScaleY;
        _slot=slot;
        _heroId=heroId;
        this->isShowGrayBg=true;
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG);
        this->createLayer();
        this->isClickClose=true;
        this->setClickEnabled(true);
        bref = true;
    } while (false);
    return bref;
}
void ChooseEquip_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void ChooseEquip_Layer::onExit()
{
    BaseLayer::onExit();
}
void ChooseEquip_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
//    CardPropertyData* data=new CardPropertyData();
//    data->heroId=_heroId;
//    CardDataManager::getInstance()->setPresentData(data);
    
    this->requestListMsg();
}
void ChooseEquip_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
ChooseEquip_Layer* ChooseEquip_Layer::create(int heroId ,int slot)
{
    ChooseEquip_Layer* layer = new ChooseEquip_Layer();
    if(layer && layer->init(heroId,slot))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}

void ChooseEquip_Layer::show(int fromeScene,int heroId ,int slot)
{
    Director::getInstance()->purgeCachedData();
    ChooseEquip_Layer* layer = ChooseEquip_Layer::create(heroId ,slot);
    layer->setFromScene(fromeScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_GENERALS);
    Director::getInstance()->replaceScene(scene);
}
//--------------------------------主界面----------------------------------------------------
void ChooseEquip_Layer::createLayer()
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
        ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(ChooseEquip_Layer::onTopComboBoxClick, this));
        for (int i = 0; i<3; i++) {
            //        boxBtn->addBtn(pathList[i], pathList2[i], "");
            boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathList[i], pathList2[i]);
        }
        boxBtn->setAnchorPoint(Point::ZERO);
        boxBtn->setPosition(10*sx,(listBg2->getContentSize().height/sx-boxBtn->getContentSize().height)/2+5*sx);
        boxBtn->getButtonAt(0)->selected();
        listBg2->addChild(boxBtn,3);
        
    }
    
}
void ChooseEquip_Layer::onTopComboBoxClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    string tempStr="0";
    switch (tag) {
        case 0:
            tempStr="quality";
            break;
        case 1:
            tempStr="level";
            break;
        case 2:
            tempStr="status";
            break;
        default:
            break;
    }
    this->sortList(tempStr);
}


string ChooseEquip_Layer::equipParts(int num)
{
    string name;
    switch (num) {
        case DictEquipPartsEnumEquipSlot1EquipID:
            name="武器";
            break;
        case DictEquipPartsEnumEquipSlot2EquipID:
            name="头盔";
            break;
        case DictEquipPartsEnumEquipSlot3EquipID:
            name="腰带";
            break;
        case DictEquipPartsEnumEquipSlot4EquipID:
            name="铠甲";
            break;
        case DictEquipPartsEnumEquipSlot5EquipID:
            name="项链";
            break;
        case DictEquipPartsEnumEquipSlot6EquipID:
            name="锦囊";
            break;
        default:
            break;
    }
    return name;
}
//--------------------------------列表部分-------------------------------------------------------//
void ChooseEquip_Layer::initTableView()
{
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    //
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+_size.height/2-20;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(listBg->getPositionX()+ 30*sx,listBg->getPositionY()+50*sx);
    this->addChild(_tableView,1,TAG_TABLEVIEW);
}
TableViewCell* ChooseEquip_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<2; i++) {
        if (idx*2+i<equipList->size()) {
            Sprite* list=singleList(idx*2+i);
            list->setPosition(i*(list->getContentSize().width+8),0);
            cell->addChild(list,1);
        }
    }

    Sprite* list=singleList(idx);
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    return cell;
}

//列表大小
Size ChooseEquip_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height;
    cellSize.width = temp->getContentSize().width*2+10;
    cellSize.height+=4;
    return cellSize;
}
//获取view的长度
ssize_t ChooseEquip_Layer::numberOfCellsInTableView(TableView *table)
{
    titleCount=ceil((float)equipList->size()/2);
    return titleCount;
}
//点击cell事件
void ChooseEquip_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}

//单个列表内容
Sprite* ChooseEquip_Layer::singleList(ssize_t idx)
{
    
    BaseEquipData* data =equipList->at(idx);
    
    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    layerBg->setTag((int)idx);
    //装备
    const char* path =PublicShowUI::getGoods(data->typeId, data->equipDictId);
    UserEquipLayer* userEquip=UserEquipLayer::create(path,data->quality,false);
    userEquip->setAnchorPoint(Point::ZERO);
    
    userEquip->setPosition(23,24);
    layerBg->addChild(userEquip,2);
    
    userEquip->setHeadInfo(data->equipLevel);
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
        Label* propertyLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
        propertyLabel->setAnchorPoint(Point::ZERO);
        propertyLabel->setPosition(160,78-i*31);
        layerBg->addChild(propertyLabel,2);
        
        Label* propertyLabel2 = PublicShowUI::getLabel(proStr.c_str(),PublicShowUI::getColor3b(COLOR_DARK_GREEN),18,false,false);
        propertyLabel2->setAnchorPoint(Point::ZERO);
        propertyLabel2->setPosition(240,78-i*31);
        layerBg->addChild(propertyLabel2,2);
    }
    //装备名字
    string nameStr=data->heroName;
    Label* equipName=PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),16,false,false);
    equipName->setAnchorPoint(Point::ZERO);
    equipName->setPosition(340,20);
    layerBg->addChild(equipName,3);
    
    const char* btnPath=NULL;
    const char* labelPath=NULL;
    float btnX;
    if (data->equipStatus==1 or data->equipStatus==2) {
        btnX=300;
        btnPath=IMG_PUBLIC_BUTTON_TWO_ORANGE;
        labelPath=IMG_PUBLIC_LABEL_CROSS;
        
    }else if (data->equipStatus==3)
    {
        btnX=300;
        btnPath=IMG_PUBLIC_BUTTON_TWO_ORANGE;
        labelPath=IMG_PUBLIC_LABEL_DOWN;
        
    }
    if (btnPath) {
        Button* btn=Button::create(btnPath, btnPath, CC_CALLBACK_1(ChooseEquip_Layer::onBtnClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(btnX,50);
        btn->setTag((int)idx);
        layerBg->addChild(btn,3);
        if(idx == 0)
        {
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumWearEquipment, btn);
        }
        Sprite* btnLabel=Sprite::create(labelPath);
        btnLabel->setAnchorPoint(Point::ZERO);
        btnLabel->setPosition((btn->getContentSize().width-btnLabel->getContentSize().width)/2,(btn->getContentSize().height-btnLabel->getContentSize().height)/2);
        btn->addChild(btnLabel,2);
    }else{
        Sprite* btnLabel=Sprite::create(labelPath);
        btnLabel->setAnchorPoint(Point::ZERO);
        btnLabel->setPosition(btnX,50);
        layerBg->addChild(btnLabel,2);
    }
    return layerBg;
}

//-------------------------------view结束。点击事件部分-------------------------------------------------------//
void ChooseEquip_Layer::onBtnClick(Ref* psender)
{
    Node* cardNode=(Node*)psender;
    BaseEquipData* equipData=equipList->at(cardNode->getTag());
    //1 可装备：符合装备条件，并且没有在任何武将身上.
    //2 可卸下：已经在某个武将身上，包括其他武将.
    //3 不可装备：不符合dict定义.
    if (equipData->equipStatus==1 or equipData->equipStatus==2) {
        equipPutOnMsg(equipData->equipId);
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumWearEquipment);
    }else if (equipData->equipStatus==3)
    {
        equipTakeOffMsg();
        
    }
    HeroListBar_Layer* listhead = HeroListBar_Layer::create();
    listhead->setUpdata();
}
void ChooseEquip_Layer::onBtnListClick(Ref* psender)
{
    
}
void ChooseEquip_Layer::onRightBtnClick(Ref* psender)
{
    
}

//-----------------------------------------------访问服务器-------------------------------------------------------//
void ChooseEquip_Layer::requestListMsg()
{
    ChooseEquipMsg* msg = new ChooseEquipMsg(_heroId,_slot);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ChooseEquip_Layer::equipPutOnMsg(int equitId)
{
    HeroPutOnMsg* msg = new HeroPutOnMsg(_heroId,_slot,equitId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ChooseEquip_Layer::equipTakeOffMsg()
{
    HeroTaskOffMsg* msg = new HeroTaskOffMsg(_heroId,_slot);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ChooseEquip_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_HERO_HeroEquipSelPageResp)
    {
        if (message->state==false) {
            return;
        }
        short size=message->byteStream->getShort();
        for (int i =0; i<size; i++) {
            BaseEquipData* data=new BaseEquipData();
            data->equipId=message->byteStream->getInt();
            data->equipName=message->byteStream->getUTF8();
            data->equipDictId=message->byteStream->getInt();
            data->equipParts=message->byteStream->getByte();
            data->quality=message->byteStream->getByte();
            data->equipLevel=message->byteStream->getInt();
            data->heroName=message->byteStream->getUTF8();
            data->equipStatus=message->byteStream->getUByte();
            int properSize=message->byteStream->getByte();
            for (int j=0; j<properSize; j++) {
                struct BaseEquipProperty propertyData = {0,0};
                propertyData.propertyType=message->byteStream->getByte();
                propertyData.propertyNum=message->byteStream->getInt();
                data->propertyList.push_back(propertyData);
            }
            DictItem* itemData=DictItemManager::getInstance()->getData(data->equipDictId);
            if (itemData) {
                data->backPackOrder=itemData->seq;
            }
            equipList->push_back(data);
        }
        this->sortList("quality");
        NewPlayerGuild::getInstance()->showNowGuide();
    }
    else if (message->messageID == SCENSE_CLIENT_HERO_HeroTakeOffResp)
    {
        this->removeFromParent();
        this->broadMsg(CUSTOM_UPDATE_EQUIP);
        
    }
    else if (message->messageID == SCENSE_CLIENT_HERO_HeroPutOnResp)
    {
          this->removeFromParent();
        this->broadMsg(CUSTOM_UPDATE_EQUIP);
    }
}
void ChooseEquip_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroEquipSelPageResp).c_str(), CC_CALLBACK_1(ChooseEquip_Layer::onMsgProcess, this));
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroTakeOffResp).c_str(), CC_CALLBACK_1(ChooseEquip_Layer::onMsgProcess, this));
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroPutOnResp).c_str(), CC_CALLBACK_1(ChooseEquip_Layer::onMsgProcess, this));
}
void ChooseEquip_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
//状态排序
bool sortOnChooseEquipStatus(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->equipStatus > n2->equipStatus;
}
bool sortOnChooseEquipStatusSelf(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->equipStatus == 3;
}

bool sortOnChooseEquipQualityAscend(BaseEquipData* n1, BaseEquipData* n2)//倒序(从大到小)
{
    return n1->quality > n2->quality;
}
bool sortOnChooseEquipQualityDescend(BaseEquipData* n1, BaseEquipData* n2)//倒序(从小到大)
{
    return n1->quality < n2->quality;
}
bool sortOnChooseEquipLevel(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->equipLevel > n2->equipLevel;
}
bool sortOnChooseEquipPackOrder(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->backPackOrder < n2->backPackOrder;
}
//排序
void ChooseEquip_Layer::sortList(string name)
{
    if (name=="quality") {
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipPackOrder);
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipQualityAscend);
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipStatusSelf);
    }else if (name=="level")
    {
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipPackOrder);
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipQualityDescend);
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipLevel);
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipStatusSelf);
    }else if (name=="status")
    {
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipPackOrder);
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipQualityDescend);
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipStatus);
        stable_sort(equipList->begin(), equipList->end(),sortOnChooseEquipStatusSelf);
    }else if (name=="0")
    {
        return;
    }
    
    this->initTableView();
}