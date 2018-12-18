//
//  Getpath_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/8.
//
//

#include "Getpath_Layer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../commonData/dictData/Dictway/DictWayManager.h"
#include "../../message/Decoding/itemWay/itemWayMsg.h"
#include "../../commonData/dictData/DictItemMater/DictItemMaterManager.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../../commonData/dictData/DictItemBook/DictItemBookManager.h"
#include "../../commonData/dictData/DictItem/DictItemManager.h"
#include "../../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../commonData/dictData/DictStage/DictStageManager.h"
#include "GotoModule.h"
Getpath_Layer::Getpath_Layer()
:sx(1)
,TAG_TABLEVIEW(3)
,_itemType(0)
,_itemQuality(0)
,_itemId(0)
,_fromMoudeId(0)
,currentItemName("")
,currentItemDesc("")
,currentItemCount(0)
,nameLabel(NULL)
,numLabel(NULL)
,descLabel(NULL)
,isMoveing(false)
{
    wayList=new Vector<WayData*>();
}
Getpath_Layer::~Getpath_Layer()
{
    wayList->clear();
    CC_SAFE_DELETE(wayList);
    
}
void Getpath_Layer::onExit()
{
    BaseLayer::onExit();
}
void Getpath_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void Getpath_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void Getpath_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
bool Getpath_Layer::init(int itemType ,int itemId,int itemQuality,int fromLayer)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        _itemType=itemType;
        _itemId=itemId;
        _itemQuality=itemQuality;
        _fromMoudeId=fromLayer;
        
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->isShowGrayBg = true;
//        this->isClickClose = true;
        this->setClickEnabled(true);
        
        this->setBackground(IMG_PUBLIC_LAYER_GETPATH);
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
Getpath_Layer* Getpath_Layer::create(int itemType ,int itemId,int itemQuality,int fromLayer)
{
    Getpath_Layer* layer = new Getpath_Layer();
    if(layer && layer->init(itemType,itemId,itemQuality,fromLayer))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void Getpath_Layer::show(int fromLayer,int itemType ,int itemId,int itemQuality)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    
    if(scene->getChildByTag(SCENE_TAG_GETPATH))
    {
        return;
    }
    
    Getpath_Layer* layer = Getpath_Layer::create(itemType,itemId,itemQuality,fromLayer);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
    layer->setAnchorPoint(Point(0.5,0.5));
    layer->setFromScene(fromLayer);
    scene->addChild(layer,SCENE_LAYER_ZORDER,SCENE_TAG_GETPATH);
}

void Getpath_Layer::createLayer()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    
    Sprite* titleSprite=Sprite::create(IMG_PUBLIC_GETPATH);
    titleSprite->setAnchorPoint(Point::ZERO);
    titleSprite->setPosition(390,483);
    bg->addChild(titleSprite);
    
    Sprite* ball=Sprite::create(IMG_PUBLIC_LAYER_BALL);
    ball->setAnchorPoint(Point::ZERO);
    ball->setPosition(373,489);
    bg->addChild(ball);
    UserEquipLayer* head=NULL;
    string resource ="";
    if (_itemType==DictItemTypeEnumItemBook) {
        DictItemBook* bookData=DictItemBookManager::getInstance()->getData(_itemId);
        if (!bookData) {
            return;
        }
        resource = bookData->resource;
        const char* path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,resource.c_str());
        head=UserEquipLayer::create(path,_itemQuality,false);
    }else if (_itemType==DictItemTypeEnumItemMater)
    {
        DictItemMater* materData=DictItemMaterManager::getInstance()->getData(_itemId);
        if (!materData) {
            return;
        }
        resource = materData->resource;
        head=UserEquipLayer::create(resource,_itemQuality);
    }
    else if(_itemType == DictItemTypeEnumItem)
    {
        DictItem* dictItem = DictItemManager::getInstance()->getData(_itemId);
        if (!dictItem) {
            return;
        }
        resource = dictItem->resource;
        head=UserEquipLayer::create(resource,_itemQuality);
    }
    else if(_itemType == DictItemTypeEnumItemEquip)
    {
        DictItemEquip* dictItem = DictItemEquipManager::getInstance()->getData(_itemId);
        if (!dictItem) {
            return;
        }
        resource = dictItem->resource;
        head=UserEquipLayer::create(resource,_itemQuality);
    }
    if(!head)
    {
        return;
    }
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(65,324);
    bg->addChild(head);
    
    string nameStr="";
    
    nameLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(40,282);
    bg->addChild(nameLabel);
    
    Sprite* numSprite=Sprite::create(IMG_PUBLIC_LABEL_CURRENTNUM);
    numSprite->setAnchorPoint(Point::ZERO);
    numSprite->setPosition(40,239);
    bg->addChild(numSprite);
    
    string numStr="";
    numLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(0xff5d5d),20,false,false);
    numLabel->setAnchorPoint(Point::ZERO);
    numLabel->setPosition(numSprite->getPositionX()+numSprite->getContentSize().width+10,numSprite->getPositionY());
    bg->addChild(numLabel);
    
    numStr="";
    descLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(0x90ac68),20,false,false);
    descLabel->setAnchorPoint(Point(0,1));
    descLabel->setPosition(32,211);
    descLabel->setMaxLineWidth(180);
    bg->addChild(descLabel);
    
}
//--------------------------------列表部分-------------------------------------------------------//

