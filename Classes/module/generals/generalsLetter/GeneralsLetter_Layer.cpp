//
//  GeneralsLetter_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/19.
//
//

#include "GeneralsLetter_Layer.h"

#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../message/Decoding/generals/letter/LetterPageMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/generals/letter/LetterDeliverMsg.h"
#include "../../../message/Decoding/generals/letter/LetterGiftMsg.h"
#include "../../../message/Decoding/generals/letter/LetterInviteMsg.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../publicLayer/Getpath_Layer.h"
#include "../../market/marketData/MarketFindResultDataManager.h"
#include "../../market/marketFind/MarketGetHeroLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/dictData/DictItemBook/DictItemBookManager.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../protocol/UserCustomEvent.h"
GeneralsLetter_Layer::GeneralsLetter_Layer()
:TAG_TABLEVIEW(1)
,TAG_LATTERNUM(2)
,TAG_ALLLETTER(3)
,sx(1)
,giftCount(0)
,giftCountMax(0)
,equipNumLabel(NULL)
,todayNumLabel(NULL)
,isSort(true)
{
    letterList=new Vector<LetterData*>();
}
GeneralsLetter_Layer::~GeneralsLetter_Layer()
{
    letterList->clear();
    CC_SAFE_DELETE(letterList);

}
GeneralsLetter_Layer* GeneralsLetter_Layer::create()
{
    GeneralsLetter_Layer* layer = new GeneralsLetter_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
bool GeneralsLetter_Layer::init()
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
void GeneralsLetter_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsLetter_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsLetter_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
//    this->initTableView();
}
void GeneralsLetter_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

void GeneralsLetter_Layer::createLayer()
{
 
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    if (listBg) {
//        Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_LISTBG2);
//        listBg2->setAnchorPoint(Point::ZERO);
//        PublicShowUI::setTargetScale(listBg2);
//        listBg2->setPosition(listBg->getPositionX()+ 34*sx,listBg->getPositionY()+465*sx);
//        this->addChild(listBg2);
//        
//        const char* pathList[2] = {IMG_PUBLIC_LABEL_MASS2_FIRST,IMG_PUBLIC_LABEL_NUMBER2_FIRST};
//        const char* pathList2[2] = {IMG_PUBLIC_LABEL_MASS_FIRST,IMG_PUBLIC_LABEL_NUMBER_FIRST};
//        ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 0, CC_CALLBACK_1(GeneralsLetter_Layer::onTopComboBoxClick, this));
//        for (int i = 0; i<2; i++) {
//            boxBtn->addBtn(pathList[i], pathList2[i], "");
//        }
//        boxBtn->setAnchorPoint(Point::ZERO);
//        boxBtn->setPosition(6*sx,(listBg2->getContentSize().height/sx-boxBtn->getContentSize().height)/2);
//        boxBtn->getButtonAt(0)->selected();
//        listBg2->addChild(boxBtn,3);
        
//        Sprite* today=Sprite::create(IMG_PUBLIC_LABEL_DAYNUM);
//        today->setAnchorPoint(Point::ZERO);
//        today->setPosition(400,(listBg2->getContentSize().height/sx-today->getContentSize().height)/2);
//        listBg2->addChild(today);
        
//        string numStr="今日送礼次数:";
//        Label* today=PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
//        today->setAnchorPoint(Point::ZERO);
//        PublicShowUI::setTargetScale(today);
//        today->setPosition(listBg->getPositionX()+45*sx,listBg->getPositionY()+18*sx);
//        this->addChild(today);
//        
//        numStr="0";
//        todayNumLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_DARK_GREEN),18,false,false);
//        todayNumLabel->setAnchorPoint(Point::ZERO);
//        PublicShowUI::setTargetScale(todayNumLabel);
//        todayNumLabel->setPosition(today->getContentSize().width+today->getPositionX()+10,today->getPositionY());
//        this->addChild(todayNumLabel,1);
//        
//        numStr="书信数量:";
//        Label* equipNumSprite=PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
//        equipNumSprite->setAnchorPoint(Point::ZERO);
//        PublicShowUI::setTargetScale(equipNumSprite);
//        equipNumSprite->setPosition(todayNumLabel->getPositionX()+80,todayNumLabel->getPositionY());
//        this->addChild(equipNumSprite);
//        
//        numStr="0";
//        equipNumLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_DARK_GREEN),18,false,false);
//        equipNumLabel->setAnchorPoint(Point::ZERO);
//        equipNumLabel->setPosition(equipNumSprite->getContentSize().width+equipNumSprite->getPositionX()+10,equipNumSprite->getPositionY());
//        this->addChild(equipNumLabel,1);
        
    }

}

