               //
//  GeneralsMaterial_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/20.
//
//

#include "GeneralsMaterial_Layer.h"
#include "../data/LetterDataManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../publicLayer/Getpath_Layer.h"
#include "../../../message/Decoding/generals/material/MaterPageMsg.h"
#include "../../../message/Decoding/generals/material/MaterComposeMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../commonData/dictData/DictItemMater/DictItemMaterManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../userWealth/UserBigEquipLayer.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
GeneralsMaterial_Layer::GeneralsMaterial_Layer()
:TAG_TABLEVIEW(1)
,TAG_COMPOUND(2)
,TAG_GOTOGAIN(3)
,TAG_ALLMATERIAL(4)
,materialNumberLabel(NULL)
,onSortStr("number")
,sx(1)
{
    materList=new vector<MaterData*>();
    selectData=new MaterData();
}
GeneralsMaterial_Layer::~GeneralsMaterial_Layer()
{
    materList->clear();
    CC_SAFE_DELETE(materList);
    selectData=NULL;
}
GeneralsMaterial_Layer* GeneralsMaterial_Layer::create()
{
    GeneralsMaterial_Layer* layer = new GeneralsMaterial_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
bool GeneralsMaterial_Layer::init()
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
void GeneralsMaterial_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsMaterial_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsMaterial_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
    
}
void GeneralsMaterial_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumCompositeButton);
}

void GeneralsMaterial_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3-60;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    if (listBg) {
        _tableView->setPosition(listBg->getPositionX()+30*sx,listBg->getPositionY()+53*sx);
    }
    
    this->addChild(_tableView,3,TAG_TABLEVIEW);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(6*sx,40*sx);
    this->addChild(shade,3);
    
    if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumCompositeButton)
    {
        NewPlayerGuild::getInstance()->showNowGuide();
    }
}
void GeneralsMaterial_Layer::createLayer()
{
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    if (listBg) {
        string numStr="今日送礼次数:";
        Label* equipNumSprite=PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
        equipNumSprite->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(equipNumSprite);
        equipNumSprite->setPosition(listBg->getPositionX()+45*sx,listBg->getPositionY()+18*sx);
        this->addChild(equipNumSprite);
        
        numStr="0";
        materialNumberLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_DARK_GREEN),18,false,false);
        materialNumberLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(materialNumberLabel);
        materialNumberLabel->setPosition(equipNumSprite->getContentSize().width+equipNumSprite->getPositionX()+10,equipNumSprite->getPositionY());
        this->addChild(materialNumberLabel,1);
        
//        Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_LISTBG2);
//        listBg2->setAnchorPoint(Point::ZERO);
//        PublicShowUI::setTargetScale(listBg2);
//        listBg2->setPosition(listBg->getPositionX()+ 34*sx,listBg->getPositionY()+465*sx);
//        this->addChild(listBg2);
//        
//        
//        Sprite* equipNumSprite=Sprite::create(IMG_PUBLIC_LABEL_ALLMATERIAL);
//        equipNumSprite->setAnchorPoint(Point::ZERO);
//        equipNumSprite->setPosition(650,(listBg2->getContentSize().height/sx-equipNumSprite->getContentSize().height)/2);
//        listBg2->addChild(equipNumSprite);
//        
//        string numStr="0";
//        materialNumberLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
//        materialNumberLabel->setAnchorPoint(Point::ZERO);
//        materialNumberLabel->setPosition(equipNumSprite->getContentSize().width+equipNumSprite->getPositionX()+10,(listBg2->getContentSize().height/sx-materialNumberLabel->getContentSize().height)/2);
//        listBg2->addChild(materialNumberLabel,1);
        
    }

