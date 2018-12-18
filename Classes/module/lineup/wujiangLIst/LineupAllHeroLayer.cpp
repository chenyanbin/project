//
//  LineupAllHeroLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/8.
//
//

#include "LineupAllHeroLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../message/Decoding/lineup/lineupHeroListMsg/LineupHeroListMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../message/Decoding/lineup/LineupSetRespMsg/LineupSetRespMsg.h"
#include "../../../message/Decoding/lineup/LineupDownMsg/LineupDownMsg.h"
#include "../LineupLayer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../lineup_data/LineupListDataManger.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../generals/generalsCard/GeneralsCard_Layer.h"
#include "../../generals/data/CardDataManager.h"
#include "../../../common/Dialog/Dialog.h"
LineupAllHeroLayer::LineupAllHeroLayer()
:listBg(NULL)
,TAG_TABLEVIEW(3)
,_tableView(NULL)
,m_lineupNo(1)
,m_fromHeroType(1)
,m_fromLocation(1)
,m_heroid(0)
,m_leader(0)
,isMoveing(false)
,isDownPoint(Point::ZERO)
,m_combatpower(0)
,m_oldCombatPower(0)
{
    heroList=new Vector<LineupListData*>();

}

LineupAllHeroLayer::~LineupAllHeroLayer()
{
    LineupListDataManger::getInstance()->destroyInstance();
    heroList->clear();
    CC_SAFE_DELETE(heroList);
}

bool LineupAllHeroLayer::init(int _lineupId, int _fromHeroType, int _fromLocation, int leader)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        
        m_lineupNo = _lineupId;
        m_fromHeroType = _fromHeroType;
        m_fromLocation = _fromLocation;
        m_leader = leader;
        
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG,Point::ZERO,this);
        setallBackGround();
        requestListMsg(m_lineupNo,m_fromHeroType,m_fromLocation);
        bref = true;
    } while (false);
    return bref;
}

LineupAllHeroLayer* LineupAllHeroLayer::create(int _lineupId, int _fromHeroType, int _fromLocation, int leader)
{
    LineupAllHeroLayer* list = new LineupAllHeroLayer();
    if(list && list->init(_lineupId,_fromHeroType,_fromLocation,leader))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void LineupAllHeroLayer::show(int _lineupId, int _fromHeroType, int _fromLocation, int leader)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    LineupAllHeroLayer* layer = LineupAllHeroLayer::create(_lineupId,_fromHeroType,_fromLocation,leader);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void LineupAllHeroLayer::onEnter()
{
    BaseLayer::onEnter();
}
void LineupAllHeroLayer::onExit()
{
    BaseLayer::onExit();
}
void LineupAllHeroLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    isClickClose = GlobalInfo::getInstance()->isGuiding ? false : true;
}
void LineupAllHeroLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumQualityFirstTag);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumZhaoyunGo);
}