void GeneralsLetter_Layer::onTopComboBoxClick(Ref* psender)
{
//    Node* sp=(Node*)psender;
//    int tag=sp->getTag();
//    string tempStr="0";
//    switch (tag) {
//        case 0:
//            tempStr="quality";
//            break;
//        case 1:
//            tempStr="number";
//            break;
//        case 2:
//            tempStr="prestige";
//            break;
//        default:
//            break;
//    }
//    this->sortList(tempStr);
}
void GeneralsLetter_Layer::onUpdata()
{    
    if (equipNumLabel) {
        equipNumLabel->setString(PublicShowUI::numberToString(letterList->size()));
    }
    if (todayNumLabel) {
        todayNumLabel->setString(PublicShowUI::numberToString(giftCount)+"/"+PublicShowUI::numberToString(giftCountMax));
    }
//    this->sortList("quality");
}

//-------------------------------------------------TableView部分-------------------------------------------------//
void GeneralsLetter_Layer::initTableView()
{
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+120;
    _tableView =TableView::create(this,_size);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    if (listBg) {
        _tableView->setPosition(listBg->getPositionX()+30*sx,listBg->getPositionY()+53*sx);
    }
//    _tableView->setPosition(36*sx,53*sx);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(6*sx,40*sx);
    this->addChild(shade,3);
}


TableViewCell* GeneralsLetter_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    
    for (int i=0; i<2; i++) {
        if (idx*2+i<letterList->size()) {
            Sprite* list=singleList(idx*2+i);
            list->setPosition(i*(list->getContentSize().width+8),5);
            cell->addChild(list,1);
        }
    }
    
    return cell;
}
//单个列表内容
Sprite* GeneralsLetter_Layer::singleList(ssize_t idx)
{
    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    layerBg->setTag((int)idx);
    //头像
    int tag=(int)idx;
    LetterData* data=letterList->at(tag);
    
    UserHeadLayer* head=UserHeadLayer::create(data->resource,data->heroQuality);
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(23,32);
    head->setFragment();
    layerBg->addChild(head);
    head->setHeadInfo(1,1);
    
//    //名字
//    string nameStr="";
//    DictHeroQuality* qualityData=DictHeroQualityManager::getInstance()->getData(data->heroQuality);
//    nameStr= data->heroName;
//    if (qualityData) {
//        nameStr=qualityData->name+" "+data->heroName;
//    }
//    Label* nameLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
//    nameLabel->setAnchorPoint(Point::ZERO);
//    nameLabel->setPosition((layerBg->getContentSize().width-nameLabel->getContentSize().width)/2,170);
//    layerBg->addChild(nameLabel);
    
    //名字背景
    Sprite* nameBg=Sprite::create(IMG_PUBLIC_EQUIP_NAMEBG);
    nameBg->setAnchorPoint(Point::ZERO);
    nameBg->setPosition(152,110);
    layerBg->addChild(nameBg,2);
    
    string name= data->heroName;
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
    
    float totalExperence = data->needBookCount;
    float percent =  data->curBookCount / totalExperence;
    ProgressTimer* expProgress = ProgressTimer::create(Sprite::create(IMG_GENERALS_MATERIAL_PROGRESS));
    expProgress->setType(ProgressTimer::Type::BAR);
    expProgress->setMidpoint(Point(0,1));
    expProgress->setBarChangeRate(Point(1,0));
    expProgress->setAnchorPoint(Point(0 ,0));
    expProgress->setPosition(255,70);
    layerBg->addChild(expProgress);
    expProgress->setPercentage(percent * 100);
    
    
    string numStr=PublicShowUI::numberToString(data->curBookCount)+"/"+PublicShowUI::numberToString(data->needBookCount);
    Label* numLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),16,false,false);
    numLabel->setAnchorPoint(Point::ZERO);
    numLabel->setPosition(300,progressBg->getPositionY()+(progressBg->getContentSize().height-numLabel->getContentSize().height)/2+1);
    layerBg->addChild(numLabel);

    