//    const char* pathList[3] = {IMG_PUBLIC_LABEL_MASS2_FIRST,IMG_PUBLIC_LABEL_NUMBER_FIRST};
//    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 16, CC_CALLBACK_1(GeneralsMaterial_Layer::onTopComboBoxClick, this));
//    for (int i = 0; i<2; i++) {
//        boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_FRIST1, IMG_PUBLIC_COMBOBOX_FRIST2, pathList[i]);
//    }
//    boxBtn->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(boxBtn);
//    boxBtn->setPosition(6,listBg->getContentSize().height);
//    boxBtn->getButtonAt(1)->selected();
//    this->addChild(boxBtn,2);
//    
//    Sprite* numBg=Sprite::create(IMG_PUBLIC_LAYER_ALLNUM_BG);
//    numBg->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(numBg);
//    numBg->setPosition((boxBtn->getContentSize().width+boxBtn->getPositionX()+20*sx),boxBtn->getPositionY());
//    this->addChild(numBg);
//    
//    Sprite* equipNumSprite=Sprite::create(IMG_PUBLIC_LABEL_ALLMATERIAL);
//    equipNumSprite->setAnchorPoint(Point::ZERO);
//    equipNumSprite->setPosition(20,(numBg->getContentSize().height/sx-equipNumSprite->getContentSize().height)/2);
//    numBg->addChild(equipNumSprite);
//    
//    string numStr=" ";
//    Label* latterNumLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
//    latterNumLabel->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(latterNumLabel);
//    latterNumLabel->setPosition(numBg->getPositionX()+120*sx,numBg->getPositionY()+(numBg->getContentSize().height-latterNumLabel->getContentSize().height)/2);
//    this->addChild(latterNumLabel,2,TAG_ALLMATERIAL);
}

//-------------------------------------------------TableView部分-------------------------------------------------//
TableViewCell* GeneralsMaterial_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    
    for (int i=0; i<2; i++) {
        if (idx*2+i<materList->size()) {
            Sprite* list=singleList(idx*2+i);
            list->setPosition(i*(list->getContentSize().width+8),5);
            cell->addChild(list,1);
        }
    }
    
    return cell;
}
//单个列表内容
Sprite* GeneralsMaterial_Layer::singleList(ssize_t idx)
{
    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    layerBg->setTag((int)idx);
    //头像
    MaterData* data=materList->at(idx);
    
    string resource = DictItemMaterManager::getInstance()->getData(data->materId)->resource;
    UserEquipLayer* head=UserEquipLayer::create(resource,data->materQuality);
    head->setAnchorPoint(Point::ZERO);
    head->setFragment();
    head->setPosition(22,26);
    layerBg->addChild(head);
    //名字背景
    Sprite* nameBg=Sprite::create(IMG_PUBLIC_EQUIP_NAMEBG);
    nameBg->setAnchorPoint(Point::ZERO);
    nameBg->setPosition(152,110);
    layerBg->addChild(nameBg,2);
    
    string name= data->materName;
    Label* nameLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(10,(nameBg->getContentSize().height-nameLabel->getContentSize().height)/2);
    nameBg->addChild(nameLabel);
    
    //材料数量
    Sprite* materialNumSprite=Sprite::create(IMG_GENERALS_MATERIAL_NUMBER);
    materialNumSprite->setAnchorPoint(Point::ZERO);
    materialNumSprite->setPosition(154,68);
    layerBg->addChild(materialNumSprite);
    //进度条
    Sprite* progressBg=Sprite::create(IMG_GENERALS_MATERIAL_PROGRESSBG);
    progressBg->setAnchorPoint(Point::ZERO);
    progressBg->setPosition(255,70);
    layerBg->addChild(progressBg);
    
    float totalExperence = data->materNeedCount;
    float percent =  data->materNumber / totalExperence;
    ProgressTimer* expProgress = ProgressTimer::create(Sprite::create(IMG_GENERALS_MATERIAL_PROGRESS));
    expProgress->setType(ProgressTimer::Type::BAR);
    expProgress->setMidpoint(Point(0,1));
    expProgress->setBarChangeRate(Point(1,0));
    expProgress->setAnchorPoint(Point(0 ,0));
    expProgress->setPosition(255,70);
    layerBg->addChild(expProgress);
    expProgress->setPercentage(percent * 100);
    
    
    string numStr=PublicShowUI::numberToString(data->materNumber)+"/"+PublicShowUI::numberToString(data->materNeedCount);
    Label* numLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),16,false,false);
    numLabel->setAnchorPoint(Point::ZERO);
    numLabel->setPosition(300,progressBg->getPositionY()+(progressBg->getContentSize().height-numLabel->getContentSize().height)/2+1);
    layerBg->addChild(numLabel);
    
    //按钮
    Button* btn=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsMaterial_Layer::onBtnListClick, this));
    btn->setPosition(287+btn->getContentSize().width/2,15+btn->getContentSize().height/2);
    layerBg->addChild(btn);
    
    Sprite* btnLabel=NULL;
    if (data->materNumber>=data->materNeedCount) {
        btnLabel=Sprite::create(IMG_PUBLIC_LABEL_COMPOUND);
        PublicShowUI::setDot(btn, Point(50,20), false,DictFunctionEnumMater);
        btn->setTag(TAG_COMPOUND);
    }else
    {
        btnLabel=Sprite::create(IMG_PUBLIC_LABEL_GAIN);
        btn->setTag(TAG_GOTOGAIN);
    }
    if(idx == 0)
    {
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumCompositeButton, btn);
       
    }
    btn->addChild(btnLabel,2);
    return layerBg;
}
//列表大小
Size GeneralsMaterial_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+8;
    cellSize.width = temp->getContentSize().width *2+10;
    return cellSize;
}
//获取view的长度
ssize_t GeneralsMaterial_Layer::numberOfCellsInTableView(TableView *table)
{
    int titleCount=ceil((float)materList->size()/2);
    return titleCount;
}
//点击cell事件
void GeneralsMaterial_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}