void LineupAllHeroLayer::setallBackGround()
{
   
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
//    listBg = (Sprite*)this->getChildByTag(TAG_BG);
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1);
    this->setContentSize(listBg->getContentSize());
    

    
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listBg2);
    listBg2->setPosition(listBg->getPositionX()+15*sx,listBg->getPositionY()+450*sx);
    this->addChild(listBg2,3);
    
    const char* pathList[3] = {IMG_PUBLIC_LABEL_LEVEL,IMG_PUBLIC_LABEL_QUALITY,IMG_PUBLIC_LABEL_PRESTIGE};
    const char* pathList2[3] = {IMG_PUBLIC_LABEL_LEVEL1,IMG_PUBLIC_LABEL_QUALITY1,IMG_PUBLIC_LABEL_PRESTIGE1};
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(LineupAllHeroLayer::onTopComboBoxClick, this));
    for (int i = 0; i<3; i++) {
//        boxBtn->addBtn(pathList[i], pathList2[i], "");
        boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathList[i], pathList2[i]);
    }
    boxBtn->setAnchorPoint(Point::ZERO);
    boxBtn->setPosition(10*sx,(listBg2->getContentSize().height/sx-boxBtn->getContentSize().height)/2+5*sx);
    boxBtn->getButtonAt(0)->selected();
    listBg2->addChild(boxBtn,3);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumQualityFirstTag, boxBtn->getButtonAt(1));
    
    //总领导力
    Sprite* lingdaoliBg = Sprite::create(IMG_LINEUP_LINGDAOLIBG);
    lingdaoliBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(lingdaoliBg);
    lingdaoliBg->setPosition(listBg->getContentSize().width-lingdaoliBg->getContentSize().width-70*sx ,listBg->getPositionY()+485*sx);
    this->addChild(lingdaoliBg,5);
    string lingdaoStr=PublicShowUI::numberToString(m_leader);
    Label* lingdaoLabel = PublicShowUI::getLabel(lingdaoStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),24,false,false);
    lingdaoLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(lingdaoLabel);
    lingdaoLabel->setPosition(listBg->getContentSize().width-lingdaoliBg->getContentSize().width+30*sx ,listBg->getPositionY()+485*sx);
    this->addChild(lingdaoLabel,5,111);
    
    //按钮
//    const char* pathList[3] = {IMG_PUBLIC_LABEL_LEVE2_FIRST,IMG_PUBLIC_LABEL_MASS2_FIRST,IMG_PUBLIC_LABEL_PRESTIGE2_FIRST};
//    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 16, CC_CALLBACK_1(LineupAllHeroLayer::onTopComboBoxClick, this));
//    for (int i = 0; i<3; i++) {
//        boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_FRIST1, IMG_PUBLIC_COMBOBOX_FRIST2, pathList[i]);
//    }
//    boxBtn->setAnchorPoint(Point::ZERO);

//    PublicShowUI::setTargetScale(boxBtn);
//    boxBtn->setPosition(10*sx  ,listBg->getContentSize().height);
//    boxBtn->getButtonAt(0)->selected();
//    this->addChild(boxBtn,1);
    
}

void LineupAllHeroLayer::createTableView()
{

    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumZhaoyunGo);
    if(_tableView)
    {
        _tableView->reloadData();
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3-100*sx;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(32 * sx + listBg->getPositionX() ,50 * sx + listBg->getPositionY());
    _tableView->reloadData();
    this->addChild(_tableView,30,TAG_TABLEVIEW);

}


