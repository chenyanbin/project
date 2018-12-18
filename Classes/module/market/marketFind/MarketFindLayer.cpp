//
//  MarketFindLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/3.
//
//

#include "MarketFindLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../protocol/Protocal.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/market/marketFindMsg/MarketFindPageMsg.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../message/Decoding/market/findExtendMsg/MarketFindExtendMsg.h"
#include "MarketGetEquipLayer.h"
#include "../marketData/MarketFindResultData.h"
#include "../marketData/MarketFindResultDataManager.h"
#include "../../../message/Decoding/market/findResultMsg/FindResultMsg.h"
#include "../marketData/marketFindDataManager.h"
#include "FindBuyMilitaryLayer.h"
#include "FindAccelerationLayer.h"
#include "FindExtendLayer.h"
#include "FindCellLayer.h"
#include "../../../avatar/hero/Hero.h"
#include "../marketData/StartFinddataManger.h"
#include "FinderHeroListLayer.h"

#include "../../../common/noticeManager/NoticeManager.h"
#include "MarketGetHeroLayer.h"
#include "MarketGetEquipLayer.h"
#include "../marketData/MarketFindResultDataManager.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../data/BaseTypeData.h"
MarketFindLayer::MarketFindLayer()
:listBg(NULL)
,_tableView(NULL)
,m_nextExtentGold(0)
,TAG_TABLEVIEW(2)
//,data(NULL)
,m_idx(1)
,popUpLoading(NULL)
,m_mark(0)
,m_jungongCount(0)
,m_xunfanglinCount(0)
,TAG_JUNGONG(10)
,TAG_XUNFANGLING(11)
,m_minHonor(0)
,TAG_JUNGONGPIC(12)
,TAG_XUNFANGWORD(13)
{

}

MarketFindLayer::~MarketFindLayer()
{
    data = NULL;
}

bool MarketFindLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        setBackGround();
        bref = true;
    } while (false);
    return bref;
}

MarketFindLayer* MarketFindLayer::create()
{
    MarketFindLayer* list = new MarketFindLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketFindLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketFindLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketFindLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestfindListMsg();
}
void MarketFindLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    clearResourcePerson();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumLookForTheGeneralsHead);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSearchExtensionButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumLookForTheStart);
}

void MarketFindLayer::setBackGround()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1);
    this->setContentSize(listBg->getContentSize());
    
//    Sprite* xunfangWord = Sprite::create(IMG_MARKET_MARKETFIND_XUNFANGWORD);
//    xunfangWord->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(xunfangWord);
//    xunfangWord->setPosition(50*sx,listBg->getContentSize().height-xunfangWord->getContentSize().height-20*sx);
//    this->addChild(xunfangWord,2,6);
//    
//    Sprite* grayxunfangWord = Sprite::create(IMG_MARKET_MARKETFIND_GRAYXUNFANGWORD);
//    grayxunfangWord->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(grayxunfangWord);
//    grayxunfangWord->setOpacity(70);
//    grayxunfangWord->setPosition(48*sx,listBg->getContentSize().height-grayxunfangWord->getContentSize().height-15*sx);
//    this->addChild(grayxunfangWord,2,5);
    
    //标题背景
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listBg2);
    listBg2->setPosition(listBg->getPositionX()+15*sx,listBg->getPositionY()+450*sx);
    this->addChild(listBg2,1);
    
    //军工
