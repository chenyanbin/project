//
//  GeneralsProps_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/20.
//
//

#include "GeneralsProps_Layer.h"
#include "../data/LetterDataManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../commonData/enum/DictItemUseTypeEnum.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../message/Decoding/generals/props/PropsItemPage.h"
#include "../../../message/Decoding/generals/props/PropsItemUseMsg.h"
#include "../../market/marketData/MarketFindResultDataManager.h"
#include "../../market/marketJuxian/MarketGoodsLayer.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/enum/DictItemUseTypeEnum.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../commonData/dictData/DictItem/DictItemManager.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../commonData/dictData/DictItemBook/DictItemBookManager.h"
//DictItemUseTypeEnum
GeneralsProps_Layer::GeneralsProps_Layer()
:TAG_TABLEVIEW(1)
,TAG_ALLPROPS(2)
,propsNumberLabel(NULL)
,sx(1)
,thisSort("")
,isClick(false)
{
    propsList=new Vector<PropsData*>();
}
GeneralsProps_Layer::~GeneralsProps_Layer()
{
    propsList->clear();
    CC_SAFE_DELETE(propsList);
    
}
GeneralsProps_Layer* GeneralsProps_Layer::create()
{
    GeneralsProps_Layer* layer = new GeneralsProps_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
bool GeneralsProps_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx= GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG);
        thisSort="drug";
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
void GeneralsProps_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsProps_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsProps_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
//    this->initTableView();
}
void GeneralsProps_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

void GeneralsProps_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        this->removeChildByTag(TAG_TABLEVIEW);
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
    this->addChild(_tableView,3,TAG_TABLEVIEW);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(6*sx,40*sx);
    this->addChild(shade,3);
}
void GeneralsProps_Layer::createLayer()
{
    
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    if (listBg) {
        Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
        listBg2->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(listBg2);
        listBg2->setPosition(listBg->getPositionX()+15*sx,listBg->getPositionY()+450*sx);
        this->addChild(listBg2,3);
        
        const char* pathList[3] = {IMG_PUBLIC_LABEL_DRUG,IMG_PUBLIC_LABEL_BOX};
        const char* pathList2[3] = {IMG_PUBLIC_LABEL_DRUG1,IMG_PUBLIC_LABEL_BOX1};
        ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(GeneralsProps_Layer::onTopComboBoxClick, this));
        for (int i = 0; i<2; i++) {
            //        boxBtn->addBtn(pathList[i], pathList2[i], "");
            boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathList[i], pathList2[i]);
        }
        boxBtn->setAnchorPoint(Point::ZERO);
        boxBtn->setPosition(10*sx,(listBg2->getContentSize().height/sx-boxBtn->getContentSize().height)/2+5*sx);
        boxBtn->getButtonAt(0)->selected();
        listBg2->addChild(boxBtn,3);
        
        Sprite* equipNumSprite=Sprite::create(IMG_PUBLIC_LABEL_ALLPROPS);
        equipNumSprite->setAnchorPoint(Point::ZERO);
        equipNumSprite->setPosition(650,(listBg2->getContentSize().height/sx-equipNumSprite->getContentSize().height)/2);
        listBg2->addChild(equipNumSprite);
        
        string numStr="0";
        propsNumberLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
        propsNumberLabel->setAnchorPoint(Point::ZERO);
        propsNumberLabel->setPosition(equipNumSprite->getContentSize().width+equipNumSprite->getPositionX()+10,(listBg2->getContentSize().height/sx-propsNumberLabel->getContentSize().height)/2);
        listBg2->addChild(propsNumberLabel,1);
        
    }
    
//    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
//    
//    
//    const char* pathList[3] = {IMG_PUBLIC_LABEL_DRUG_FIRST,IMG_PUBLIC_LABEL_ITEMBOX_FIRST};
//    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 16, CC_CALLBACK_1(GeneralsProps_Layer::onTopComboBoxClick, this));
//    for (int i = 0; i<2; i++) {
//        boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_FRIST1, IMG_PUBLIC_COMBOBOX_FRIST2, pathList[i]);
//    }
//    boxBtn->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(boxBtn);
//    boxBtn->setPosition(6,listBg->getContentSize().height);
//    boxBtn->getButtonAt(0)->selected();
//    this->addChild(boxBtn,2);
//    
//    Sprite* numBg=Sprite::create(IMG_PUBLIC_LAYER_ALLNUM_BG);
//    numBg->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(numBg);
//    numBg->setPosition((boxBtn->getContentSize().width+boxBtn->getPositionX()+20*sx),boxBtn->getPositionY());
//    this->addChild(numBg);
//    
//    Sprite* equipNumSprite=Sprite::create(IMG_PUBLIC_LABEL_ALLPROPS);
//    equipNumSprite->setAnchorPoint(Point::ZERO);
//    equipNumSprite->setPosition(20,(numBg->getContentSize().height/sx-equipNumSprite->getContentSize().height)/2);
//    numBg->addChild(equipNumSprite);
//    
//    string numStr=" ";
//    Label* latterNumLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
//    latterNumLabel->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(latterNumLabel);
//    latterNumLabel->setPosition(numBg->getPositionX()+120*sx,numBg->getPositionY()+(numBg->getContentSize().height-latterNumLabel->getContentSize().height)/2);
//    this->addChild(latterNumLabel,2,TAG_ALLPROPS);
}