Sprite* LineupAllHeroLayer::singleList(ssize_t idx)
{
    if(idx >= heroList->size())
    {
        return NULL;
    }
    float sx = 1;//GlobalInfo::getInstance()->screenScaleX;

    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);


    LineupListData* data = heroList->at(idx);
    
    DictHero* dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
    if (dictHero) {
        UserHeadLayer* userHead=UserHeadLayer::create(dictHero->resource.c_str(),data->quality);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setHeadInfo(data->level, data->prestige);
        userHead->setPosition(28 * sx, 28 * sx);
        layerBg->addChild(userHead,2,idx);
        userHead->addTouchBegainCallBack(this, callfuncN_selector(LineupAllHeroLayer::onUserClick));
    }
    
    // 上阵按钮
    if (data->op == 1)//上阵
    {
     
//        Sprite* zhenrongBg = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
        TouchSprite* zhenrongBg = TouchSprite::createWithPic(IMG_PUBLIC_BUTTON_TWO_ORANGE,this,callfuncN_selector(LineupAllHeroLayer::onshangzhenClick));
        zhenrongBg->setAnchorPoint(Point::ZERO);
        zhenrongBg->isButtonMode = true;
         zhenrongBg->setSwallowTouches(false);
        zhenrongBg->setPosition(layerBg->getContentSize().width-zhenrongBg->getContentSize().width - 10 * sx,20 * sx);
        layerBg->addChild(zhenrongBg,3,idx);

        Sprite *shangzhen = Sprite::create(IMG_LINEUP_SHANGZHEN1);
        shangzhen->setAnchorPoint(Point::ZERO);
    
        shangzhen->setPosition(Point::ZERO);
        zhenrongBg->addChild(shangzhen,2,idx);
        if(GlobalInfo::getInstance()->isDebug && !GuideButtonManager::getInstance()->getButton(DictNewGuideEventEnumZhaoyunGo))
        {
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumZhaoyunGo, zhenrongBg);
        }
        if(data->heroName == "文丑")
        {
            GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumZhaoyunGo);
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumZhaoyunGo, zhenrongBg);
        }
       
    }
    else if (data->op  == 2)//下阵，卸下
    {
        Sprite* zhenrongBg = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
        zhenrongBg->setAnchorPoint(Point::ZERO);
       
        m_oldCombatPower = data->combatPower;//替换的的英雄战力
        TouchSprite *xiazhen = TouchSprite::createWithPic(IMG_LINEUP_XIAZHEN,this,callfuncN_selector(LineupAllHeroLayer::onxiazhenClick));
        xiazhen->setAnchorPoint(Point::ZERO);
        xiazhen->setSwallowTouches(false);
        xiazhen->setPosition(Point::ZERO);
        zhenrongBg->addChild(xiazhen,2,idx);
        
        zhenrongBg->setPosition(layerBg->getContentSize().width-zhenrongBg->getContentSize().width - 10 * sx,20 * sx);
        layerBg->addChild(zhenrongBg,3);
    }
    else if (data->op  == 3)//已在阵上
    {
        Sprite* zhenrongBg = Sprite::create(IMG_LINEUP_YISHANGZHEN);
        zhenrongBg->setAnchorPoint(Point::ZERO);
   
        zhenrongBg->setPosition(layerBg->getContentSize().width-zhenrongBg->getContentSize().width -3 * sx,layerBg->getContentSize().height-zhenrongBg->getContentSize().height);
        layerBg->addChild(zhenrongBg,3);

    }
    else if (data->op  == 4)//不能上阵（领导力超出）
    {
        Sprite* zhenrongBg = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
        zhenrongBg->setAnchorPoint(Point::ZERO);
        
        TouchSprite *xiazhen = TouchSprite::createWithPic(IMG_LINEUP_SHANGZHEN2,this,callfuncN_selector(LineupAllHeroLayer::onzuiyizhenClick));
        xiazhen->setAnchorPoint(Point::ZERO);
        xiazhen->setSwallowTouches(false);
        xiazhen->setPosition(Point::ZERO);
        zhenrongBg->addChild(xiazhen,2,idx);
        zhenrongBg->setPosition(layerBg->getContentSize().width-zhenrongBg->getContentSize().width - 10 * sx,20 * sx);
        layerBg->addChild(zhenrongBg,3);
    }
    else
    {
        log("erron");
    }
    
    //势力forcef
    char stt[100]="";
  
    if(dictHero)
    {
        int typeNum =  dictHero->attackType == 0 ? 1 : dictHero->attackType;
        sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
        Sprite* force=Sprite::create(stt);
        force->setAnchorPoint(Point::ZERO);
        force->setScale(0.7*sx);
        force->setPosition(150 * sx,(layerBg->getContentSize().height-force->getContentSize().height)+10*sx);
        layerBg->addChild(force,2);

    }
        //名字
    string name= data->heroName;
    Label* nameLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),22,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(200*sx,(layerBg->getContentSize().height-nameLabel->getContentSize().height) - 20*sx );
    layerBg->addChild(nameLabel);
    
    if (m_fromHeroType == 1)
    {
        //列表战力
        Sprite* listMilitary=Sprite::create(IMG_PUBLIC_MILITARY);
        listMilitary->setAnchorPoint(Point::ZERO);
        listMilitary->setPosition(150,70);
        layerBg->addChild(listMilitary,1);
        //列表战力数值
        int combat= data->combatPower;
        string combatStr=PublicShowUI::numberToString(combat);
        Label* combatLabel = PublicShowUI::getLabel(combatStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
        combatLabel->setAnchorPoint(Point::ZERO);
        combatLabel->setPosition(76,2);
        listMilitary->addChild(combatLabel);
    }else if (m_fromHeroType == 2)
    {
        Label* liveLabel = NULL;
        if (m_fromLocation == 1)
        {
            string power = StringUtils::format("%d",data->hp);
            power = "生命：" + power;
            liveLabel = PublicShowUI::getLabel(power.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),24,false,false);
        }
        else if (m_fromLocation == 2)
        {
            string power = StringUtils::format("%d",data->attack);
            power = "攻击：" + power;
            liveLabel = PublicShowUI::getLabel(power.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),24,false,false);
        }
        else if (m_fromLocation == 3)
        {
            string power = StringUtils::format("%d",data->defend);
            power = "防御：" + power;
            liveLabel = PublicShowUI::getLabel(power.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE_YELLOW),24,false,false);
        }
        liveLabel->setAnchorPoint(Point::ZERO);
        liveLabel->setPosition(155*sx,70*sx);
        layerBg->addChild(liveLabel,2);
    }
    
    //列表领导力
    Sprite* listLead=Sprite::create(IMG_PUBLIC_LAYER_LEAD);
    listLead->setAnchorPoint(Point::ZERO);
  
    Sprite* lingdaoliBg = Sprite::create(IMG_LINEUP_STAR);
    lingdaoliBg->setAnchorPoint(Point::ZERO);
 
    lingdaoliBg->setPosition(listLead->getContentSize().width-lingdaoliBg->getContentSize().width+7.5,-5);
    listLead->addChild(lingdaoliBg,2);
    //列表领导力数值
    int leader= data->leadership;
    string leaderStr=PublicShowUI::numberToString(leader);
    Label* leaderLabel = PublicShowUI::getLabel(leaderStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    leaderLabel->setAnchorPoint(Point::ZERO);
    leaderLabel->setPosition(95 ,(listLead->getContentSize().height-leaderLabel->getContentSize().height)/2);
    listLead->addChild(leaderLabel,4);

    listLead->setPosition(150 * sx,20 * sx);
    layerBg->addChild(listLead,1);
    PublicShowUI::setTargetScale(layerBg);
    return layerBg;
}
void LineupAllHeroLayer::onUserClick(Node* pSender)
{
    
    log("列表点击 isMoveing＝%d",isMoveing);
    if(isMoveing)
    {
        return;
    }
    Node* target = (Node*)pSender;
    int index = target->getTag();
    log("%d",index);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=(_size.height*3-100*GlobalInfo::getInstance()->screenScaleX);
    _size.width=_size.width+10*GlobalInfo::getInstance()->screenScaleX;
    isDownPoint.x = isDownPoint.x;
    isDownPoint.y = isDownPoint.y;
    log("%f,%f,%f,%f",_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_size.width,_size.height);
    log("%f,%f",isDownPoint.x,isDownPoint.y);
    log("%f,%f",GlobalInfo::getInstance()->screenScaleX,GlobalInfo::getInstance()->screenScaleY);
    Rect bb=Rect(_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_size.width, _size.height);
    if (bb.containsPoint(isDownPoint)) {
        CardPropertyData* data = new CardPropertyData;
        data->heroId = heroList->at(pSender->getTag())->heroId;
        data->heroDictId= heroList->at(pSender->getTag())->heroDictId;
        CardDataManager::getInstance()->setPresentData(data);
        GeneralsCard_Layer::show(SCENE_TAG_LINEUP, DictFunctionEnumEquip);
    }

    
//    CardPropertyData* data = new CardPropertyData;
//    data->heroId = heroList->at(pSender->getTag())->heroId;
//    data->heroDictId= heroList->at(pSender->getTag())->heroDictId;
//    CardDataManager::getInstance()->setPresentData(data);
//    GeneralsCard_Layer::show(SCENE_TAG_LINEUP, DictFunctionEnumEquip);
}

