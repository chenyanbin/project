//
//  BattleCountDown.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/12.
//
//

#include "BattleCountDown.hpp"
#include "../../../protocol/UserCustomEvent.h"
BattleCountDown* BattleCountDown::_instance = NULL;
BattleCountDown::BattleCountDown()
:TAG_LEFTTIME(1)
,TAG_ACTION(2)
,m_isTimeWinMode(false)
,TAG_TIMEBG(3)
{
    m_leftTime = 0;
    onDelay();
    Label* label = ( Label*)this->getChildByTag(TAG_LEFTTIME);
    this->setContentSize(label->getContentSize());
}
BattleCountDown::~BattleCountDown()
{
    _instance = NULL;
}

BattleCountDown* BattleCountDown::getInstance()
{
  if(!_instance)
  {
      _instance = new BattleCountDown();
      _instance->autorelease();
  }
    return _instance;
}

void BattleCountDown::start(bool isTimeWinMode,int _leftTime)
{
    this->m_leftTime = _leftTime;
    this->m_isTimeWinMode = isTimeWinMode;
    this->stopActionByTag(TAG_ACTION);
    DelayTime* delay = DelayTime::create(1);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleCountDown::onDelay, this));
    RepeatForever* action = RepeatForever::create(Sequence::create(delay,callBack, NULL)) ;
    action->setTag(TAG_ACTION);
    this->runAction(action);
}
void BattleCountDown::onDelay()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* sprBg = (Sprite*)this->getChildByTag(TAG_TIMEBG);
    if(!sprBg)
    {
        sprBg = Sprite::create(IMG_BATTLE_TIMEBG);
        sprBg->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(sprBg,false,false);
        sprBg->setPosition(0,-20*sx);
        this->addChild(sprBg,2,TAG_TIMEBG);
    }
    string str = GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan ? PublicShowUI::getTime(m_leftTime * 1000) :  PublicShowUI::getTime(m_leftTime * 1000,2);
//    string preStr = this->m_isTimeWinMode ? "胜利倒计时" : "结束倒计时";
    Label* label = ( Label*)this->getChildByTag(TAG_LEFTTIME);
//    str = preStr + str;
    if(label)
    {
        label->setString(str);
    }
    else
    {
        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE ),26,false,true);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(sprBg->getPositionX() +  160 * sx,sprBg->getPositionY() + 10 * sx);
        this->addChild(label,3,TAG_LEFTTIME);
    }
    
    m_leftTime --;
    if(this->m_leftTime < 0)
    {
        this->stopActionByTag(TAG_ACTION);
        broadMsg(CUSTOM_BATTLE_COUNTDOWN_OVER);
        return;
    }
//    long time = m_leftTime * 1000;
//    long hour = time/3600000;
//    long minutes = time%3600000/60000;
//    long sec = time%3600000%60000/1000;
//    
//    this->removeChildByTag(TAG_LEFTTIME);
//    Node* node = Node::create();
//    node->setAnchorPoint(Point::ZERO);
//    
//    Node* hourLabel = PublicShowUI::getNumbers(hour);
//    hourLabel->setAnchorPoint(Point::ZERO);
    
}
void BattleCountDown::stop()
{
   this->stopActionByTag(TAG_ACTION);
}
void BattleCountDown::onEnter()
{
    BaseLayer::onEnter();
}
void BattleCountDown::onExit()
{
    BaseLayer::onExit();
}
void BattleCountDown::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void BattleCountDown::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}