//    Sprite* jungong = Sprite::create(IMG_ICON_JUNGONG);
//    jungong->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(jungong);
//    jungong->setScale(0.5*sx);
//    jungong->setPosition(listBg->getContentSize().width/2-jungong->getContentSize().width/2-300*sx,listBg->getContentSize().height-jungong->getContentSize().height+40*sx);
//    this->addChild(jungong,2);
//    
//    string jungongStr="铜钱:";
//    Label* jungongLabel= PublicShowUI::getLabel(jungongStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
//    jungongLabel->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(jungongLabel);
//    this->addChild(jungongLabel,5,TAG_JUNGONGPIC);
//    jungongLabel->setPosition(jungong->getPositionX()+60*sx,jungong->getPositionY()+20*sx);

    
    //寻访令
    Sprite* xunfangToken = Sprite::create(IMG_ICON_XUNFANGLIN);
    xunfangToken->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(xunfangToken);
    xunfangToken->setScale(0.5*sx);
    xunfangToken->setPosition(listBg->getContentSize().width/2-xunfangToken->getContentSize().width/2-300*sx,listBg->getContentSize().height-xunfangToken->getContentSize().height+40*sx);
    this->addChild(xunfangToken,2,7);
    
    string tokenStr="寻访令:";
    Label* tokenLabel= PublicShowUI::getLabel(tokenStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    tokenLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(tokenLabel);
    this->addChild(tokenLabel,5,TAG_XUNFANGWORD);
    tokenLabel->setPosition(xunfangToken->getPositionX()+60*sx,xunfangToken->getPositionY()+20*sx);
    
}
//铜钱数量/寻访令数量
void MarketFindLayer::setJungong()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    
//    //铜钱
//    Label* jungongWord = (Label*)this->getChildByTag(TAG_JUNGONGPIC);
//    string jungongStr=PublicShowUI::numberToString(m_jungongCount);
//    Label* jungongLabel = (Label*)this->getChildByTag(TAG_JUNGONG);
//    if (jungongLabel) {
//        jungongLabel->setString(jungongStr);
//    }else{
//        jungongLabel= PublicShowUI::getLabel(jungongStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
//        jungongLabel->setAnchorPoint(Point::ZERO);
//        PublicShowUI::setTargetScale(jungongLabel);
//        this->addChild(jungongLabel,6,TAG_JUNGONG);
//    }
//    jungongLabel->setPosition(jungongWord->getPositionX()+jungongWord->getContentSize().width,jungongWord->getPositionY());
    
    //寻访令
    Label* xunfangWord = (Label*)this->getChildByTag(TAG_XUNFANGWORD);
    string tokenStr=PublicShowUI::numberToString(m_xunfanglinCount);
    Label* tokenLabel = (Label*)this->getChildByTag(TAG_XUNFANGLING);
    if (tokenLabel) {
        tokenLabel->setString(tokenStr);
    }else{
        tokenLabel= PublicShowUI::getLabel(tokenStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
        tokenLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(tokenLabel);
        this->addChild(tokenLabel,6,TAG_XUNFANGLING);
    }
    tokenLabel->setPosition(xunfangWord->getPositionX()+xunfangWord->getContentSize().width,xunfangWord->getPositionY());
    
}
void MarketFindLayer::createTableView()
{
   
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3 - 20* GlobalInfo::getInstance()->screenScaleX;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(35,60);
    
    this->addChild(_tableView,2,TAG_TABLEVIEW);
}
Sprite* MarketFindLayer::singleList(ssize_t idx)
{
    if (idx < marketFindDataManager::getInstance()->findList->size())
    {
        MarketFindData* data = marketFindDataManager::getInstance()->findList->at(idx);
        
        Sprite*layerBg = Sprite::create(IMG_TASK_ITEMBG);
        layerBg->setAnchorPoint(Point::ZERO);
        //头像
        TouchSprite* boxbg = TouchSprite::createWithPic(IMG_PUBLIC_HEROHEADBG, this, callfuncN_selector(MarketFindLayer::onHeroHeadClick));
        boxbg->setAnchorPoint(Point::ZERO);
        boxbg->setPosition(33,10);
        layerBg->addChild(boxbg,1,idx);
        
        Label* xunfangLabel = PublicShowUI::getLabel("选择武将",PublicShowUI::getColor3b(COLOR_GREEN_BLUE),32,false,false);
        xunfangLabel->setAnchorPoint(Point::ZERO);
        xunfangLabel->setMaxLineWidth(80);
        xunfangLabel->setPosition(25,20);
        boxbg->addChild(xunfangLabel,2);
        if(idx == 0)
        {
            GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumLookForTheGeneralsHead);
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumLookForTheGeneralsHead, boxbg);
        }
        
        DictHero* dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
        if (dictHero) {
            UserHeadLayer* userHead=UserHeadLayer::create(dictHero->resource.c_str(),data->heroQuality);
            userHead->setHeadInfo(data->heroLevel, data->heroPrestige);
            userHead->setPosition(4, 4);
            boxbg->addChild(userHead,3,idx);
         
        }
        if (data->status == 1)//开始寻访
        {
            Sprite* map1=Sprite::create(IMG_MARKET_MARKETFIND_MAP);
            map1->setAnchorPoint(Point::ZERO);
            map1->setPosition(170,-3);
            layerBg->addChild(map1,1);
            
            Sprite* unBegin=Sprite::create(IMG_MARKET_MARKETFIND_UNBEGIN);
            unBegin->setAnchorPoint(Point::ZERO);
            unBegin->setPosition(0,100);
            map1->addChild(unBegin,2);
            
            const char* beginpath = PublicShowUI::getResImgPath(IMG_MARKET_MARKETFIND_XUNFANG, PublicShowUI::numberToString(3).c_str());

            TouchSprite* beginxunfangSpr = TouchSprite::createWithPic(beginpath, this, callfuncN_selector(MarketFindLayer::onClick));
            beginxunfangSpr->setAnchorPoint(Point::ZERO);
            beginxunfangSpr->setPosition(470 + map1->getPositionX(),25);
            layerBg->addChild(beginxunfangSpr,2,idx);
            if( idx == 0)
            {
                GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumLookForTheStart);
                GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumLookForTheStart, beginxunfangSpr);
            }
        }
        else if (data->status == 2)//正在寻访
        {
            FindCellLayer* map2 = FindCellLayer::create(idx);
            map2->setAnchorPoint(Point::ZERO);
            map2->setPosition(170, -3);
            layerBg->addChild(map2,1,idx);
        }
        else if (data->status == 3 )//寻访完成
        {
            Sprite* map3=Sprite::create(IMG_MARKET_MARKETFIND_MAP);
            map3->setAnchorPoint(Point::ZERO);
            map3->setPosition(170,-3);
            layerBg->addChild(map3,1);
            
            Sprite* completeSpr=Sprite::create(IMG_MARKET_MARKETFIND_XUUNFANGWANCHENGSPR);
            completeSpr->setAnchorPoint(Point::ZERO);
            completeSpr->setPosition(200,60);
            map3->addChild(completeSpr,2);
            
            const char* jiesupath = PublicShowUI::getResImgPath(IMG_MARKET_MARKETFIND_XUNFANG, PublicShowUI::numberToString(1).c_str());
            Button* xunfangjiesuSpr=Button::create(jiesupath, "", CC_CALLBACK_1(MarketFindLayer::onjieguoClick, this));
            xunfangjiesuSpr->setAnchorPoint(Point::ZERO);
            xunfangjiesuSpr->setPosition(470,25);
            map3->addChild(xunfangjiesuSpr,2,idx);
        }
        return layerBg;

    }else{
        Sprite* unlayerBg = Sprite::create(IMG_TASK_ITEMBG);
        unlayerBg->setAnchorPoint(Point::ZERO);
        Button* kuozhanSpr = Button::create(IMG_MARKET_MARKETFIND_KUOZHANSPR, "", CC_CALLBACK_1(MarketFindLayer::onkuozhanClick, this));
        kuozhanSpr->setAnchorPoint(Point::ZERO);
        kuozhanSpr->setPosition(330,50);
        unlayerBg->addChild(kuozhanSpr);
       
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSearchExtensionButton, kuozhanSpr);
        
        return unlayerBg;
    }
}
    
