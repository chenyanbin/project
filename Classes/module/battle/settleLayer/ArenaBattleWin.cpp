//
//  ArenaBattleWin.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/31.
//
//

#include "ArenaBattleWin.hpp"
#include "../../../protocol/Protocal.h"
#include "../../../message/Encoding/MessageReceive.h"
#include "../../../message/Decoding/arena/ArenaBattleEndMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../battleTest/PlayerDataManager.hpp"
#include "../../../protocol/UserCustomEvent.h"
#include "../../arena/historyBest/HistoryBestLayer.hpp"
ArenaBattleWin::ArenaBattleWin()
:roleName("")
,roleLevel(1)
,m_honour(0)
,m_gold(0)
,m_nowOrder(0)
,changeValue(0)
{
    
}
ArenaBattleWin::~ArenaBattleWin()
{
    
}
bool ArenaBattleWin::initWithRoleID()
{
    this->m_roleID =  PlayerDataManager::getInstance()->_targetRoleID;
    this->isShowGrayBg = true;
    this->isClickClose = true;
    this->isAbleGuiding = false;
    setUserInfo();
    setTitle();
    
    return true;
}
ArenaBattleWin* ArenaBattleWin::create()
{
    ArenaBattleWin* layer = new ArenaBattleWin();
    if(layer && layer->initWithRoleID())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void ArenaBattleWin::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(SCENE_TAG_SETTLE))
    {
        return;
    }
    ArenaBattleWin* layer = ArenaBattleWin::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_LAYER_ZORDER,SCENE_TAG_SETTLE);

}
void ArenaBattleWin::setTitle()
{
    Node* node = this->getChildByTag(TAG_USERINFO);
    Sprite* title = Sprite::create(IMG_BATTLERESULT_WINTITLE);
    title->setAnchorPoint(Point::ZERO);
    this->addChild(title);
    title->setPosition((node->getContentSize().width - title->getContentSize().width)/2,node->getContentSize().height);
    Size size = node->getContentSize();
    size.height = title->getContentSize().height + title->getPositionY();
    this->setContentSize(size);
}
void ArenaBattleWin::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
    Director::getInstance()->getScheduler()->setTimeScale(1);
    
    
}
void ArenaBattleWin::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void ArenaBattleWin::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    broadMsg(CUSTOM_BATTLE_QUITBATTLE,__Bool::create(true));
}
void ArenaBattleWin::onEnterTransitionDidFinish()
{
    SoundManager::stopBackgroundMusic();
    BaseLayer::onEnterTransitionDidFinish();
    
    Dialog::showServerLoading();
    ArenaBattleEndMsg* msg = new ArenaBattleEndMsg(true,this->m_roleID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ArenaBattleWin::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaEndBattleResp).c_str(), CC_CALLBACK_1(ArenaBattleWin::onMsgCallBack, this));
}
void ArenaBattleWin::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void ArenaBattleWin::setUserInfo()
{
    if(this->getChildByTag(TAG_USERINFO))
    {
        this->removeChildByTag(TAG_USERINFO);
    }
    Sprite* bg = Sprite::create(IMG_ARENA_WINBG);
    bg->setAnchorPoint(Point::ZERO);
    bg->setCascadeOpacityEnabled(true);
    string str = GlobalInfo::getInstance()->gameRole->name.size() ? GlobalInfo::getInstance()->gameRole->name : "       ";
    
    
    Label* nickNameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xbdeaff),20,false,false);
    nickNameLabel->setAnchorPoint(Point::ZERO);
    nickNameLabel->setPosition(70, (bg->getContentSize().height - nickNameLabel->getContentSize().height)/2+80);
    bg->addChild(nickNameLabel);
    
    str =  PublicShowUI::numberToString(this->roleLevel);
    str = " lv:"+str;
    Label* levelLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x00ff00),20,false,false);
    levelLabel->setAnchorPoint(Point::ZERO);
    levelLabel->setPosition(nickNameLabel->getPositionX() + nickNameLabel->getContentSize().width +20, nickNameLabel->getPositionY());
    bg->addChild(levelLabel);
    
    
    str = "荣誉:";
    Label* honourTitle =  PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x19c3e8),20,false,false);
    honourTitle->setAnchorPoint(Point::ZERO);
    honourTitle->setPosition(levelLabel->getPositionX() + levelLabel->getContentSize().width +20, nickNameLabel->getPositionY());
    bg->addChild(honourTitle,6);
    
    
    str = PublicShowUI::numberToString(this->m_honour);
    Label* honourLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x19c3e8),20,false,false);
    honourLabel->setAnchorPoint(Point::ZERO);
    honourLabel->setPosition(honourTitle->getPositionX() + honourTitle->getContentSize().width, honourTitle->getPositionY());
    bg->addChild(honourLabel,5,TAG_EXPLABEL);
    
