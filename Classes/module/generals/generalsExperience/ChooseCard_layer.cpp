//
//  ChooseCard_layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/13.
//
//

#include "ChooseCard_layer.h"
#include "ExperienceEffect.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../message/Decoding/generals/experience/ChooseCardMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/dictData/DictHeroLevel/DictHeroLevelManager.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../../message/Decoding/generals/experience/ExperienceDetermineMsg.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../common/Dialog/PopUpLayer.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"

ChooseCard_layer::ChooseCard_layer()
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
,thisSort("")
,upHeroData(NULL)
,selectCard(NULL)
,isMoveing(false)
{
    chooseCardList=new Vector<CardPropertyData*>() ;
    upHeroData=new CardPropertyData();
    selectCard=new UserHeadLayer();
}
ChooseCard_layer::~ChooseCard_layer()
{
    chooseCardList->clear();
    CC_SAFE_DELETE(chooseCardList);
    
//    CC_SAFE_RELEASE_NULL(upHeroData);
//    CC_SAFE_RELEASE_NULL(selectCard);
    CardDataManager::getInstance()->clearCardList();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumExperience);
    upHeroData=NULL;
}

void ChooseCard_layer::onExit()
{
    BaseLayer::onExit();
}
void ChooseCard_layer::onEnter()
{
    BaseLayer::onEnter();
}
void ChooseCard_layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumGeneralsHead);
}
void ChooseCard_layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
bool ChooseCard_layer::init(int cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        thisSort="level";
        this->setBackground(IMG_GENERALS_EXPERIENCE_LIST_BG2);
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
ChooseCard_layer* ChooseCard_layer::create(int cardId)
{
    ChooseCard_layer* layer = new ChooseCard_layer();
    if(layer && layer->init(cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void ChooseCard_layer::createLayer()
{
    


    
    Sprite* listLabel=Sprite::create(IMG_GENERALS_EXPERIENCE_LIST_LABEL);
    listLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listLabel);
    listLabel->setPosition(40*sx,26*sx);
    this->addChild(listLabel,3);
    
    string numStr=":"+PublicShowUI::numberToString(getExperience);
    Label* currentLv = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    currentLv->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(currentLv);
    currentLv->setPosition(125*sx,54*sx);
    this->addChild(currentLv,3,TAG_EXPERIENCELABEL);
    
    string expStr=":"+PublicShowUI::numberToString(getExperience);
    Label* expLabel = PublicShowUI::getLabel(expStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    expLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(expLabel);
    expLabel->setPosition(125*sx,25*sx);
    this->addChild(expLabel,3,TAG_EXPUPDATALABEL);
    
    string lvStr="LV"+PublicShowUI::numberToString(CardDataManager::getInstance()->getPresentData()->level);
    Label* lvLabel = PublicShowUI::getLabel(lvStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    lvLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(lvLabel);
    lvLabel->setPosition(210*sx,56*sx);
    this->addChild(lvLabel,3,TAG_CURRENTLV);
   
    string upLvStr="+0";
    Label* upLvLabel = PublicShowUI::getLabel(upLvStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
    upLvLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(upLvLabel);
    upLvLabel->setPosition(lvLabel->getContentSize().width+lvLabel->getPositionX()+10*sx,lvLabel->getPositionY());
    this->addChild(upLvLabel,3,TAG_UPLEVEL);
    
    //颜值
    Sprite* prestSprite=Sprite::create(IMG_GENERALSLIST_PREST);
    prestSprite->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(prestSprite);
    prestSprite->setPosition(210*sx,27*sx);
    this->addChild(prestSprite,3);
    expStr=PublicShowUI::numberToString(CardDataManager::getInstance()->getPresentData()->prestige);
    Label* prestLabel = PublicShowUI::getLabel(expStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),18,false,false);
    prestLabel->setAnchorPoint(Point::ZERO);
    prestLabel->setPosition(90,(prestSprite->getContentSize().height/sx-prestLabel->getContentSize().height)/2);
    prestSprite->addChild(prestLabel,1);
    
    string addPrestStr="+0";
    Label* addPrestLabel = PublicShowUI::getLabel(upLvStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),20,false,false);
    addPrestLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(addPrestLabel);
    addPrestLabel->setPosition(prestSprite->getContentSize().width+prestSprite->getPositionX()+6*sx,prestSprite->getPositionY()+(prestSprite->getContentSize().height-addPrestLabel->getContentSize().height)/2);
    this->addChild(addPrestLabel,3,TAG_ADDPRESTIGE);
    //开始历练按钮
    Button* startBtn=Button::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE, "", CC_CALLBACK_1(ChooseCard_layer::onStartExperience, this));
    PublicShowUI::setTargetScale(startBtn);
    startBtn->setAnchorPoint(Point::ZERO);
    startBtn->setPosition(this->getContentSize().width-startBtn->getContentSize().width-45*sx,30*sx);
    this->addChild(startBtn);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumExperience, startBtn);
    Sprite* startLabel=Sprite::create(IMG_PUBLIC_LABEL_STARTPRACTICE);
    startLabel->setAnchorPoint(Point::ZERO);
    startLabel->setPosition((startBtn->getContentSize().width/sx-startLabel->getContentSize().width)/2,(startBtn->getContentSize().height/sx-startLabel->getContentSize().height)/2);
    startBtn->addChild(startLabel,2);
    
    //消耗
    Sprite* coin=Sprite::create(IMG_ICON_PUBLIC_COIN);
    coin->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(coin);
    coin->setPosition(startBtn->getPositionX()-startBtn->getContentSize().width,(startBtn->getContentSize().height-coin->getContentSize().height)/2+30*sx);
    this->addChild(coin,3);
    
    string coinStr="0";
    Label* coinLabel = PublicShowUI::getLabel(coinStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),20,false,false);
    coinLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(coinLabel);
    coinLabel->setPosition(coin->getContentSize().width+coin->getPositionX()+5*sx,coin->getPositionY()+(coin->getContentSize().height-coinLabel->getContentSize().height)/2);
    this->addChild(coinLabel,3,TAG_CONSUME);
//    IMG_ICON_PUBLIC_COIN
}
void ChooseCard_layer::onStartExperience(Ref* psender)
{
    int num=(int)CardDataManager::getInstance()->getDataList()->size();
    CardPropertyData*data=CardDataManager::getInstance()->getPresentData();
    CardPropertyData*data2=NULL;
    
    bool isBol=false;
    for (int i=0; i<num; i++) {
        data2=CardDataManager::getInstance()->getCardDataByIndex(i);
        if (data2->quality>2 or data2->level>1 or data2->prestige>data->prestige) {
            isBol=true;
            break;
        }
    }
    if (isBol && GlobalInfo::getInstance()->isGuiding == false) {
        Dialog::show("您当前放入了更加强力的武将，历练后这些武将将会消失，是否继续？","",2,this,callfuncN_selector(ChooseCard_layer::onNext));
    }else
    {
        ExperienceDetermineMsg* msg = new ExperienceDetermineMsg(CardDataManager::getInstance()->getPresentData()->heroId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
        
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumExperience);
    
}
void ChooseCard_layer::onNext(Node* pSender)
{
    if(pSender && pSender->getTag() == 1)
    {
        ExperienceDetermineMsg* msg = new ExperienceDetermineMsg(CardDataManager::getInstance()->getPresentData()->heroId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }

}
//void ChooseCard_layer::onTopComboBoxClick(Ref* psender)
//{
//    Node* sp=(Node*)psender;
//    int tag=sp->getTag();
//    switch (tag) {
//        case 0:
//            thisSort="level";
//            break;
//        case 1:
//            thisSort="quality";
//            break;
//        case 2:
//            thisSort="prestige";
//            break;
//        default:
//            break;
//    }
//    this->sortList(thisSort);
//}

//--------------------------------列表部分-------------------------------------------------------//
void ChooseCard_layer::initTableView()
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
    _size.height=_size.height*3;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition(40*sx,105*sx);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    //    shade->setScaleX(0.6);
    //    shade->setOpacity(170);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(0*sx,90*sx);
    this->addChild(shade,3);
    
    
    
}
TableViewCell* ChooseCard_layer::tableCellAtIndex(TableView *table, ssize_t idx)
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
        if (chooseCardList->size()>tag) {
            int tempNum=chooseCardList->at(tag)->heroDictId;
            DictHero* dictHero = DictHeroManager::getInstance()->getData(tempNum);
            if (dictHero) {
                UserHeadLayer* userHead=UserHeadLayer::create(dictHero->resource.c_str(),chooseCardList->at(tag)->quality);
                userHead->setAnchorPoint(Point::ZERO);
                userHead->setHeadInfo(chooseCardList->at(tag)->level, chooseCardList->at(tag)->prestige);
                userHead->setHeadNumber(chooseCardList->at(tag)->isSelect);
                userHead->addTouchBegainCallBack(this, callfuncN_selector(ChooseCard_layer::onUserClick));
                userHead->setPosition(5+136*i,5);
                cell->addChild(userHead,1,tag);
                if(tag == 0)
                {
                    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumGeneralsHead, userHead);
                }

            }
           
        }
    }
    return cell;
}