void Getpath_Layer::initTableView()
{
        Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
        TableView* _tableView = (TableView*)listBg->getChildByTag(TAG_TABLEVIEW);
        //
        if(_tableView)
        {
            Point cp=_tableView->getContentOffset();
            _tableView->reloadData();
            _tableView->setContentOffset(cp);
            return;
        }
        Size _size=tableCellSizeForIndex(NULL,NULL);
        _size.width=_size.width;
        _size.height=_size.height*3-38;
        _tableView =TableView::create(this,_size);
        _tableView->setDelegate(this);
        _tableView->setDirection(TableView::Direction::VERTICAL);
        _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
        _tableView->setAnchorPoint(Point(0, 0));
        _tableView->setPosition(246,20);
        listBg->addChild(_tableView,4,TAG_TABLEVIEW);
}
TableViewCell* Getpath_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    WayData* data=wayList->at(idx);
    int tag=(int)idx;
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Sprite* cellBg=Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellBg->setAnchorPoint(Point::ZERO);
    cell->addChild(cellBg);

    string resource="";
    Vector<DictWay*>* list =DictWayManager::getInstance()->getDataList();
    for (DictWay* Dictdata:*list) {
        if (Dictdata->function==data->wayFunction) {
            resource=Dictdata->resource;
            break;
        }
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    if(resource == "")
    {
        return cell;
    }
    //头像背景
    const char*path=PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM,resource.c_str());
    UserEquipLayer* head=UserEquipLayer::create(path,_itemQuality,false);
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(22,24);
    cellBg->addChild(head);
    
    string titleStr=data->wayName;
    string titleCount;
    if (data->wayMaxCount<0) {
         titleCount="(0/0)";
    }else
    {
         titleCount="("+PublicShowUI::numberToString(data->wayCount)+"/"+PublicShowUI::numberToString(data->wayMaxCount)+")";
    }
    
    Label* titlelLabel = PublicShowUI::getLabel(titleStr.c_str(),PublicShowUI::getColor3b(0x46e22c),20,false,false);
    titlelLabel->setAnchorPoint(Point::ZERO);
    titlelLabel->setPosition(157,110);
    cellBg->addChild(titlelLabel);
    
    Label* titleCountLabel = PublicShowUI::getLabel(titleCount.c_str(),PublicShowUI::getColor3b(0xff6000),20,false,false);
    titleCountLabel->setAnchorPoint(Point::ZERO);
    titleCountLabel->setPosition(titlelLabel->getPositionX()+titlelLabel->getContentSize().width+20,110);
    cellBg->addChild(titleCountLabel);
    
    titleStr=data->wayDesc;
    Label* contentLabel=PublicShowUI::getLabel(titleStr.c_str(),PublicShowUI::getColor3b(0xbbdb8d ),18,false,false);
    contentLabel->setAnchorPoint(Point(0,1));
    contentLabel->setPosition(157,100);
    contentLabel->setMaxLineWidth(280);
    cellBg->addChild(contentLabel);
    
    //前往
    Button* gotoBtn = Button::create(IMG_PUBLIC_BUTTON_GOTO,"", CC_CALLBACK_1(Getpath_Layer::onBtnClick, this));