void LineupAllHeroLayer::onshangzhenClick(Node* psender)//上阵
{
    m_heroid = heroList->at(psender->getTag())->heroId;
    m_combatpower =heroList->at(psender->getTag())->combatPower;
    requestLineupSetMsg(m_lineupNo,m_fromHeroType,m_fromLocation,m_heroid);
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumZhaoyunGo);
}
void LineupAllHeroLayer::onxiazhenClick(Node* psender)//下阵
{

    m_heroid = heroList->at(psender->getTag())->heroId;
    requestLineupDownMsg(m_lineupNo,m_heroid);
}
void LineupAllHeroLayer::onzuiyizhenClick(Node* psender)//最已阵/不能上阵
{
    NoticeManager::getInstance()->showNotice("总领导力超出，不能上阵");
}
void LineupAllHeroLayer::onTopComboBoxClick(Ref* psender)
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

    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumQualityFirstTag);

}

TableViewCell* LineupAllHeroLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
        list->setPositionX(420 * GlobalInfo::getInstance()->screenScaleX * i);
        cell->addChild(list);
        cell->setContentSize(list->getContentSize());
        cell->setTag(tag);
    }
    
    return cell;
}

//列表大小
Size LineupAllHeroLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    PublicShowUI::setTargetScale(temp);
    cellSize.height = temp->getContentSize().height+3.5;
    cellSize.width = temp->getContentSize().width *2+10;
    return cellSize;
}
//获取view的长度
ssize_t LineupAllHeroLayer::numberOfCellsInTableView(TableView *table)
{
    ssize_t  now_count =ceil(double(heroList->size()) / 2);
    return now_count;
}
//点击cell事件
void LineupAllHeroLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
}

