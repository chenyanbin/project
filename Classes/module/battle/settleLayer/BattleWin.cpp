//
//  BattleWin.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/23.
//
//

#include "BattleWin.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../tips/TipsLayer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../protocol/Protocal.h"
#include "../../../message/Decoding/stage/RequestEndStageBattle.h"
#include "../../../message/Decoding/musou/RequestMusouEndMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/dictData/DictStageBattleReward/DictStageBattleRewardManager.h"
#include "../../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../../commonData/dictData/DictMusouBattle/DictMusouBattleManager.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../tdTalkData/TDTalkDataManager.hpp"
#include "../../../common/NumberChange.h"
#include "../../../common/CustomMsgProcesser.h"
BattleWin::BattleWin()
:TAG_ITEMBG(1)
,TAG_HEADLIST(2)
,TAG_USERINFO(3)
,TAG_STAR(4)
,TAG_EXPLABEL(5)
,TAG_COINLABEL(6)
,TAG_ENDBTN(7)
,TAG_AGAINBTN(8)
,m_battleID(0)
,commonDrops(NULL)
,prestigeDrops(NULL)
,heroList(NULL)
,m_starCount(0)
,roleOldLevel(0)
,roleNewLevel(0)
,m_starIndex(0)
,m_bloodBottle(0)
,dropCoinAdd(0)
,m_useTime(0)
{
//    SoundManager::setBackgroundMusicVolume(.1);
    commonDrops = new Vector<PrizeData*>();
    prestigeDrops = new Vector<PrizeData*>();
    heroList = new Vector<DictAvatarProp*>();
}
BattleWin::~BattleWin()
{
    CC_SAFE_DELETE(commonDrops);
    CC_SAFE_DELETE(prestigeDrops);
    commonDrops = NULL;
    prestigeDrops = NULL;
    CC_SAFE_DELETE(heroList);
    heroList = NULL;
}
bool BattleWin::init(int battleID,float leftLife,int bloodBottle,int dropCoinAdd,long usetime)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isShowGrayBg = true;
        this->m_battleID = battleID;
        this->m_leftLife = leftLife;
        this->m_bloodBottle = bloodBottle;
        this->dropCoinAdd = dropCoinAdd;
        this->isAbleGuiding = false;
        this->m_useTime = usetime;
        
 
        bref = true;
    } while (false);
    return bref;
}
BattleWin* BattleWin::create(int battleID,float leftLife,int bloodBottle,int dropCoinAdd,long usetime)
{
    BattleWin* layer = new BattleWin();
    if(layer && layer->init(battleID,leftLife,bloodBottle,dropCoinAdd,usetime))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void BattleWin::setItemBg()
{
    Sprite* itemBg = Sprite::create(IMG_BATTLERESULT_ITEMBG);
    itemBg->setAnchorPoint(Point::ZERO);
    itemBg->setCascadeOpacityEnabled(true);
    this->addChild(itemBg,0,TAG_ITEMBG);
    itemBg->setPosition(0, 0);
    itemBg->setOpacity(0);
    this->setContentSize(itemBg->getContentSize());
}
void BattleWin::setUserInfo()
{
    Node* itemBg = this->getChildByTag(TAG_ITEMBG);
 
    Sprite* bg = Sprite::create(IMG_BATTLERESULT_USERPRIZEBG);
    bg->setAnchorPoint(Point::ZERO);
    bg->setCascadeOpacityEnabled(true);
    string str = GlobalInfo::getInstance()->gameRole->name.size() ? GlobalInfo::getInstance()->gameRole->name : "       ";

        
    Label* nickNameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xbdeaff),20,false,false);
    nickNameLabel->setAnchorPoint(Point::ZERO);
    nickNameLabel->setPosition(70, (bg->getContentSize().height - nickNameLabel->getContentSize().height)/2+80);
    bg->addChild(nickNameLabel);
  
    str =  PublicShowUI::numberToString(this->roleNewLevel);
    str = " lv:"+str;
    Label* levelLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x00ff00),20,false,false);
    levelLabel->setAnchorPoint(Point::ZERO);
    levelLabel->setPosition(nickNameLabel->getPositionX() + nickNameLabel->getContentSize().width +20, nickNameLabel->getPositionY());
    bg->addChild(levelLabel);
    
 
    str = "EXP:";
    Label* expTitle =  PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x19c3e8),20,false,false);
    expTitle->setAnchorPoint(Point::ZERO);
    expTitle->setPosition(levelLabel->getPositionX() + levelLabel->getContentSize().width +20, nickNameLabel->getPositionY());
    bg->addChild(expTitle,6);
    
    
    str = PublicShowUI::numberToString(this->expAdd);
    Label* expLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x19c3e8),20,false,false);
    expLabel->setAnchorPoint(Point::ZERO);
    expLabel->setPosition(expTitle->getPositionX() + expTitle->getContentSize().width, expTitle->getPositionY());
    bg->addChild(expLabel,5,TAG_EXPLABEL);
    
    
    Sprite* coin = Sprite::create(IMG_ICON_PUBLIC_COIN);
    coin->setAnchorPoint(Point::ZERO);
    bg->addChild(coin);
    coin->setCascadeOpacityEnabled(true);
    coin->setPosition(expLabel->getPositionX() + expLabel->getContentSize().width +20,nickNameLabel->getPositionY()-10);
    
    str = PublicShowUI::numberToString(this->coinAdd);

    Label* coinLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xfff8da),20,false,false);
    coinLabel->setAnchorPoint(Point::ZERO);
    bg->addChild(coinLabel,6,TAG_COINLABEL);
    coinLabel->setPosition(coin->getPositionX() + coin->getContentSize().width, coin->getPositionY() + (coin->getContentSize().height - coinLabel->getContentSize().height)/2);
    
    str = "+(" + PublicShowUI::numberToString(dropCoinAdd) + ")";
    Label* addCoin = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xfff8da),20,false,false);
    addCoin->setAnchorPoint(Point::ZERO);
    bg->addChild(addCoin,7);
    addCoin->setPosition(coinLabel->getPositionX() + coinLabel->getContentSize().width, coinLabel->getPositionY());
    
    
    
    bg->setOpacity(0);
    this->addChild(bg,3,TAG_USERINFO);
    bg->setPosition((this->getContentSize().width - bg->getContentSize().width)/2, itemBg->getPositionY() + itemBg->getContentSize().height + 10);
}
void BattleWin::setHeroList()
{
    
    Node* userBg = this->getChildByTag(TAG_USERINFO);
    userBg->setCascadeOpacityEnabled(true);
    UserHeadLayer* userHead = NULL;
    Node* headList = Node::create();
    headList->setCascadeOpacityEnabled(true);
    headList->setAnchorPoint(Point::ZERO);
    ssize_t len = heroList->size();
    DictAvatarProp* hero = NULL;
    DictHero* dictHero = NULL;
    for(int i = 0; i < len; i++)
    {
        hero = heroList->at(i);
        if(hero->id == 0)
        {
            continue;
        }
        dictHero = DictHeroManager::getInstance()->getData(hero->dictID);
        if(dictHero)
        {
            userHead=UserHeadLayer::create(dictHero->resource.c_str(),hero->quality,true);
           
            userHead->setHeadInfo(hero->level, hero->prestige);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setCascadeOpacityEnabled(true);
            headList->addChild(userHead);
            userHead->setPosition(i * (userHead->getContentSize().width + 10), 0);
        }
       
        
       
        
    }
    if(userHead)
    {
        Size size = userHead->getContentSize();
        size.width = userHead->getPositionX() + userHead->getContentSize().width;
        headList->setContentSize(size);
        
        
    }
    userBg->addChild(headList,2,TAG_HEADLIST);
    headList->setPosition(30,40);
//    headList->setPosition((this->getContentSize().width - headList->getContentSize().width)/2, userBg->getPositionY()  + 10);
}