//    gotoBtn->setAnchorPoint(Point::ZERO);
    gotoBtn->setPosition(280+gotoBtn->getContentSize().width/2,10+gotoBtn->getContentSize().height/2);
    gotoBtn->setTag(tag);
    if (data->wayMaxCount<0) {
        gotoBtn->setEnabled(false);
    }
    cellBg->addChild(gotoBtn);
    
    
    return cell;
}
//列表大小
Size Getpath_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* cellBg=Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    
    cellSize.height=cellBg->getContentSize().height;
    cellSize.width=cellBg->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t Getpath_Layer::numberOfCellsInTableView(TableView *table)
{
//    int count = (int)equipList->size()/4+1;
    int count = (int)wayList->size();
    return count;
}
//点击cell事件
void Getpath_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = true;
    log("%d",cell->getTag());
}
void Getpath_Layer::onBtnClick(Ref* psender)
{
    Sprite* sp=(Sprite*)psender;
    int tag=sp->getTag();
    WayData* data=wayList->at(tag);
    if(data->wayStageId)
    {
        
        DictStageBattle* dictStageBattle = DictStageBattleManager::getInstance()->getData(data->wayStageId);
        if(dictStageBattle->inStageId)
        {
            GlobalInfo::getInstance()->selectedStageBattle = data->wayStageId;
            GlobalInfo::getInstance()->taskInStageBattle = dictStageBattle->inStageId;
            GotoModule::param1 =  data->wayCount == -1 ? NULL : __Integer::create(dictStageBattle->inStageId);
        }
       
    }
   
    GotoModule::gotoModuleByFunctionID(data->wayFunction,_fromMoudeId);
}
void Getpath_Layer::updateLabel()
{
    if (nameLabel) {
        nameLabel->setString(currentItemName);
    }
    if (numLabel) {
        numLabel->setString(PublicShowUI::numberToString(currentItemCount));
    }
    if (descLabel) {
        descLabel->setString(currentItemDesc);
    }
}
//------------------------------------------------------------服务器返回------------------------------------------------------------//
void Getpath_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_ITEM_ItemWayResp)
    {
        wayList->clear();
        currentItemName=message->byteStream->getUTF8();
        currentItemDesc=message->byteStream->getUTF8();
        currentItemCount=message->byteStream->getInt();
        
        int _count=message->byteStream->getShort();
        for (int i=0; i<_count; i++) {
            WayData* data  = new WayData();
            data->autorelease();
//            data->wayId=message->byteStream->getByte();
            data->wayName=message->byteStream->getUTF8();
            data->wayDesc=message->byteStream->getUTF8();
            data->wayCount=message->byteStream->getInt();//int	Y	不同way，次数有不同的定义
//            战役：当日可进次数, -1未开启
//            举贤：免费举贤次数
//            寻访：寻访
//            其他：没有

            data->wayMaxCount=message->byteStream->getInt();
            data->wayFunction=message->byteStream->getByte();
            data->wayStageId=message->byteStream->getInt();
            data->wayBattleMode=message->byteStream->getByte();
            wayList->pushBack(data);
        }
        this->updateLabel();
        this->initTableView();
    }
}

void Getpath_Layer::requestListMsg()
{
//    DictwayManager
    itemWayMsg* msg = new itemWayMsg(_itemType,_itemId,_itemQuality);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
//---------------------------------------------------------------监听-----------------------------------------------------------------//
void Getpath_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ITEM_ItemWayResp).c_str(), CC_CALLBACK_1(Getpath_Layer::onMsgProcess, this));
}
void Getpath_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

void Getpath_Layer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            isMoveing = true;
        }
    }
    
}
bool Getpath_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    isMoveing = false;
    return true;
}
void Getpath_Layer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
    
}
void Getpath_Layer::onTouchEnded(Touch *touch, Event *unused_event)
{
   
    BaseLayer::onTouchEnded(touch, unused_event);
    closeScene();
}
void Getpath_Layer::closeScene()
{
    if (isMoveing == false) {
        this->removeFromParent();
    }
    
}