void LineupAllHeroLayer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
bool LineupAllHeroLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void LineupAllHeroLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
    
    
}
void LineupAllHeroLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
    BaseLayer::onTouchEnded(touch, unused_event);
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void LineupAllHeroLayer::requestListMsg(int _lineupId,int _fromHeroType,int _fromLocation)//发送武将列表消息
{
    LineupHeroListMsg* msg = new LineupHeroListMsg(_lineupId, _fromHeroType, _fromLocation);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LineupAllHeroLayer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    LineupListDataManger::getInstance()->clearheroList();
    if(message->messageID == SCENSE_CLIENT_LINEUP_LineupHeroSelPageResp)
    {
        short heroNum=message->byteStream->getShort();
        for (int i =0; i<heroNum; i++) {
            LineupListData* data=new LineupListData();
            data->autorelease();
            data->heroId=message->byteStream->getInt();
            data->heroDictId=message->byteStream->getInt();
            data->heroName=message->byteStream->getUTF8();
            data->force = message->byteStream->getByte();
            data->prestige=message->byteStream->getShort();
            data->leadership=message->byteStream->getInt();
            data->combatPower=message->byteStream->getInt();
            data->hp = message->byteStream->getInt();
            data->attack = message->byteStream->getInt();
            data->defend = message->byteStream->getInt();
            data->level=message->byteStream->getInt();
            data->quality=message->byteStream->getByte();
            data->op = message->byteStream->getByte();

            if (data->op==2) {
                data->sort=1;
            }
            LineupListDataManger::getInstance()->addData(data);
            heroList->pushBack(data);
            data->retain();
        }
        
        createTableView();
        sortList("level");
        NewPlayerGuild::getInstance()->showNowGuide();
      
   
    }
}