void BattleWin::setStar()
{
    
    
    
    Node* userInfo = this->getChildByTag(TAG_USERINFO);
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    Sprite* starBg = NULL;
    Sprite* star = NULL;
   
    for(int i = 0; i < 3; i++)
    {

        starBg = Sprite::create(IMG_BATTLERESULT_STARBG);
        starBg->setAnchorPoint(Point::ZERO);
        node->addChild(starBg,i,i);
        starBg->setPositionX(i * (starBg->getContentSize().width + 7));
        starBg->setPositionY(i % 2 * 10);
        
        if(i < m_starCount)
        {
            star = Sprite::create(IMG_BATTLERESULT_STAR);
            starBg->addChild(star,1,1);
            star->setPosition(starBg->getContentSize().width/2, starBg->getContentSize().height/2);
            star->setVisible(false);

        }
    }
    Size size = starBg->getContentSize();
    size.width = starBg->getPositionX() + starBg->getContentSize().width/2;
    node->setContentSize(size);
    
    node->setPosition((this->getContentSize().width - size.width)/2-30, userInfo->getPositionY() + userInfo->getContentSize().height);
    this->addChild(node,11,TAG_STAR);
    m_starIndex = 0;
    size = this->getContentSize();
    size.height = node->getPositionY()+node->getContentSize().height;
    this->setContentSize(size);
    node->setCascadeOpacityEnabled(true);
    node->setVisible(false);
  
    
}
void BattleWin::showStartEffect(float dt)//星级动画效
{
    Sprite* node = (Sprite*)this->getChildByTag(TAG_STAR);
    if(!node)
    {
        return;
    }
    node->setVisible(true);
    Sprite* starBg = (Sprite*)node->getChildByTag(this->m_starIndex);
    
    if(starBg)
    {
        if(this->m_starIndex < this->m_starCount)
        {
            Node* star = starBg->getChildByTag(1);
            Point cp = star->getPosition();
            star->setVisible(true);
            star->setScale(8);
            ScaleTo* scaleTo = ScaleTo::create(.17, .5);
            ScaleTo* scaleTo2 = ScaleTo::create(.1, 1); 
            CallFuncN* callFun = CallFuncN::create(CC_CALLBACK_1(BattleWin::showStarSound, this));
            star->runAction(Sequence::create(scaleTo,scaleTo2,callFun, NULL));
          
            m_starIndex ++;
        }
        if(m_starIndex >= this->m_starCount)
        {
            this->unschedule(schedule_selector(BattleWin::showStartEffect));
            onSoundReset();
        }
        
    }
}
void BattleWin::onSoundReset()
{
//    SoundManager::resetBackgroundMusicVolume();
    
    Node* itemBg = this->getChildByTag(TAG_ITEMBG);
    float _height = itemBg->getContentSize().height + 20;
    
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleWin::setEndBtn, this));
    Point toPoint1 = itemBg->getPosition();
    toPoint1.y = -10;
    
    Point toPoint2 = toPoint1;
    toPoint2.y = 0;
    itemBg->setPositionY(_height);
    MoveTo* moveby1 = MoveTo::create(.7, toPoint1);
    MoveTo* moveby2 = MoveTo::create(.1, toPoint2);
    itemBg->runAction(Sequence::create(moveby1,moveby2, callBack, NULL));
    itemBg->runAction(FadeIn::create(.5));
}
void BattleWin::showStarSound(Node* target)
{
    SoundManager::playEffectMusic(EFFECT_STAR);
}
void BattleWin::setTitle()
{
//    Sprite* title = Sprite::create(IMG_BATTLERESULT_WINTITLE);
//    title->setAnchorPoint(Point::ZERO);
//    this->addChild(title);
//    title->setPosition(-title->getContentSize().width-10,this->getContentSize().height/2-title->getContentSize().height/2);
//    title->setOpacity(0);
//    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleWin::showUserInfo, this));
//    title->runAction(Sequence::create(FadeIn::create(.5),callBack,NULL));

//
    CommonEffect* commonEffect = CommonEffect::create("shengliguangquan");
    commonEffect->setAnchorPoint(Point::ZERO);
    commonEffect->setPosition(-240,-100);
    this->addChild(commonEffect,-1);
}
void BattleWin::showUserInfo()
{
      setTitle();
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleWin::startStarEffect, this));
    Node* userInfo = this->getChildByTag(TAG_USERINFO);
    userInfo->runAction(Sequence::create(FadeIn::create(.5),callBack, NULL) );
    
    Label* expLabel = (Label*)userInfo->getChildByTag(TAG_EXPLABEL);
    expLabel->setString("");
    expLabel->runAction(NumberChange::create(2, 0, this->expAdd));
    
    
    Label* coinLabel = (Label*)userInfo->getChildByTag(TAG_COINLABEL);
    coinLabel->setString("");
    coinLabel->runAction(NumberChange::create(2, 0, this->coinAdd));
}
void BattleWin::startStarEffect()
{
    this->schedule(schedule_selector(BattleWin::showStartEffect), .2);
}
void BattleWin::setTitleEffect()
{
    CommonEffect* commonEffect = CommonEffect::create("zhandoujiesuan",false);
    commonEffect->isAutoStop = true;
    commonEffect->setAnchorPoint(Point::ZERO);
    commonEffect->setPosition(-commonEffect->getContentSize().width/2 - 65,-40);
    this->addChild(commonEffect,30);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleWin::showUserInfo, this));
    commonEffect->runAction(Sequence::create(FadeIn::create(.5),callBack,NULL));
}
void BattleWin::setEndBtn()
{
    this->setCascadeOpacityEnabled(true);
    Node* userInfo = this->getChildByTag(TAG_USERINFO);
    
    Button* btn = (Button*)this->getChildByTag(TAG_ENDBTN);
    Button* againBtn = (Button*)this->getChildByTag(TAG_AGAINBTN);
    if(btn)
    {
        btn->setVisible(true);
        againBtn->setVisible(true);
        
        if(!CustomMsgProcesser::getInstance()->getIsHasMsg())
        {
            NewPlayerGuild::getInstance()->showNowGuide();
        }
        else
        {
            NewPlayerGuild::getInstance()->pause();
        }
        return;
    }
    
    
    btn = Button::create(IMG_BATTLERESULT_ENDBTN, "", CC_CALLBACK_1(BattleWin::onEndBtnClick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->setCascadeOpacityEnabled(true);
    this->addChild(btn,10,TAG_ENDBTN);
    btn->setVisible(false);

    btn->setPosition(userInfo->getPosition().x + userInfo->getContentSize().width + 10,userInfo->getPositionY());
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumEnd, btn);
  
    againBtn = Button::create(IMG_BATTLERESULT_AGAINBTN, "", CC_CALLBACK_1(BattleWin::onAgainClick, this));
    againBtn->setAnchorPoint(Point::ZERO);
    againBtn->setCascadeOpacityEnabled(true);
    this->addChild(againBtn,10,TAG_AGAINBTN);
    againBtn->setPosition(btn->getPositionX(), btn->getPositionY() - againBtn->getContentSize().height - 20);
    againBtn->setVisible(false);
    NewPlayerGuild::getInstance()->pause();
}
void BattleWin::onAgainClick(Ref* pSender)
{
    int costPower = 0;
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        DictStageBattle* dictStageBattle = DictStageBattleManager::getInstance()->getData(m_battleID);
        costPower = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStageBattle->costPowerElite : dictStageBattle->costPower;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        DictMusouBattle* dictMusouBattle = DictMusouBattleManager::getInstance()->getData(m_battleID);
        costPower = dictMusouBattle->costPower;
    }
    if(GlobalInfo::getInstance()->bodyPower < costPower)
    {
        Dialog::showNoPowerDialog(SCENE_TAG_CHAPTER);
        return;
    }
    this->removeFromParent();
    GlobalInfo::getInstance()->isShowStoryTalk = false;
    broadMsg(CUSTOM_BATTLE_REPLAY);
}
void BattleWin::onEndBtnClick(Ref* pSender)
{
     broadMsg(CUSTOM_BATTLE_QUITBATTLE,__Bool::create(true));
    DictNewGuide* curGuideData = NewPlayerGuild::getInstance()->getNowData();
    if(curGuideData && NewPlayerGuild::getInstance()->addFunction(curGuideData->function,curGuideData->orderIndex))
    {
        NewPlayerGuild::getInstance()->sendNewGuideMsg();
    }

    this->removeFromParent();
   
}
void BattleWin::show(int battleID,float leftLife,int bloodBottle,int dropCoinAdd,long useTime)
{
    
    Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(SCENE_TAG_SETTLE))
    {
        return;
    }
    BattleWin* layer = BattleWin::create(battleID,leftLife,bloodBottle,dropCoinAdd,useTime);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_LAYER_ZORDER,SCENE_TAG_SETTLE);
}
void BattleWin::onMsgProcess(EventCustom* message)
{
   
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
      log("back eventlistener==%d",msg->messageID);
    if(msg->messageID == SCENSE_CLIENT_BATTLE_EndBattleResp || msg->messageID == SCENSE_CLIENT_MUSOU_MusouEndBattleResp)
    {
        if(!msg->state)
        {
            log("结算失败啦。。。。。。。。。==%d",msg->messageID);
            onEndBtnClick(NULL);
            return;
        }

        commonDrops->clear();
        prestigeDrops->clear();
        m_starCount = msg->byteStream->get();
        expAdd = msg->byteStream->getInt();
        coinAdd = msg->byteStream->getInt();
        roleOldLevel = msg->byteStream->getInt();
        roleNewLevel = msg->byteStream->getInt();


        int len = msg->byteStream->get();
        for(int i = 0; i < len; i++)
        {
            DictAvatarProp* avatar = new DictAvatarProp();
            avatar->autorelease();
            avatar->dictID = msg->byteStream->getInt();
            avatar->id = msg->byteStream->getInt();
            avatar->level = msg->byteStream->getInt();
            avatar->prestige = msg->byteStream->getInt();
            avatar->quality = msg->byteStream->get();
            heroList->pushBack(avatar);
        }
        len = msg->byteStream->get();

        for(int i = 0; i < len; i++)
        {
            PrizeData* prize = new PrizeData();
            prize->autorelease();
            prize->itemType = msg->byteStream->get();
            prize->itemDictId = msg->byteStream->getInt();
            prize->itemCount = msg->byteStream->get();
            prize->itemQuality = msg->byteStream->get();
            commonDrops->pushBack(prize);
        }
        len = msg->byteStream->get();
        for(int i = 0; i < len; i++)
        {
            PrizeData* prize = new PrizeData();
            prize->autorelease();
            prize->itemType = msg->byteStream->get();
            prize->itemDictId = msg->byteStream->getInt();
            prize->itemCount = msg->byteStream->get();
            prize->itemQuality = msg->byteStream->get();
            
            prize->itemQuality = prize->itemQuality == 0 ? 1 : prize->itemQuality ;
            prestigeDrops->pushBack(prize);
            commonDrops->pushBack(prize);
        }
        setItemBg();
      
        
        setUserInfo();
        setHeroList();
        setStar();
        setEndBtn();
  
        setPrizeItem();
        setStarInstruction();
        setTitleEffect();
        PublicShowUI::setTargetScale(this);
        this->setAnchorPoint(Point::ZERO);
        this->setPosition(VisibleRect::center().x - this->getContentSize().width/2,VisibleRect::center().y - this->getContentSize().height/2);
        this->setCascadeOpacityEnabled(true);
    }
    else
    {
        log("没有进入返回");
    }
    
}
void BattleWin::setStarInstruction()
{
    if(GlobalInfo::getInstance()->battleType != kBattleType_MingZhanYi)
    {
        return;
    }
     Node* userInfo = this->getChildByTag(TAG_USERINFO);
    userInfo->setCascadeOpacityEnabled(true);
    DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(this->m_battleID);
    string str = "";
    vector<string> strList;
    vector<bool> hasStarList;
    if(stageBattle->starDetermine1 > 0)//通关
    {
        strList.push_back("消灭所有敌人");
        hasStarList.push_back(true);
    }
    if(stageBattle->starDetermine2 > 0)
    {
        strList.push_back("剩余血量≥"+ PublicShowUI::numberToString(stageBattle->starDetermine2 * 100) + "%");
       hasStarList.push_back(this->m_leftLife >= stageBattle->starDetermine2);
    }
    
    if(stageBattle->starDetermine3 > 0)
    {
        strList.push_back("用时≤" + PublicShowUI::numberToString(stageBattle->starDetermine3) +"秒");
        hasStarList.push_back(this->m_useTime <= stageBattle->starDetermine3);
    }
    Label* label = NULL;
    Sprite* star = NULL;
    float scale = .3;
    for(int i = 0;i < strList.size(); i++)
    {
        label = PublicShowUI::getLabel(strList[i].c_str(),PublicShowUI::getColor3b(0xff7b7b),18,false,false);
        label->setAnchorPoint(Point::ZERO);
        userInfo->addChild(label,10);
        label->setPosition(userInfo->getContentSize().width - 213, 25 + i * (label->getContentSize().height + 12));
        if(hasStarList[i])
        {
            label->setColor(Color3B::GREEN);
            star = Sprite::create(IMG_BATTLERESULT_STAR);
            star->setScale(scale);
            star->setAnchorPoint(Point::ZERO);
            star->setPosition(label->getPositionX() - star->getContentSize().width * scale, label->getPositionY());
            userInfo->addChild(star,10);
        }
       
    }
    str = PublicShowUI::numberToString(m_useTime) + "秒";
    
   
    Label* useLabel = PublicShowUI::getLabel(str.c_str() ,PublicShowUI::getColor3b(0xffaf9d),20,false,false);
    useLabel->setAnchorPoint(Point::ZERO);
    userInfo->addChild(useLabel,10);
    useLabel->setPosition(label->getPositionX() + 55, label->getPositionY() + label->getContentSize().height + 15);
}
//Node* BattleWin::getIconByTypeID(int typeId,int id,int quality)
//{
//    //头像背景
//    char sttr[100] = "";
//    memset(sttr, 0, 100);
//    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
//    TouchSprite* iconBg = TouchSprite::createWithPic(sttr);
//    iconBg->setAnchorPoint(Point::ZERO);
//    
//    const char* path = PublicShowUI::getGoods(typeId,id);
//    if(strcmp(path, "") != 0)
//    {
//        Sprite* icon = Sprite::create(path);
//        if(icon)
//        {
//            float _scaleX = (iconBg->getContentSize().width - 5) / icon->getContentSize().height;
//            icon->setScale(_scaleX);
//            icon->setPosition(iconBg->getContentSize().width/2, iconBg->getContentSize().height/2);
//            iconBg->addChild(icon);
//        }
//    }
//    
//    memset(sttr, 0, 100);
//    sprintf(sttr,IMG_PUBLIC_HEADTALENTFRAME,quality);
//    Sprite* headForm=Sprite::create(sttr);
//    
//    headForm->setPosition(iconBg->getContentSize().width/2, iconBg->getContentSize().height/2);
//    iconBg->addChild(headForm);
//    return iconBg;
//}
Node* BattleWin::getIconByTypeID(int typeId,int id,int quality)
{
    const char* path = PublicShowUI::getGoods(typeId,id);
    UserEquipLayer* head = UserEquipLayer::create(path,quality,false);
    head->setAnchorPoint(Point::ZERO);
    if (typeId == DictItemTypeEnumItemMater) {
        head->setFragment();
    }else if (typeId == DictItemTypeEnumItemBook)
    {
        head->setLetterFragment();
    }
 
    return head;
}
void BattleWin::setPrizeItem()
{

    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    node->setCascadeOpacityEnabled(true);
    ssize_t len = commonDrops->size();
    PrizeData* prize = NULL;
    UserHeadLayer* icon = NULL;

    float _width = 125.8;
    for(int i= 0 ;i <len; i++)
    {
        prize = commonDrops->at(i);
 
        
        icon = (UserHeadLayer*)this->getIconByTypeID(prize->itemType,prize->itemDictId,prize->itemQuality);
        icon->setAnchorPoint(Point::ZERO);
        icon->addTouchBegainCallBack(this, callfuncN_selector(BattleWin::onItemClick));
//        if(prize->itemCount > 1)
//        {
//            Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(prize->itemCount).c_str(),Color3B::WHITE,17,false,false);
//            label->setAnchorPoint(Point::ZERO);
//            icon->addChild(label);
//            label->setPosition(icon->getContentSize().width - label->getContentSize().width - 2, 2);
//           
//        }
        icon->setCascadeOpacityEnabled(true);
        node->addChild(icon,i,i);
        icon->setPositionX(i * (_width));
        
   
     
        
    }
    if(icon)
    {
        Size size = icon->getContentSize();

        size.width = icon->getPositionX() + size.width;
        node->setContentSize(size);
    }
    Node* itemBg = this->getChildByTag(TAG_ITEMBG);
    itemBg->setCascadeColorEnabled(true);
    node->setPosition(24, 50);
    itemBg->addChild(node);
    
}
void BattleWin::onItemClick(Node* node)
{
    PrizeData* prize = commonDrops->at(node->getTag());
    TipsLayer::show(prize->itemType, prize->itemDictId, prize->itemCount);
}
void BattleWin::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
    Director::getInstance()->getScheduler()->setTimeScale(1);
   
   
}
void BattleWin::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void BattleWin::onExitTransitionDidStart()
{
//     SoundManager::resetBackgroundMusicVolume();
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumEnd);
    log(" removeButton removeButton removeButton removeButton DictNewGuideEventEnumEnd");
}
void BattleWin::onEnterTransitionDidFinish()
{
    SoundManager::stopBackgroundMusic();
    
    BaseLayer::onEnterTransitionDidFinish();
    Director::getInstance()->getScheduler()->setTimeScale(1);
   
   
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        m_starCount = 1;//通关为1
        DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(m_battleID);
        if(this->m_leftLife >= stageBattle->starDetermine2)
        {//剩余血量
            m_starCount++;
        }
        if(this->m_useTime <= stageBattle->starDetermine3)
        {//使用时间秒
            m_starCount++;
        }
    }
    else
    {
        m_starCount = 3;
    }
    
    Dialog::showServerLoading();
    if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        RequestMusouEndMsg* msg = new RequestMusouEndMsg(m_battleID,1,m_starCount,m_bloodBottle);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        
        RequestEndStageBattle* msg = new RequestEndStageBattle(m_battleID,1,m_starCount,m_bloodBottle);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
         Dialog::hideServerLoading();
        onEndBtnClick(NULL);
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_LoginBattle)
    {
        
        Dialog::hideServerLoading();
        onEndBtnClick(NULL);
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle)
    {
        Dialog::hideServerLoading();
        onEndBtnClick(NULL);
    }
    TDTalkDataManager::getInstance()->onMissionCompleted(PublicShowUI::numberToString(m_battleID).c_str());
    
}
void BattleWin::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BATTLE_EndBattleResp).c_str(), CC_CALLBACK_1(BattleWin::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MUSOU_MusouEndBattleResp).c_str(), CC_CALLBACK_1(BattleWin::onMsgProcess, this));
}
void BattleWin::removeEventListener()
{
    BaseLayer::removeEventListener();
}