void GeneralsMaterial_Layer::onBtnListClick(Ref* psender)
{
    NewPlayerGuild::getInstance()->next();
    Node* node=(Node*)psender;
    int tag=node->getTag();
    int parent=node->getParent()->getTag();
    selectData=materList->at(parent);
    int materId=selectData->materId;
    if (tag==TAG_COMPOUND) {
        this->requestComposeMsg(materId);
    }else if (tag==TAG_GOTOGAIN)
    {
//        Getpath_Layer::show(SCENE_TAG_GENERALS_MATERIAL,DictItemTypeEnumItemMater, materList->at(parent)->materId,materList->at(parent)->materQuality);
        
        Scene* scene = Director::getInstance()->getRunningScene();
        if(scene->getChildByTag(SCENE_TAG_GETPATH))
        {
            return;
        }
        Getpath_Layer* layer = Getpath_Layer::create(DictItemTypeEnumItemMater,materList->at(parent)->materId,materList->at(parent)->materQuality,SCENE_TAG_GENERALS_MATERIAL);
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
        layer->setAnchorPoint(Point(0.5,0.5));
        scene->addChild(layer,SCENE_TWOLAYER_ZORDER,SCENE_TAG_GETPATH);
    }
    
}
//-------------------------------------------------服务器部分----------------------------------------------------//
void GeneralsMaterial_Layer::requestListMsg()
{
    MaterPageMsg* msg = new MaterPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsMaterial_Layer::requestComposeMsg(int _materId)
{
    
    MaterComposeMsg* msg = new MaterComposeMsg(_materId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsMaterial_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_MATER_MaterPageResp)
    {
        if (message->state==false) {
            return;
        }
        materList->clear();
        int itemCount=message->byteStream->getShort();
        for (int i=0; i<itemCount; i++) {
            MaterData* data  = new MaterData();
            data->materId=message->byteStream->getInt();
            data->materName=message->byteStream->getUTF8();
            data->materQuality=message->byteStream->getByte();
            data->materNumber=message->byteStream->getInt();
            data->materNeedCount=message->byteStream->getInt();
            materList->push_back(data);
        }
        this->sortList(onSortStr);
        

        if (materialNumberLabel) {
            materialNumberLabel->setString(PublicShowUI::numberToString((int)materList->size()));
        }
        

    }else if (message->messageID==SCENSE_CLIENT_MATER_MaterComposeResp)
    {
        if (message->state==false) {
            return;
        }
        
        UserBigEquipLayer* layer=UserBigEquipLayer::create(selectData);
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
        Scene* scene = Director::getInstance()->getRunningScene();
        scene->addChild(layer,SCENE_TWOLAYER_ZORDER);
        this->requestListMsg();
        
        broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumMater));
    }
}
void GeneralsMaterial_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MATER_MaterPageResp).c_str(), CC_CALLBACK_1(GeneralsMaterial_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MATER_MaterComposeResp).c_str(), CC_CALLBACK_1(GeneralsMaterial_Layer::onMsgProcess, this));
}
void GeneralsMaterial_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
//排序

//状态排序
bool sortOnMaterialQualityAscend(MaterData* n1, MaterData* n2)
{
    return n1->materQuality > n2->materQuality;
}

bool sortOnMaterialId(MaterData* n1, MaterData* n2)
{
    return n1->materId > n2->materId;
}
//排序
void GeneralsMaterial_Layer::sortList(string name)
{
    stable_sort(materList->begin(), materList->end(),sortOnMaterialQualityAscend);
    stable_sort(materList->begin(), materList->end(),sortOnMaterialId);
    
    this->initTableView();
}