//    //进度条
//    
//    float totalExperence = data->letterHeroMaxFriends;
//    float percent =  data->letterHeroFriends / totalExperence;
//    
//    ProgressTimer* expProgress = ProgressTimer::create(Sprite::create(IMG_GENERALS_LATTER_PROGRESS));
//    expProgress->setType(ProgressTimer::Type::BAR);
//    expProgress->setMidpoint(Point(0,1));
//    expProgress->setBarChangeRate(Point(1,0));
//    expProgress->setAnchorPoint(Point(0 ,0));
//    expProgress->setPosition(248,120);
//    layerBg->addChild(expProgress,2);
//    expProgress->setPercentage(percent * 100);
    
    
    //按钮
    Button* btn=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsLetter_Layer::onBtnListClick, this));
    //    btn->setAnchorPoint(Point::ZERO);
    btn->setPosition(287+btn->getContentSize().width/2,15+btn->getContentSize().height/2);
    layerBg->addChild(btn);
    
    Sprite* btnLabel=NULL;
    if (data->curBookCount>=data->needBookCount) {
        PublicShowUI::setDot(btn, Point(btn->getContentSize().width/2, btn->getContentSize().height/2), false,DictFunctionEnumBook);
        btnLabel=Sprite::create(IMG_PUBLIC_LABEL_COMPOUND);
        btn->setTag(BUTTON_DEYAMA);
    }else
    {
        btnLabel=Sprite::create(IMG_PUBLIC_LABEL_GAIN);
        btn->setTag(BUTTON_GAIN);
    }
    if(idx == 0)
    {
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumCompositeButton, btn);
        
    }
    btn->addChild(btnLabel,2);
    
    //按钮2
//    string numStr=PublicShowUI::numberToString(data->letterHeroFriends)+"/"+PublicShowUI::numberToString(data->letterHeroMaxFriends);
//    Label* numLabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),16,false,false);
//    numLabel->setAnchorPoint(Point::ZERO);
//    numLabel->setPosition(300,expProgress->getPositionY()+(expProgress->getContentSize().height-numLabel->getContentSize().height)/2+1);
//    layerBg->addChild(numLabel,3);
//    
//    if (data->letterHeroFriends==data->letterHeroMaxFriends) {
//        Button* btn2=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsLetter_Layer::onBtnListClick, this));
//        btn2->setAnchorPoint(Point(0.5,0.5));
//        layerBg->addChild(btn2);
//        btn2->setPosition(216+btn2->getContentSize().width/2,50+btn2->getContentSize().height/2);
//        btn2->setTag(BUTTON_DEYAMA);
//        
//        Sprite*btnLabel=Sprite::create(IMG_PUBLIC_LABEL_DEYAMA);
//        btnLabel->setAnchorPoint(Point(0.5,0.5));
//        btn2->addChild(btnLabel,2);
//    }else
//    {
//        //书信数量
//        Sprite* latterNumSprite=Sprite::create(IMG_GENERALS_LATTER_NUMBER);
//        latterNumSprite->setAnchorPoint(Point::ZERO);
//        latterNumSprite->setPosition(147,20);
//        layerBg->addChild(latterNumSprite);
//        //书信数量个数
//        string num=PublicShowUI::numberToString(data->letterHeroNumber);
//        Label* latterNumLabel = PublicShowUI::getLabel(num.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),16,false,false);
//        latterNumLabel->setAnchorPoint(Point(0,0.5));
//        latterNumLabel->setPosition((latterNumSprite->getContentSize().width+10),15);
//        latterNumSprite->addChild(latterNumLabel);
//        
//        //元宝
//        Sprite* expendSprite=Sprite::create(IMG_GENERALS_LATTER_EXPEND);
//        expendSprite->setAnchorPoint(Point::ZERO);
//        expendSprite->setPosition(292,20);
//        layerBg->addChild(expendSprite);
//        if (data->letterHeroConsume>0) {
//            num=PublicShowUI::numberToString(data->letterHeroConsume);
//        }else{
//            num="";
//        }
//        
//        Label* goldLabel=PublicShowUI::getLabel(num.c_str(),PublicShowUI::getColor3b(COLOR_NORMAL_YELLOW),16,false,false);
//        goldLabel->setAnchorPoint(Point(0,0.5));
//        goldLabel->setPosition(expendSprite->getContentSize().width+expendSprite->getPositionX(),expendSprite->getContentSize().height/2+expendSprite->getPositionY());
//        layerBg->addChild(goldLabel);
//
//        //第一个按钮
//        Button* btn1=Button::create(IMG_PUBLIC_BUTTON_TWO_RED,"", CC_CALLBACK_1(GeneralsLetter_Layer::onBtnListClick, this));
//        btn1->setPosition(148+btn1->getContentSize().width/2,50+btn1->getContentSize().height/2);
//        layerBg->addChild(btn1);
//        
//        Sprite* btn1Label;
//        if (data->letterHeroNumber==0) {
//            btn1Label=Sprite::create(IMG_PUBLIC_LABEL_GAIN);
//            btn1->setTag(BUTTON_GAIN);
//        }else
//        {
//            btn1Label=Sprite::create(IMG_PUBLIC_LABEL_GIVELETTERS);
//            btn1->setTag(BUTTON_LETTER);
//        }
//        btn1Label->setPosition(Point(0.5,0.5));
//        btn1->addChild(btn1Label,2);
//        
//        Button* btn2=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsLetter_Layer::onBtnListClick, this));
//        if (data->letterHeroConsume==-1) {
//            btn2->setEnabled(false);
//        }
//        layerBg->addChild(btn2);
//        btn2->setPosition(290+btn2->getContentSize().width/2,50+btn2->getContentSize().height/2);
//        Sprite* btn2Label=btn2Label=Sprite::create(IMG_PUBLIC_LABEL_GIFTS);
//        btn2Label->setPosition(Point(0.5,0.5));
//        btn2->addChild(btn2Label,2);
//        
//        //按钮2字体
//        if (giftCount==giftCountMax) {
//            btn2->setTag(BUTTON_NOTGIFTS);
//            btn2->setEnabled(false);
//        }else
//        {
//            btn2->setTag(BUTTON_GIFTS);
//        }
//    }
    
    return layerBg;
}
//列表大小
Size GeneralsLetter_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
//    PublicShowUI::setTargetScale(temp);
    cellSize.height = temp->getContentSize().height+8;
    cellSize.width = temp->getContentSize().width ;
    cellSize.width=cellSize.width*2+10;
    return cellSize;
}
//获取view的长度
ssize_t GeneralsLetter_Layer::numberOfCellsInTableView(TableView *table)
{
    int titleCount=ceil((float)letterList->size()/2);
    return titleCount;
}
//点击cell事件
void GeneralsLetter_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}