//列表大小
Size ChooseCard_layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
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
ssize_t ChooseCard_layer::numberOfCellsInTableView(TableView *table)
{
    float t=(float)chooseCardList->size()/5;
    
    int count = ceil(t);
    return count;
}

//点击cell事件
void ChooseCard_layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumGeneralsHead);
    if (!isMoveing) {
        return;
    }
    int tag=selectCard->getTag();
    CardPropertyData* data= chooseCardList->at(tag);
    if(!data)
    {
        return;
    }
    if (data->isSelect) {
        data->isSelect=false;
        CardDataManager::getInstance()->removeData(data->heroId);
    }else
    {
        data->isSelect=true;
        CardDataManager::getInstance()->addData(data);
    }
    this->updataData();
    selectCard->setHeadNumber(data->isSelect);
  
    this->isMoveing=false;
}
void ChooseCard_layer::scrollViewDidScroll(ScrollView* view)
{
    
}
//////////////------------------------------------------------------------------------------//////////////////

void ChooseCard_layer::onUserClick(Node* pSender)
{
    this->isMoveing=true;
    selectCard=(UserHeadLayer*)pSender;
    
}
bool sortOnHeroLevelDescend(DictHeroLevel* n1, DictHeroLevel* n2)//倒序(从小到大)
{
    return n1->heroLevel < n2->heroLevel;
}
void ChooseCard_layer::updataData()
{
    
    int expNum=0;//获取经验
    int upPrest=0;//增加声望
    int coinNum=0;//钱数；
    int totalExper=0;//增加经验
    int MaxLevel=0;//最大等级
    int level=CardDataManager::getInstance()->getPresentData()->level;//当前等级
    int exper=CardDataManager::getInstance()->getPresentData()->heroExperience;//当前经验
    int maxExp=0;//当前品质 当前等级需要多少经验升到最高等级
    
    
    Vector<DictHeroLevel*>* dictHroLevel=DictHeroLevelManager::getInstance()->getDataList();
    sort(dictHroLevel->begin(),dictHroLevel->end(),sortOnHeroLevelDescend);
    //品质等级表
    Vector<DictHeroQuality*>* dictHeroQuality=  DictHeroQualityManager::getInstance()->getDataList();
    //当前历练的品质
    int tempQuality=CardDataManager::getInstance()->getPresentData()->quality;
    
    for(DictHeroQuality* monster :* dictHeroQuality)
    {
        if (monster->level==tempQuality) {
            MaxLevel=monster->levelUpLimit;
            break;
        }
    }
    
    //当前品质 当前等级需要多少经验升到最高等级计算
    for (DictHeroLevel* targe : *dictHroLevel) {
        if (targe->heroLevel <=MaxLevel and targe->heroLevel>=level) {
            maxExp+=targe->heroLevelUpExp;
        }
    }
    maxExp-=exper;
    //--------------------------计算结束
    
    int _size=(int)CardDataManager::getInstance()->getDataList()->size();
    for (int i=0; i<_size; i++) {
        //
        CardPropertyData* data=CardDataManager::getInstance()->getCardDataByIndex(i);
        expNum+=data->cardGetExperience*data->cardGetExpValue;
        
        totalExper+=data->cardGetExperience;
        
        if (CardDataManager::getInstance()->getPresentData()->heroDictId==data->heroDictId) {
            upPrest+=data->prestige;
        }
        
        coinNum+=data->cardConsumeCoin;
    }
    if (expNum>maxExp) {
        expNum=maxExp;
    }
    //当前获取经验
    Label* currentLabel=(Label*)this->getChildByTag(TAG_EXPERIENCELABEL);
    string numStr=":"+PublicShowUI::numberToString(expNum);
    if (currentLabel and level<MaxLevel) {
        currentLabel->setString(numStr);
    }
    
    int heroAddlevel=0;
    int hardenLevel=-exper;
    for (DictHeroLevel* targe : *dictHroLevel) {
        if (targe->heroLevel >=level) {
            hardenLevel+=targe->heroLevelUpExp;
            if (expNum!=0 and expNum>=hardenLevel and (level+heroAddlevel)<MaxLevel) {
                heroAddlevel++;
            }else
            {
                break;
            }
        }
    }
    Label* expUpLabel=(Label*)this->getChildByTag(TAG_UPLEVEL);
    if (expUpLabel) {
//        if (level==MaxLevel) {
//            Label* expUpLabel=(Label*)this->getChildByTag(TAG_UPLEVEL);
//            Sprite* max=Sprite::create(IMG_PUBLIC_LABEL_MAX);
//            max->setAnchorPoint(Point::ZERO);
//            PublicShowUI::setTargetScale(max);
//            max->setPosition(expUpLabel->getPosition());
//            this->addChild(max);
//            if (expUpLabel) {
//                this->removeChildByTag(TAG_UPLEVEL);
//            }
//        }else
//        {
            expUpLabel->setString("+"+PublicShowUI::numberToString(heroAddlevel));
//        }
        
    }
    //声望
    Label* prestigeLabel=(Label*)this->getChildByTag(TAG_ADDPRESTIGE);
    if (prestigeLabel) {
        prestigeLabel->setString("+ "+PublicShowUI::numberToString(upPrest));
    }
    
    
    //花费
     Label* consumeLabel=(Label*)this->getChildByTag(TAG_CONSUME);
    if (consumeLabel) {
        consumeLabel->setString(PublicShowUI::numberToString(coinNum));
    }
    CC_SAFE_DELETE(dictHroLevel);
    dictHroLevel = NULL;
    CC_SAFE_DELETE(dictHeroQuality);
    dictHeroQuality = NULL;
}

