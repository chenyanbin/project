//
//  GeneralsRiseQuality_Layer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/11.
//
//

#include "GeneralsRiseQuality_Layer.hpp"

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
GeneralsRiseQuality_Layer::GeneralsRiseQuality_Layer()
:TAG_TABLEVIEW(1)
,TAG_ALLPROPS(2)
,propsNumberLabel(NULL)
,sx(1)
,isClick(false)
{
    propsList=new Vector<PropsData*>();
}
GeneralsRiseQuality_Layer::~ GeneralsRiseQuality_Layer()
{
    propsList->clear();
    CC_SAFE_DELETE(propsList);
    
}
GeneralsRiseQuality_Layer* GeneralsRiseQuality_Layer::create()
{
    GeneralsRiseQuality_Layer* layer = new GeneralsRiseQuality_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
bool GeneralsRiseQuality_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx= GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG);
        
        bref = true;
    } while (false);
    return bref;
}
void GeneralsRiseQuality_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsRiseQuality_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsRiseQuality_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
void GeneralsRiseQuality_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->removeEventListener();
}

void GeneralsRiseQuality_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        this->removeChildByTag(TAG_TABLEVIEW);
    }
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+_size.height/2+30;
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

////-------------------------------------------------TableView部分-------------------------------------------------//
TableViewCell* GeneralsRiseQuality_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
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
Sprite* GeneralsRiseQuality_Layer::singleList(ssize_t idx)
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
//    Button* btn=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsRiseQuality_Layer::onBtnListClick, this));
//    btn->setPosition(295+btn->getContentSize().width/2,10+btn->getContentSize().height/2);
//    btn->setTag((int)idx);
//    if (data->propsCanUse==0 or (data->propsUseType==DictItemUseTypeEnumPowerUse and GlobalInfo::getInstance()->bodyPower>=GlobalInfo::getInstance()->bodyPowerMax)) {
//        btn->setEnabled(false);
//    }
//    layerBg->addChild(btn);
//    
//    Sprite*btnLabel=Sprite::create(IMG_PUBLIC_LABEL_USE);
//    btn->addChild(btnLabel,2);
    
    return layerBg;
}
//列表大小
Size GeneralsRiseQuality_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+8;
    cellSize.width = temp->getContentSize().width *2+10;
    return cellSize;
}
//获取view的长度
ssize_t GeneralsRiseQuality_Layer::numberOfCellsInTableView(TableView *table)
{
    int titleCount=ceil((float)propsList->size()/2);
    return titleCount;
}
//点击cell事件
void GeneralsRiseQuality_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}

//-------------------------------------------------服务器部分----------------------------------------------------//
void GeneralsRiseQuality_Layer::requestListMsg()
{
    PropsItemPage* msg = new PropsItemPage();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsRiseQuality_Layer::onMsgProcess(EventCustom* msg)
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
                if (data->subType == 2) {
                    propsList->pushBack(data);
                }
            }
            this->initTableView();
            if (propsNumberLabel) {
                propsNumberLabel->setString(PublicShowUI::numberToString((int)propsList->size()));
            }
        }
        this->isClick=true;
        
    }
}
void GeneralsRiseQuality_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ITEM_ItemPageResp).c_str(), CC_CALLBACK_1(GeneralsRiseQuality_Layer::onMsgProcess, this));
}
void GeneralsRiseQuality_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}


