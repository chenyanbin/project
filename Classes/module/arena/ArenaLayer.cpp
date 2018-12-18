//
//  ArenaLayer.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/9.
//
//

#include "ArenaLayer.hpp"
#include "../userWealth/UserWealthLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "arenaList/ArenaListLayer.hpp"
#include "arenaOrder/ArenaOrderLayerList.hpp"
#include "arenaTeam/ArenaTeamLayer.hpp"
#include "arenaExchange/ArenaExchangeLayerList.hpp"
#include "arenaRecored/ArenaRecoredLayer.hpp"
#include "../../common/Dialog/Dialog.h"
#include "../../message/Decoding/arena/ArenaEveryDayPriceMsg.hpp"
#include "../../net/NetworkDataProcessing.h"
#include "ArenaExplainLayer.hpp"
#include "../../commonData/enum/DictFunctionEnum.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
ArenaLayer::ArenaLayer()
:TAG_USERWEALTH(1)
,TAG_RIGHTBTN(2)
,TAG_LEFTTIME(3)
,TAG_TOPPRIZE(4)
,TAG_RECORDBTN(5)
,TAG_INSTRUCTIONBTN(6)
,m_tagLayer(-1)
,leftTime(99999)
{
    
}
ArenaLayer::~ArenaLayer()
{
    
}
bool ArenaLayer::init(int showPage)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_tagLayer = showPage;
        setbackGround();
        topLayer();
//        requestEveryTimeMsg();
//        setTime();
//        settopPrizeTitle();
//        setRightBtn();
//        setBottomInstruction();
        this->setBackBtn(20 * GlobalInfo::getInstance()->screenScaleX,15 * GlobalInfo::getInstance()->screenScaleX,true);
        bref = true;
    } while (false);
    return bref;
}
ArenaLayer* ArenaLayer::create(int showPage)
{
    ArenaLayer* layer = new ArenaLayer();
    if(layer && layer->init(showPage))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void ArenaLayer::show(int showPage)
{
    ArenaLayer* layer = ArenaLayer::create(showPage);
    layer->setAnchorPoint(Point::ZERO);
    layer->setFromScene(SCENE_TAG_MAINUI);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_ARENA);
    Director::getInstance()->replaceScene(scene);
}
void ArenaLayer::setRightBtn()
{
  
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, -20, CC_CALLBACK_1(ArenaLayer::onRightBtnClick, this));
    const char* titleList[4] = {IMG_ARENA_EXCHAGETITLE,IMG_ARENA_ORDERTITLE,IMG_ARENA_TEANTITLE,IMG_ARENA_RACETITLE};
    int tagList[4] = {PAGE_ARENAEXCHANGE,PAGE_ARENAORDER,PAGE_ARENATEAM,PAGE_ARENALIST};
    for (int i = 0; i < 4; i++)
    {
      
        boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, titleList[i],true,tagList[i]);
    }