//开始寻访
void MarketFindLayer::onClick(Node* psender)
{
    
     Node* target = (Node*)psender;
    log("%d",target->getTag());//tagget上传到服务器
    if (marketFindDataManager::getInstance()->findList->at(target->getTag())->heroDictId == 0) {
        NoticeManager::getInstance()->showNotice("请先选择武将");
        return;
    }
    else if (m_xunfanglinCount<=0)
    {
         NoticeManager::getInstance()->showNotice("寻访令不足");
        return;
    }
    else
    {

        FindBuyMilitaryLayer::show(target->getTag(),m_minHonor,m_jungongCount);
    }
    //不能放在 FindBuyMilitaryLayer::show 的前面
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumLookForTheStart);
    
}
//查看结果
void MarketFindLayer::onjieguoClick(Ref* psender)
{
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    requestDumpMsg(marketFindDataManager::getInstance()->findList->at(target->getTag())->findId);
    m_idx =target->getTag();
}
//领地扩展
void MarketFindLayer::onkuozhanClick(Ref* psender)
{
    if(m_nextExtentGold == -1)
    {
        NoticeManager::getInstance()->showNotice("已是最大领地，不能再扩展!");
    }else{
        FindExtendLayer::show(m_nextExtentGold);
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumSearchExtensionButton);
}
//选择寻访者
void MarketFindLayer::onHeroHeadClick(Node* psender)
{
     NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumLookForTheGeneralsHead);
    if (marketFindDataManager::getInstance()->findList->at(psender->getTag())->status == 1) {
        FinderHeroListLayer::show(psender->getTag());
        log("%d",psender->getTag());
    }else{
        NoticeManager::getInstance()->showNotice("武将寻访中!");
    }
   
}
TableViewCell* MarketFindLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Sprite* list=singleList(idx);
    PublicShowUI::setTargetScale(list);
    list->setAnchorPoint(Point::ZERO);
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    return cell;
}
//列表大小
Size MarketFindLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_TASK_ITEMBG);
    PublicShowUI::setTargetScale(temp);
    cellSize.height = temp->getContentSize().height+5;
    cellSize.width = temp->getContentSize().width ;
    return cellSize;
}
//获取view的长度
ssize_t MarketFindLayer::numberOfCellsInTableView(TableView *table)
{
    return marketFindDataManager::getInstance()->findList->size()+1;
}
//点击cell事件
void MarketFindLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
    log("%d",cell->getTag());
}