void GeneralsProps_Layer::onTopComboBoxClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    string tempStr="0";
    switch (tag) {
        case 0:
            tempStr="drug";
            break;
        case 1:
            tempStr="box";
            break;
        default:
            break;
    }
    this->sortList(tempStr);
}


//-------------------------------------------------TableView部分-------------------------------------------------//
TableViewCell* GeneralsProps_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<2; i++) {
        if (idx*2+i<propsList->size()) {
            Sprite* list=singleList(idx*2+i);
            list->setPosition(i*(list->getContentSize().width+8),0);
            cell->addChild(list,1);
        }
    }
    return cell;
}
//单个列表内容
Sprite* GeneralsProps_Layer::singleList(ssize_t idx)
{
    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    layerBg->setTag((int)idx);
    //头像
    PropsData* data=propsList->at(idx);
    
    const char* path=PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM, data->propResource.c_str());
    UserEquipLayer* head=UserEquipLayer::create(path,data->propsQuality,false);
    if (head) {
        head->setAnchorPoint(Point::ZERO);
        head->setPosition(22,24);
        layerBg->addChild(head);
    }
    //名字背景
    Sprite* nameBg=Sprite::create(IMG_PUBLIC_EQUIP_NAMEBG);
    nameBg->setAnchorPoint(Point::ZERO);
    nameBg->setPosition(152,110);
    layerBg->addChild(nameBg,2);
    
    string name= data->propsName;
    Label* nameLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(10,(nameBg->getContentSize().height-nameLabel->getContentSize().height)/2);
    nameBg->addChild(nameLabel);
    //描述
    Sprite* descBg=Sprite::create(IMG_GENERALS_PROPS_DESC_BG);
    descBg->setAnchorPoint(Point::ZERO);
    descBg->setPosition(154,53);
    layerBg->addChild(descBg,2);
    
    name= data->propsDesc;
    Label* descLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(0x8beed3),16,false,false);
    descLabel->setAnchorPoint(Point(0,1));
    descLabel->setPosition(2,(descBg->getContentSize().height-3));
    descLabel->setMaxLineWidth(descBg->getContentSize().width);
    descBg->addChild(descLabel);
    //剩余数量
    Sprite* surplus=Sprite::create(IMG_PUBLIC_LABEL_SURPLUS);
    surplus->setAnchorPoint(Point::ZERO);
    surplus->setPosition(148,21);
    layerBg->addChild(surplus,2);
    
    name= PublicShowUI::numberToString(data->propsNumber);
    Label* surplusLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),16,false,false);
    surplusLabel->setAnchorPoint(Point::ZERO);
    surplusLabel->setPosition(surplus->getPositionX()+surplus->getContentSize().width+3,surplus->getPositionY()+(surplus->getContentSize().height-surplusLabel->getContentSize().height)/2);
    layerBg->addChild(surplusLabel);
    
    //按钮
    Button* btn=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsProps_Layer::onBtnListClick, this));
    btn->setPosition(295+btn->getContentSize().width/2,10+btn->getContentSize().height/2);
    btn->setTag((int)idx);
    if (data->propsCanUse==0 or (data->propsUseType==DictItemUseTypeEnumPowerUse and GlobalInfo::getInstance()->bodyPower>=GlobalInfo::getInstance()->bodyPowerMax)) {
        btn->setEnabled(false);
    }
    layerBg->addChild(btn);
    
    Sprite*btnLabel=Sprite::create(IMG_PUBLIC_LABEL_USE);
    btn->addChild(btnLabel,2);
    
    return layerBg;
}
//列表大小
Size GeneralsProps_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+8;
    cellSize.width = temp->getContentSize().width *2+10;
    return cellSize;
}
//获取view的长度
ssize_t GeneralsProps_Layer::numberOfCellsInTableView(TableView *table)
{
    int titleCount=ceil((float)propsList->size()/2);
    return titleCount;
}
//点击cell事件
void GeneralsProps_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}