//    RefreshDot::getInstance()->requestMsg(boxBtn->getButtonAt(3),Point::ZERO,false,DictFunctionEnumArena);
    PublicShowUI::setDot(boxBtn->getButtonAt(3), Point::ZERO, false,DictFunctionEnumArena);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumArenaExchangeButton, boxBtn->getButtonAt(0));

    PublicShowUI::setTargetScale(boxBtn);
    boxBtn->setPosition(VisibleRect::right().x - boxBtn->getContentSize().width,VisibleRect::center().y-boxBtn->getContentSize().height/2);
    this->addChild(boxBtn,3,TAG_RIGHTBTN);
    boxBtn->selectAtByTag(m_tagLayer);
   
}
void ArenaLayer::onRightBtnClick(Ref* psender)
{
    if(this->getChildByTag(m_tagLayer))
    {
        this->removeChildByTag(m_tagLayer);
    }
  
    BaseLayer* layer = NULL;
    Node* target = (Node*)psender;
    int tag = target->getTag();
    switch (tag)
    {
        case PAGE_ARENALIST:
            layer = ArenaListLayer::create();
          
            break;
        case PAGE_ARENATEAM:
            layer = ArenaTeamLayer::create();
           
            
            break;
        case PAGE_ARENAORDER:
            layer = ArenaOrderLayerList::create();
          
            break;
        case PAGE_ARENAEXCHANGE:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumArenaExchangeButton);
            layer = ArenaExchangeLayerList::create();
            break;
        default:
            break;
    }
    if(layer)
    {
        layer->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(layer);
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2 - 40 * GlobalInfo::getInstance()->screenScaleX, VisibleRect::center().y - layer->getContentSize().height/2 - 30 * GlobalInfo::getInstance()->screenScaleX);
        this->addChild(layer, 2, tag);
    }
     this->m_tagLayer = tag;
    updateTopTimePosition();
}
void ArenaLayer::setBottomInstruction()
{
    Node* layer = this->getChildByTag(m_tagLayer);
    
    Sprite* spr = Sprite::create(IMG_ARENA_BOTTOM_INSTRUCTION);
    spr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(spr);
    spr->setPosition(VisibleRect::center().x - spr->getContentSize().width/2, layer->getPositionY() - spr->getContentSize().height + 10 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(spr,3);
}
void ArenaLayer::setbackGround()
{
    Sprite* bgSpr = Sprite::create(IMG_PUBLIC_MODULE_BG);
    PublicShowUI::setTargetScale(bgSpr,true);
    bgSpr->setAnchorPoint(Point::ZERO);
    bgSpr->setPosition(Point::ZERO);
    this->addChild(bgSpr,-2);
    
    Sprite* bgSprgray = Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
    PublicShowUI::setTargetScale(bgSprgray,true);
    bgSprgray->setAnchorPoint(Point::ZERO);
    bgSprgray->setPosition(Point::ZERO);
    this->addChild(bgSprgray,-1);
}
void ArenaLayer::topLayer()
{
    UserWealthLayer* layer = (UserWealthLayer*)this->getChildByTag(TAG_USERWEALTH);
    if(!layer)
    {
        layer = UserWealthLayer::create(UserWealthLayer::FAMOUSE);
        PublicShowUI::setTargetScale(layer);
    }

    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,2,TAG_USERWEALTH);
    layer->setTitle(IMG_PUBLIC_ARENA);
}
void ArenaLayer::setTime()
{
    if(leftTime < 0)
    {
        return;
    }
    string str = PublicShowUI::getTime(this->leftTime);
    Label* label = (Label*)this->getChildByTag(TAG_LEFTTIME);
    if(label)
    {
        label->setString(str);
    }
    else
    {
        float sx = GlobalInfo::getInstance()->screenScaleX;
        Node* node = this->getChildByTag(TAG_USERWEALTH);
        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE),24,false,true);
        label->setAnchorPoint(Point::ZERO);
        this->addChild(label,9,TAG_LEFTTIME);
        if(node)
        {
            label->setPosition(330 * sx,node->getPositionY() + 15 * sx);
        }
     
    }
    DelayTime* delay = DelayTime::create(1);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(ArenaLayer::setTime, this));
    label->runAction(Sequence::create(delay,callBack, NULL));
    leftTime-= 1000;
}
void ArenaLayer::settopPrizeTitle()
{
    Sprite* title = Sprite::create(IMG_ARENA_TOP_PRIZE);
    title->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(title);
    Label* label = (Label*)this->getChildByTag(TAG_LEFTTIME);
    this->addChild(title,9,TAG_TOPPRIZE);
    title->setPosition(label->getPositionX() + label->getContentSize().width, label->getPositionY());
    
}
void ArenaLayer::updateTopTimePosition()//更新顶部时间位置
{
    this->removeChildByTag(TAG_RECORDBTN);
    this->removeChildByTag(TAG_INSTRUCTIONBTN);
    Node* topPrize = this->getChildByTag(TAG_TOPPRIZE);
    Node* timeLabel = this->getChildByTag(TAG_LEFTTIME);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    switch (m_tagLayer)
    {
        case PAGE_ARENALIST:
        case PAGE_ARENAORDER:
            timeLabel->setPositionX(330 * sx);
            topPrize->setPositionX(timeLabel->getPositionX() + timeLabel->getContentSize().width);
            setTopBtn();
            break;
        case PAGE_ARENATEAM:
        case PAGE_ARENAEXCHANGE:
            timeLabel->setPositionX(VisibleRect::center().x - timeLabel->getContentSize().width);
            topPrize->setPositionX(timeLabel->getPositionX() + timeLabel->getContentSize().width);
            break;
        default:
            break;
    }
}
void ArenaLayer::setTopBtn()
{
     Node* node = this->getChildByTag(TAG_TOPPRIZE);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    CustomButton* recordBtn = CustomButton::create(IMG_PUBLIC_BUTTON_FOUR_RED, "", CC_CALLBACK_1(ArenaLayer::onRecoredClick, this));
    recordBtn->setAnchorPoint(Point::ZERO);
    recordBtn->addTitle(IMG_ARENA_RECORDETITLE, IMG_ARENA_RECORDETITLE);
    PublicShowUI::setTargetScale(recordBtn);
    recordBtn->setPosition(node->getPositionX() + node->getContentSize().width + 15 * sx, node->getPositionY() - 10 * sx);
    this->addChild(recordBtn,10,TAG_RECORDBTN);
    
    CustomButton* instructionBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(ArenaLayer::onInstructionBtnClick, this));
    instructionBtn->setAnchorPoint(Point::ZERO);
     instructionBtn->addTitle(IMG_ARENA_INSTRUCTIONTITLE, IMG_ARENA_INSTRUCTIONTITLE);
    PublicShowUI::setTargetScale(instructionBtn);
    instructionBtn->setPosition(recordBtn->getPositionX() + recordBtn->getContentSize().width + 15 * sx, recordBtn->getPositionY());
    this->addChild(instructionBtn,10,TAG_INSTRUCTIONBTN);
}
void ArenaLayer::onRecoredClick(Ref* pSender)
{
    ArenaRecoredLayer::show();
}
void ArenaLayer::onInstructionBtnClick(Ref* pSender)
{
    ArenaExplainLayer::show();
}
void ArenaLayer::onExit()
{
     BaseLayer::onExit();
}
void ArenaLayer::onEnter()
{
    BaseLayer::onEnter();
    
}
void ArenaLayer::onExitTransitionDidStart()
{
     BaseLayer::onExitTransitionDidStart();
     removeEventListener();
}
void ArenaLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestEveryTimeMsg();
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void ArenaLayer::requestEveryTimeMsg()
{
    Dialog::showServerLoading();
    ArenaEveryDayPriceMsg* msg = new ArenaEveryDayPriceMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}
void ArenaLayer::onEveryTimeMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_ARENA_ArenaDayRewardCountDownResp)
    {
        if(message->state)//返回成功
        {
            leftTime = message->byteStream->getLong();//当前排名
            setTime();
            settopPrizeTitle();
            setRightBtn();
            NewPlayerGuild::getInstance()->showNowGuide();
        }
    }
}
void ArenaLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaDayRewardCountDownResp).c_str(), CC_CALLBACK_1(ArenaLayer::onEveryTimeMsgProcess, this));
}
void ArenaLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