void MarketFindLayer::loadPerson()
{
    log("1111111111111111loadPerson");
    popUpLoading = Dialog::showLoading();
    bool hashero = false;
    for (int i = 0; i < marketFindDataManager::getInstance()->findList->size(); i++) {
        if (marketFindDataManager::getInstance()->findList->at(i)->status == 2) {
            int dict = marketFindDataManager::getInstance()->findList->at(i)->heroDictId;
            DictHero* dictHero = DictHeroManager::getInstance()->getData(dict);
            if(dictHero)
            {
               
                AnimationData* animationData = ArmatureDataManager::getInstance()->getAnimationData(dictHero->resource);
                if(!animationData)
                {
                    m_mark = 1;
                    const char* path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
                    log("1111111111111111path=%s",path);
                    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(MarketFindLayer::onDataLoaded));
                    hashero = true;
                    
                }
                
            }
        }
    }
    if (!hashero) {
        m_mark = 0;
        log("2222222loadPerson no person");
        onDataLoaded(1);
        return;
    }
}
void MarketFindLayer::onDataLoaded(float percent)
{
    log("perdent==%f",percent);
    if(popUpLoading && popUpLoading->getParent())
    {
        popUpLoading->setProgressPercent(percent * 100);
    }
    if(percent >= 1)
    {
        Dialog::hideLoading();
        popUpLoading = NULL;
        broadMsg(CUSTOM_MARKER_HEROLOADED,__Integer::create(m_mark));
    }
}

void MarketFindLayer::clearResourcePerson()//清除人物资源
{
    const char* path = NULL;
    for (int i = 0; i < marketFindDataManager::getInstance()->findList->size(); i++)
    {
        if (marketFindDataManager::getInstance()->findList->at(i)->status == 2)
        {
            int dict = marketFindDataManager::getInstance()->findList->at(i)->heroDictId;
            DictHero* dictHero = DictHeroManager::getInstance()->getData(dict);
            if(dictHero)
            {
                path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
                ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
            }
        }
    }
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    ArmatureDataManager::destroyInstance();
}