void LineupAllHeroLayer::requestLineupSetMsg(int lineupNo,int heroType, int location, int heroId)//发送选择英雄上阵消息
{
    log("==================requestLin   eupSetMsg===============");
    LineupSetRespMsg* msg = new LineupSetRespMsg(lineupNo,heroType,location,heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LineupAllHeroLayer::onUpLineupMsgProcess(EventCustom* msg)//接收上阵消息
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_LINEUP_LineupSetResp)
    {
        if (message->state) {
            LineupLayer::show(SCENE_TAG_MAINUI,m_lineupNo,m_combatpower-m_oldCombatPower);
        }
    }
}

void LineupAllHeroLayer::requestLineupDownMsg(int lineupNo, int heroId)//发送下阵消息
{
    Dialog::showServerLoading();
    LineupDownMsg* msg = new LineupDownMsg(lineupNo,heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LineupAllHeroLayer::onDownLineupMsgProcess(EventCustom* msg)//接收下阵消息
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_LINEUP_LineupDownResp)
    {
        if (message->state) {
            LineupLayer::show(SCENE_TAG_MAINUI,m_lineupNo,0);
        }
    }
}

void LineupAllHeroLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupHeroSelPageResp).c_str(), CC_CALLBACK_1(LineupAllHeroLayer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupSetResp).c_str(), CC_CALLBACK_1(LineupAllHeroLayer::onUpLineupMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupDownResp).c_str(), CC_CALLBACK_1(LineupAllHeroLayer::onDownLineupMsgProcess, this));
}
void LineupAllHeroLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
//状态排序
bool sortOnChooseCardPrestige(LineupListData* n1, LineupListData* n2)
{
    return n1->prestige > n2->prestige;
}
bool sortOnChooseCardQualityAscend(LineupListData* n1, LineupListData* n2)//倒序(从大到小)
{
    return n1->quality > n2->quality;
}
bool sortOnChooseCardQualityDescend(LineupListData* n1, LineupListData* n2)//倒序(从小到大)
{
    return n1->quality < n2->quality;
}
bool sortLineupLevel(LineupListData* n1, LineupListData* n2)
{
    return n1->level > n2->level;
}
bool sortOnChooseCardstate(LineupListData* n1,  LineupListData* n2)
{
    return n1->sort > n2->sort;
}
void LineupAllHeroLayer::sortList(string name)
{
    ssize_t len = heroList->size();
    if (len<=1) {
        return;
    }
    if(name == "prestige" )
    {
        sort(heroList->begin(), heroList->end(),sortOnChooseCardstate);
        int tempNum=0;
        ssize_t len = heroList->size();
        for (int i=0;i<len;i++) {
            if (heroList->at(i)->op==2) {
                tempNum=i+1;
                log("i=========================%d",tempNum);
            }
        }
        sort(heroList->find(heroList->at(tempNum)),heroList->end(),sortOnChooseCardPrestige);
//        sort(heroList->begin(),heroList->find(heroList->at(tempNum)),sortOnChooseCardPrestige);
        
    }
    else if(name == "quality")
    {
        sort(heroList->begin(), heroList->end(),sortOnChooseCardstate);
        int tempNum=0;
        ssize_t len = heroList->size();
        for (int i=0;i<len;i++) {
            if (heroList->at(i)->op==2) {
                tempNum=i+1;
                log("i=========================%d",tempNum);
            }
        }
        sort(heroList->find(heroList->at(tempNum)),heroList->end(),sortOnChooseCardQualityAscend);
//        sort(heroList->begin(), heroList->end(),sortOnChooseCardQualityAscend);
    }
    else if(name == "level" )
    {
        sort(heroList->begin(), heroList->end(),sortOnChooseCardstate);
        int tempNum=0;
        ssize_t len = heroList->size();
        for (int i=0;i<len;i++) {
            if (heroList->at(i)->op==2) {
                tempNum=i+1;
                log("i=========================%d",tempNum);
            }
        }
        sort(heroList->find(heroList->at(tempNum)),heroList->end(),sortLineupLevel);
        
    }else if(name=="0")
    {
        return;
    }

    this->createTableView();
    
}