void GeneralsProps_Layer::onBtnListClick(Ref* psender)
{
    if (!this->isClick) {
        return;
    }
    this->isClick=false;
    Sprite* sp=(Sprite*)psender;
    int tag=sp->getTag();
    PropsData* data  = propsList->at(tag);
    
    PropsItemUseMsg* msg = new PropsItemUseMsg(data->propsId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
//-------------------------------------------------服务器部分----------------------------------------------------//
void GeneralsProps_Layer::requestListMsg()
{
    PropsItemPage* msg = new PropsItemPage();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsProps_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_ITEM_ItemPageResp)
    {
        
        if (message->state==true) {
            propsList->clear();
            int itemCount=message->byteStream->getShort();
            for (int i=0; i<itemCount; i++) {
                PropsData* data  = new PropsData();
                data->autorelease();
                data->propsId=message->byteStream->getInt();
                data->propsUseType=message->byteStream->getByte();
                data->propsQuality=message->byteStream->getByte();
                data->propsName=message->byteStream->getUTF8();
                data->propsDesc=message->byteStream->getUTF8();
                data->propsNumber=message->byteStream->getInt();
                data->propsCanUse=message->byteStream->getByte();
                data->propResource=message->byteStream->getUTF8();
                data->subType= message->byteStream->getShort();
                DictItem* itemData=DictItemManager::getInstance()->getData(data->propsId);
                if (itemData) {
                    data->backPackOrder=itemData->seq;
                }
                if (data->subType == 1) {
                    propsList->pushBack(data);
                }
            }
            this->sortList(thisSort);
            if (propsNumberLabel) {
                propsNumberLabel->setString(PublicShowUI::numberToString((int)propsList->size()));
            }
        }
        this->isClick=true;
        
    }else if (message->messageID == SCENSE_CLIENT_ITEM_ItemUseResp)
    {
        if (message->state==false) {
            return;
        }
        MarketFindResultDataManager::getInstance()->clearDumpList();
        int rewardType=message->byteStream->getByte();
        int itemCount=message->byteStream->getByte();
        for (int i=0; i<itemCount; i++) {
            MarketFindResultData* data  = new MarketFindResultData();
            data->autorelease();
            data->itemType=message->byteStream->getByte();
            data->itemId=message->byteStream->getInt();
            data->quality=message->byteStream->getByte();
            data->name=message->byteStream->getUTF8();
            MarketFindResultDataManager::getInstance()->addData(data);
        }
        if (rewardType==2) {
            this->runEffect();
        }
        else if (rewardType==1)
        {
            this->requestListMsg();
        }
    }
}
void GeneralsProps_Layer::runEffect()
{
    Dialog::showServerLoading(5);
    CommonEffect* commonEffect = CommonEffect::create("baoxiangdonghua",false,true,CC_CALLBACK_0(GeneralsProps_Layer::effectOver, this));
    commonEffect->setAnchorPoint(Point(0.5,0.5));
    PublicShowUI::setTargetScale(commonEffect);
    commonEffect->setPosition((this->getContentSize().width)/2,(this->getContentSize().height)/2);
    this->addChild(commonEffect,12);
}
void GeneralsProps_Layer::effectOver()
{
    Dialog::hideServerLoading();
    this->requestListMsg();
    MarketGoodsLayer* goodsLayer = MarketGoodsLayer::create(false);
    goodsLayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(goodsLayer);
    goodsLayer->setPositionX(VisibleRect::center().x-goodsLayer->getContentSize().width/2);
    goodsLayer->setPositionY(VisibleRect::center().y - goodsLayer->getContentSize().height/2);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(goodsLayer, SCENE_TWOLAYER_ZORDER);
}
void GeneralsProps_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ITEM_ItemPageResp).c_str(), CC_CALLBACK_1(GeneralsProps_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ITEM_ItemUseResp).c_str(), CC_CALLBACK_1(GeneralsProps_Layer::onMsgProcess, this));
}
void GeneralsProps_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
//状态排序

bool sortOnBoxUse(PropsData* n1, PropsData* n2)
{
    return n1->propsUseType == DictItemUseTypeEnumBoxUse;
}

bool sortOnBoxPackOrder(PropsData* n1, PropsData* n2)
{
    return n1->backPackOrder < n2->backPackOrder;
}
bool sortOnBoxQuality(PropsData* n1, PropsData* n2)
{
    return n1->propsQuality < n2->propsQuality;
}
void GeneralsProps_Layer::sortList(string name)
{
    if (name=="drug") {
        thisSort="drug";
        stable_sort(propsList->begin(), propsList->end(),sortOnBoxQuality);
        stable_sort(propsList->begin(), propsList->end(),sortOnBoxPackOrder);
    }else if (name=="box")
    {
        thisSort="box";
        stable_sort(propsList->begin(), propsList->end(),sortOnBoxPackOrder);
        stable_sort(propsList->begin(), propsList->end(),sortOnBoxQuality);
        stable_sort(propsList->begin(), propsList->end(),sortOnBoxUse);
    }

    this->initTableView();

}