void MarketFindLayer::onSureFindMsgProcess(EventCustom* msg)//确认开始寻访
{
    int findId = StartFinddataManger::getInstance()->getfindIdData();
    int  remainingTimes = StartFinddataManger::getInstance()->getRemainingTimesData();
    log("%d",(int)marketFindDataManager::getInstance()->findList->size());
    marketFindDataManager::getInstance()->findList->at(findId-1)->status = 2;
    marketFindDataManager::getInstance()->findList->at(findId-1)->remainingTime = remainingTimes;
    
    int glod = StartFinddataManger::getInstance()->getjiasugoldData();
    marketFindDataManager::getInstance()->findList->at(findId-1)->fastGold = glod;
    _tableView->updateCellAtIndex(findId-1);
    
    m_xunfanglinCount = StartFinddataManger::getInstance()->getxunfanglingData();
    m_jungongCount = StartFinddataManger::getInstance()->getjungongData();
    setJungong();
    loadPerson();
   
}

void MarketFindLayer::ontSureSpeedMsgProcess(EventCustom* msg)//确认加速寻访
{
    __Integer* inter = (__Integer*)msg->getUserData();
    int idx = inter->getValue();
    marketFindDataManager::getInstance()->findList->at(idx)->status = 3;
    _tableView->updateCellAtIndex(idx);
}

void MarketFindLayer::ontlingdikuozhanProcess(EventCustom* msg)//扩展成功
{
    
    __Integer* inter = (__Integer*)msg->getUserData();
    m_nextExtentGold = inter->getValue();
     _tableView->insertCellAtIndex(marketFindDataManager::getInstance()->findList->size());
    MarketFindData* data=new MarketFindData();
    int findlistsize = marketFindDataManager::getInstance()->findList->size();
    if (marketFindDataManager::getInstance()->findList->size() == 0) {
        data->findId = 1;
    }else{
        data->findId = marketFindDataManager::getInstance()->findList->at(findlistsize-1)->findId+1;
    }
    data->status = 1;
    data->heroId = 0;
    data->heroDictId = 0;
    data->heroQuality = 0;
    data->heroLevel = 0;
    data->heroPrestige = 0;
    data->remainingTime = 0;
    data->fastGold = 0;
    marketFindDataManager::getInstance()->findList->pushBack(data);
    _tableView->insertCellAtIndex(findlistsize);
    if(findlistsize<3)
    {
        _tableView->reloadData();
    }else{
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
    }
    NoticeManager::getInstance()->showNotice("扩展成功！");
}