//    
//    Sprite* coin = Sprite::create(IMG_ICON_PUBLIC_GOLD);
//    coin->setAnchorPoint(Point::ZERO);
//    bg->addChild(coin);
//    coin->setCascadeOpacityEnabled(true);
//    coin->setPosition(honourLabel->getPositionX() + honourLabel->getContentSize().width +20,nickNameLabel->getPositionY()-10);
//    
//    str = PublicShowUI::numberToString(this->m_gold);
//    
//    Label* goldLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xfff8da),20,false,false);
//    goldLabel->setAnchorPoint(Point::ZERO);
//    bg->addChild(goldLabel,6,TAG_COINLABEL);
//    goldLabel->setPosition(coin->getPositionX() + coin->getContentSize().width, coin->getPositionY() + (coin->getContentSize().height - goldLabel->getContentSize().height)/2);
    

    this->addChild(bg,0,TAG_USERINFO);
    bg->setPosition(Point::ZERO);

}
void ArenaBattleWin::setHeroList()
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

void ArenaBattleWin::onMsgCallBack(EventCustom* message)
{
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_ARENA_ArenaEndBattleResp)
    {
        this->heroList->clear();
        this->roleName = msg->byteStream->getUTF8();
        this->roleLevel = msg->byteStream->getInt();
        this->m_nowOrder = msg->byteStream->getInt();
        this->m_honour = msg->byteStream->getInt();
        this->changeValue = msg->byteStream->getInt();
        this->m_gold = msg->byteStream->getInt();
        int len = msg->byteStream->getByte();
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
        setUserInfo();
        this->setHeroList();
        setOrder();
        PublicShowUI::setTargetScale(this);
        this->setAnchorPoint(Point::ZERO);
        this->setPosition(VisibleRect::center().x - this->getContentSize().width/2,VisibleRect::center().y - this->getContentSize().height/2);
      
        if(this->changeValue > 0)
        {
            showHistoryBest();
        }
    }
}
void ArenaBattleWin::setOrder()
{
      Node* userBg = this->getChildByTag(TAG_USERINFO);
    Label* label = PublicShowUI::getLabel("     ",PublicShowUI::getColor3b(COLOR_ORANGE_YELLOW),25,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(userBg->getContentSize().width - label->getContentSize().width - 100, userBg->getContentSize().height/2 +5);
    userBg->addChild(label,3);
    Node* number = NULL;
    float _scale = 1;
    if(m_nowOrder)
    {
        number = PublicShowUI::getNumbers(m_nowOrder,IMG_PUBLIC_NUMBER2);
        _scale = .4;
        number->setScale(_scale);
    }
    else
    {
        number = PublicShowUI::getLabel("未入榜",PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),20,false,false);
    }
   
    
    number->setAnchorPoint(Point::ZERO);
    number->setPosition(userBg->getContentSize().width - number->getContentSize().width/2 - 20,  userBg->getContentSize().height/2 - number->getContentSize().height*_scale - 5);
    userBg->addChild(number,3);
    
    Sprite* arrow = NULL;
    string str = "";
    if(this->changeValue > 0)
    {
        arrow = Sprite::create(IMG_GENERALS_EXPERIENCE_ARROW);
        arrow->setAnchorPoint(Point(0.5,0.5));
        arrow->setRotation(-90);
        str = "[    " + PublicShowUI::numberToString(changeValue) + "]";
    }
    else if(changeValue < 0)
    {
        str = "[下降" + PublicShowUI::numberToString(changeValue) + "]";
    }
    else
    {
        str = "[排名未变]";
    }
    Label* changeLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),18,false,false);
       changeLabel->setAnchorPoint(Point::ZERO);
    changeLabel->setPosition(number->getPositionX(),number->getPositionY() - changeLabel->getContentSize().height -5);
    userBg->addChild(changeLabel,4);
    if(arrow)
    {
        arrow->setPosition(changeLabel->getPositionX() + arrow->getContentSize().width/2 + 10, changeLabel->getPositionY() + arrow->getContentSize().height/2 + 10);
        userBg->addChild(arrow);
    }

}
void ArenaBattleWin::showHistoryBest()
{
    HistoryBestLayer* layer = HistoryBestLayer::create(this->m_nowOrder,m_nowOrder - changeValue, m_gold);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    
    Scene* scene = Director::getInstance()->getRunningScene();
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_LAYER_ZORDER);
}