void GeneralsLetter_Layer::onBtnListClick(Ref* psender)
{
    Node* node=(Node*) psender;
    int tag=node->getTag();
    int parentTag=node->getParent()->getTag();
    int letterId=letterList->at(parentTag)->bookId;
//    letterList
    if (tag==BUTTON_LETTER) {//送信
        
        LetterDeliverMsg* msg = new LetterDeliverMsg(letterId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }else if (tag==BUTTON_GIFTS)//送礼
    {
        
        LetterGiftMsg* msg = new LetterGiftMsg(letterId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;

    }else if (tag==BUTTON_NOTGIFTS)//送礼次数最大了
    {
        
    }else if (tag==BUTTON_GAIN)//获得
    {
        Vector<DictItemBook*>* list=DictItemBookManager::getInstance()->getDataList();
        int letterID=0;
        for (DictItemBook* data:*list) {
            if (data->heroId==letterList->at(parentTag)->heroDictId) {
                letterID=data->id;
            }
        }
        CC_SAFE_DELETE(list);
        list = NULL;
        Scene* scene = Director::getInstance()->getRunningScene();
        if(scene->getChildByTag(SCENE_TAG_GETPATH))
        {
            return;
        }
        Getpath_Layer* layer = Getpath_Layer::create(DictItemTypeEnumItemBook,letterID,letterList->at(parentTag)->heroQuality,SCENE_TAG_MAINUI);//SCENE_TAG_GENERALS_LATER
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
        layer->setAnchorPoint(Point(0.5,0.5));
        scene->addChild(layer,SCENE_TWOLAYER_ZORDER,SCENE_TAG_GETPATH);
    }else if (tag==BUTTON_DEYAMA)//出山
    {
        LetterInviteMsg* msg = new LetterInviteMsg(letterId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
}
//-------------------------------------------------服务器部分----------------------------------------------------//
void GeneralsLetter_Layer::requestListMsg()
{
    
    LetterPageMsg* msg = new LetterPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsLetter_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_BOOK_BookPage2Resp)
    {
        
        letterList->clear();
//        giftCount=message->byteStream->getShort();
//        giftCountMax=message->byteStream->getShort();
        int _size=message->byteStream->getShort();
        for (int i=0; i<_size; i++) {
            LetterData* data=new LetterData();
            data->bookId = message->byteStream->getInt();
            data->heroDictId = message->byteStream->getInt();
            data->heroQuality = message->byteStream->getByte();
            data->heroName = message->byteStream->getUTF8();
            data->curBookCount = message->byteStream->getShort();
            data->needBookCount = message->byteStream->getShort();
            data->costCoin = message->byteStream->getInt();
            data->resource = message->byteStream->getUTF8();
//            data->letterId=message->byteStream->getInt();
//            data->letterHeroDictId=message->byteStream->getInt();
//            data->letterHeroQuality=message->byteStream->getByte();
//            data->letterHeroName=message->byteStream->getUTF8();
//            data->letterHeroFriends=message->byteStream->getShort();
//            data->letterHeroMaxFriends=message->byteStream->getShort();
//            data->letterHeroNumber=message->byteStream->getShort();
//            data->letterHeroConsume=message->byteStream->getShort();
//            data->letterHeroResource=message->byteStream->getUTF8();
//            DictItemBook* bookData=DictItemBookManager::getInstance()->getData(data->bookId);
//            if (bookData) {
//                data->letterBackPackOrder=bookData->seq;
//            }
            letterList->pushBack(data);
        }
        this->initTableView();
//        this->onUpdata();
    }else if (message->messageID == SCENSE_CLIENT_BOOK_BookDeliverResp)
    {
        this->isSort=false;
        NoticeManager::getInstance()->showNotice("送信成功",NoticeManager::COLOR_GREEN);
        this->requestListMsg();
        
    }else if (message->messageID == SCENSE_CLIENT_BOOK_BookGiftResp)
    {
        this->isSort=false;
        NoticeManager::getInstance()->showNotice("送礼成功",NoticeManager::COLOR_GREEN);
        this->requestListMsg();
    }else if (message->messageID == SCENSE_CLIENT_BOOK_BookInvite2Resp)
    {

        MarketFindResultData* data=new MarketFindResultData();
        data->heroId=message->byteStream->getInt();
        data->dictId=message->byteStream->getInt();
        data->name=message->byteStream->getUTF8();
        data->heroForce=message->byteStream->getByte();
        data->level=message->byteStream->getInt();
        data->leaderShip=message->byteStream->getInt();
        data->prestige=message->byteStream->getInt();
        data->combatPower=message->byteStream->getInt();
        
        MarketGetHeroLayer* getHeroLayer = MarketGetHeroLayer::create(data,NULL);
        getHeroLayer->setAnchorPoint(Point::ZERO);
        Scene* scene = Director::getInstance()->getRunningScene();
        getHeroLayer->setPositionX(VisibleRect::center().x-getHeroLayer->getContentSize().width/2);
        getHeroLayer->setPositionY(VisibleRect::center().y - getHeroLayer->getContentSize().height/2);
        scene->addChild(getHeroLayer,SCENE_POPLAYER_ZORDER);
        
        this->requestListMsg();
        broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumBook));
    }
}
void GeneralsLetter_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BOOK_BookPage2Resp).c_str(), CC_CALLBACK_1(GeneralsLetter_Layer::onMsgProcess, this));
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BOOK_BookDeliverResp).c_str(), CC_CALLBACK_1(GeneralsLetter_Layer::onMsgProcess, this));
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BOOK_BookGiftResp).c_str(), CC_CALLBACK_1(GeneralsLetter_Layer::onMsgProcess, this));
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BOOK_BookInvite2Resp).c_str(), CC_CALLBACK_1(GeneralsLetter_Layer::onMsgProcess, this));
}
void GeneralsLetter_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

//状态排序
//bool sortOnLetterId(LetterData* n1, LetterData* n2)
//{
//    return n1->letterHeroId > n2->letterHeroId;
//}
//bool sortOnLetterQuality(LetterData* n1, LetterData* n2)//正序(从大到小)
//{
//    return n1->letterHeroQuality > n2->letterHeroQuality;
//}
//bool sortOnLetterPackOrder(LetterData* n1, LetterData* n2)
//{
//    return n1->letterBackPackOrder < n2->letterBackPackOrder;
//}
//void GeneralsLetter_Layer::sortList(string name)
//{
//    stable_sort(letterList->begin(), letterList->end(),sortOnLetterPackOrder);
//    stable_sort(letterList->begin(), letterList->end(),sortOnLetterId);
//    stable_sort(letterList->begin(), letterList->end(),sortOnLetterQuality);
//    this->initTableView();
//
//}