/******------------------------------------访问服务器------------------------------*************/
void MarketFindLayer::requestfindListMsg()//请求列表信息
{
    Dialog::showServerLoading();
    MarketFindPageMsg* msg = new MarketFindPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketFindLayer::onMsgProcess(EventCustom* msg)//获取列表信息返回值
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    marketFindDataManager::getInstance()->clearfindList();
    if(message->messageID == SCENSE_CLIENT_FIND_FindPageResp)
    {
      
        if(message->state)//返回成功
        {
            m_xunfanglinCount = message->byteStream->getInt();
           
            m_jungongCount = message->byteStream->getInt();

            GlobalInfo::getInstance()->gameRole->expLoit = m_jungongCount;
            m_nextExtentGold = message->byteStream->getInt();
            m_minHonor = message->byteStream->getInt();//最小军工
            int findSize = message->byteStream->getByte();
            for (int i = 0; i < findSize; i ++) {
                MarketFindData* data=new MarketFindData();
                data->autorelease();
                data->findId = message->byteStream->getInt();
                data->status = message->byteStream->getByte();
                data->heroId = message->byteStream->getInt();
                data->heroDictId = message->byteStream->getInt();
                data->heroQuality = message->byteStream->getByte();
                data->heroLevel = message->byteStream->getInt();
                data->heroPrestige = message->byteStream->getInt();
                data->remainingTime = message->byteStream->getInt();
                data->fastGold = message->byteStream->getInt();
                marketFindDataManager::getInstance()->addData(data);
            }
            createTableView();
            setJungong();
            loadPerson();
            
            NewPlayerGuild::getInstance()->showNowGuide();
        }
      
    }
}
void MarketFindLayer::requestDumpMsg(int findId)//请求寻访结果信息
{
    FindResultMsg* msg = new FindResultMsg(findId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketFindLayer::ontDumpMsgProcess(EventCustom* msg)//获取寻访结果信息返回值
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    MarketFindResultDataManager::getInstance()->clearDumpList();
    if(message->messageID == SCENSE_CLIENT_FIND_FindResultResp)
    {
        if(message->state)//返回成功
        {
            
            MarketFindResultData* data = new MarketFindResultData;
            data->autorelease();
            data->itemType = message->byteStream->getByte();
            log("itemType===========%d",data->itemType);
            MarketFindResultDataManager::getInstance()->setfindTypeData(data->itemType);
            if (data->itemType == 1) {
                data->heroId = message->byteStream->getInt();
                data->dictId = message->byteStream->getInt();
                data->heroForce = message->byteStream->getByte();
                data->name = message->byteStream->getUTF8();
                data->quality = message->byteStream->getByte();
                data->level = message->byteStream->getInt();
                data->prestige =message->byteStream->getInt();
                data->combatPower = message->byteStream->getInt();
                data->leaderShip = message->byteStream->getInt();
                MarketFindResultDataManager::getInstance()->addData(data);
                 MarketGetHeroLayer::show(MarketFindResultDataManager::getInstance()->dumpList->at(0));
//                broadMsg(CUSTOM_MARKER_HEROLAYER);//获得武将
            }
            else if(data->itemType>1 && data->itemType<7){
                data->dictId = message->byteStream->getInt();
                data->name = message->byteStream->getUTF8();
                data->quality = message->byteStream->getByte();
                data->itemDesc = message->byteStream->getUTF8();
                
                Vector<BaseTypeData*> *m_basegift = new Vector<BaseTypeData*>();
                m_basegift->clear();
                BaseTypeData* basedata = new BaseTypeData();
                basedata->autorelease();
                basedata->dataId = data->dictId;
                basedata->dataName = data->name;// itemName;
                basedata->dataType = data->itemType;
                basedata->dataQuality = data->quality;
                basedata->dataCount = 1;
                m_basegift->pushBack(basedata);
                AwardBox_Layer* layer=AwardBox_Layer::create(m_basegift);
                layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
                Scene* scene=Director::getInstance()->getRunningScene();
                scene->addChild(layer);
//                MarketFindResultDataManager::getInstance()->addData(data);
//                MarketGetEquipLayer::show();
//                broadMsg(CUSTOM_MARKER_EQUIPLAYER);//获得物品
            }
            marketFindDataManager::getInstance()->findList->at(m_idx)->status = 1;
            marketFindDataManager::getInstance()->findList->at(m_idx)->heroDictId = 0;
            _tableView->updateCellAtIndex(m_idx);
        }
    }
}

void MarketFindLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIND_FindPageResp).c_str(), CC_CALLBACK_1(MarketFindLayer::onMsgProcess, this));//
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIND_FindResultResp).c_str(), CC_CALLBACK_1(MarketFindLayer::ontDumpMsgProcess, this));
    this->addUserMsg(CUSTOM_MARKER_KAISHIXUNFANG, CC_CALLBACK_1(MarketFindLayer::onSureFindMsgProcess, this));
    this->addUserMsg(CUSTOM_MARKER_SUREJAISU, CC_CALLBACK_1(MarketFindLayer::ontSureSpeedMsgProcess, this));
    this->addUserMsg(CUSTOM_MARKER_LINGDIKUOZHAN, CC_CALLBACK_1(MarketFindLayer::ontlingdikuozhanProcess, this));
}
void MarketFindLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