//-----------------------------------------------访问服务器-------------------------------------------------------//
void ChooseCard_layer::requestListMsg()
{
    ChooseCardMsg* msg = new ChooseCardMsg(CardDataManager::getInstance()->getPresentData()->heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ChooseCard_layer::onMsgProcess(EventCustom* msg)
{
    
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_HERO_HeroMaterialSelPageResp)
    {
        
        chooseCardList->clear();
        CardPropertyData* prestionCardData=new CardPropertyData();
        prestionCardData->heroExperience=message->byteStream->getInt();
        prestionCardData->level=cardLeve=message->byteStream->getShort();
        prestionCardData->heroDictId=message->byteStream->getInt();
        prestionCardData->quality=message->byteStream->getByte();
        
        int sizeInt=message->byteStream->getShort();
        for (int i=0; i<sizeInt; i++) {
            CardPropertyData* cardData=new CardPropertyData();
            cardData->heroId=message->byteStream->getInt();
            cardData->heroDictId=message->byteStream->getInt();
            cardData->level=message->byteStream->getShort();
            cardData->prestige=message->byteStream->getShort();
            cardData->quality=message->byteStream->getByte();
            
            DictHero* dictHero = DictHeroManager::getInstance()->getData(cardData->heroDictId);
            if (dictHero) {
                cardData->cardGetExpValue=(float)dictHero->initialStar/(float)100;
                cardData->backPackOrder=dictHero->seq;
            }
            cardData->cardGetExperience=this->setCardInfoData("quality",cardData->quality);
            cardData->cardConsumeCoin=this->setCardInfoData("consumeCoin",cardData->quality);
            chooseCardList->pushBack(cardData);
            
        }
        DictHeroLevel* heroLevel = DictHeroLevelManager::getInstance()->getData(cardLeve);
        if(heroLevel)
        {
            int upExp= heroLevel->heroLevelUpExp-prestionCardData->heroExperience;
            Label* expUpLabel=(Label*)this->getChildByTag(TAG_EXPUPDATALABEL);
            string expStr=":"+PublicShowUI::numberToString(upExp);
            if (expUpLabel) {
                expUpLabel->setString(expStr);
            }
            Label* currentLvLabel=(Label*)this->getChildByTag(TAG_CURRENTLV);
            expStr="LV."+PublicShowUI::numberToString(cardLeve);
            if (currentLvLabel) {
                currentLvLabel->setString(expStr);
            }
            
        }
        
        
        this->sortList(thisSort);
        NewPlayerGuild::getInstance()->showNowGuide();
    }else if(message->messageID == SCENSE_CLIENT_HERO_HeroStartPlacesResp)
    {
        upHeroData->heroDictId=message->byteStream->getInt();
        upHeroData->heroName=message->byteStream->getUTF8();
        upHeroData->heroForce=message->byteStream->getByte();
        upHeroData->level=message->byteStream->getInt();
        upHeroData->leadership=message->byteStream->getInt();
        upHeroData->prestige=message->byteStream->getInt();
        upHeroData->combatPower=message->byteStream->getInt();
        upHeroData->heroExperience=message->byteStream->getInt();
        upHeroData->heroMaxExperience=message->byteStream->getInt();
        //历练特效
        
        this->effectOver();
//        userHead->runAction(CCSequence::create(DelayTime::create(0.05),CallFuncN::create(CC_CALLBACK_1(ChooseCard_layer::effectOver, this)), NULL));
    }
    
}
void ChooseCard_layer::effectOver()
{
    CardPropertyData* data=new CardPropertyData();
    CardDataManager::getInstance()->copyData(data, CardDataManager::getInstance()->getPresentData());
    ExperienceEffect* effect=ExperienceEffect::create(data, upHeroData);
    Scene* scene=Director::getInstance()->getRunningScene();
    effect->setPosition(VisibleRect::center());
    scene->addChild(effect,10);
    
    CardDataManager::getInstance()->clearCardList();
//    upCostList->clear();
    Label* currentLabel=(Label*)this->getChildByTag(TAG_EXPERIENCELABEL);
    string numStr=": 0";
    if (currentLabel) {
        currentLabel->setString(numStr);
    }
    Label* expUpLabel=(Label*)this->getChildByTag(TAG_UPLEVEL);
    if (expUpLabel) {
        expUpLabel->setString("+0");
    }
    
    //声望
    Label* prestigeLabel=(Label*)this->getChildByTag(TAG_ADDPRESTIGE);
    if (prestigeLabel) {
        prestigeLabel->setString("+ 0");
    }
    
    
    //花费
    Label* consumeLabel=(Label*)this->getChildByTag(TAG_CONSUME);
    if (consumeLabel) {
        consumeLabel->setString("0");
    }
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        this->removeChildByTag(TAG_TABLEVIEW);
    }

    this->broadMsg(CUSTOM_START_FUN);
}
int ChooseCard_layer::setCardInfoData(string valueStr , int value)
{
    
    int valueNum=0;
    Vector<DictHeroPrestigeUpCost*>* list = DictHeroPrestigeUpCostManager::getInstance()->getDataList();
    
    
    for (DictHeroPrestigeUpCost* stage : *list) {
        if (stage->level==cardLeve and stage->quality==value) {
            if (valueStr=="quality") {
                valueNum=stage->rewardExp;
            }else if (valueStr=="consumeCoin")
            {
                valueNum=stage->consumeCoin;
            }
            break;
            
        }
        
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return valueNum;
}
//状态排序
bool sortOnChooseCardId(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->heroDictId ==114030 ;
}
bool sortOnChooseCardId2(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->heroDictId ==114040;
}
bool sortOnChooseCardPrestige(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->prestige > n2->prestige;
}
bool sortOnChooseCardQualityAscend(CardPropertyData* n1, CardPropertyData* n2)//倒序(从大到小)
{
    return n1->quality > n2->quality;
}
bool sortOnChooseCardQualityDescend(CardPropertyData* n1, CardPropertyData* n2)//倒序(从小到大)
{
    return n1->quality < n2->quality;
}
bool sortOnChooseCardLevel(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->level > n2->level;
}
bool sortOnChooseCardPackOrder(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->backPackOrder < n2->backPackOrder ;
}

//-------------------------------------------------------排序-------------------------------------------------------//
void ChooseCard_layer::sortList(string name)
{
    stable_sort(chooseCardList->begin(), chooseCardList->end(),sortOnChooseCardPackOrder);
    stable_sort(chooseCardList->begin(), chooseCardList->end(),sortOnChooseCardLevel);
    stable_sort(chooseCardList->begin(), chooseCardList->end(),sortOnChooseCardQualityAscend);
    stable_sort(chooseCardList->begin(), chooseCardList->end(),sortOnChooseCardId);
    stable_sort(chooseCardList->begin(), chooseCardList->end(),sortOnChooseCardId2);
    
    //灵龟王排序
    int tempNum=0;
    int num2=0;
    ssize_t len = chooseCardList->size();
    for (int i=0;i<len;i++) {
        if (chooseCardList->at(i)->heroDictId==114040) {
            tempNum++;
        }else if (chooseCardList->at(i)->heroDictId==114030)
        {
            num2++;
        }else
        {
            break;
        }
    }
    num2+=tempNum;
    if (tempNum) {
        stable_sort(chooseCardList->begin(), chooseCardList->begin()+tempNum,sortOnChooseCardPackOrder);
        stable_sort(chooseCardList->begin(), chooseCardList->begin()+tempNum,sortOnChooseCardLevel);
        stable_sort(chooseCardList->begin(), chooseCardList->begin()+tempNum,sortOnChooseCardQualityAscend);
    }
    //灵龟幼崽排序
    if (num2) {
        stable_sort(chooseCardList->begin()+tempNum, chooseCardList->begin()+num2,sortOnChooseCardPackOrder);
        stable_sort(chooseCardList->begin()+tempNum, chooseCardList->begin()+num2,sortOnChooseCardLevel);
        stable_sort(chooseCardList->begin()+tempNum, chooseCardList->begin()+num2,sortOnChooseCardQualityAscend);
    }
    this->initTableView();
}

void ChooseCard_layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroMaterialSelPageResp).c_str(), CC_CALLBACK_1(ChooseCard_layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroStartPlacesResp).c_str(), CC_CALLBACK_1(ChooseCard_layer::onMsgProcess, this));
}
void ChooseCard_layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
