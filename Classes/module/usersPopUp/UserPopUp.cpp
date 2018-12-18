//
//  UserPropUp.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#include "UserPopUp.hpp"
#include "upLevelPopUp/UpLevelPopUp.hpp"
#include "functionOpen/FunctionOpenPopUp.hpp"
#include "../../common/CustomMsgProcesser.h"
void UserPopUp::showLevel(int newLevel)
{
    UpLevelPopUp* layer = UpLevelPopUp::create(newLevel);
    layer->setAnchorPoint(Point::ZERO);
//    float sx = GlobalInfo::getInstance()->screenScaleX;
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2 + 30 * GlobalInfo::getInstance()->screenScaleX);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_LAYER_ZORDER + 20,LAYER_USER_POPUP);
    
//    MoveBy* moveBy = MoveBy::create(1, Point(0,150 * sx));
//    layer->runAction(moveBy);
}
void UserPopUp::showNewFunctionOpen(int functionID)
{
    FunctionOpenPopUp* layer = FunctionOpenPopUp::create(functionID);
    layer->setAnchorPoint(Point::ZERO);
 
    layer->setScale(2);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_LAYER_ZORDER + 20,LAYER_USER_POPUP);

}
UserPopUp::UserPopUp()
{
    this->isAbleGuiding = false;
}
UserPopUp::~UserPopUp()
{
    
}
bool UserPopUp::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}
void UserPopUp::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void UserPopUp::onTouchEnded(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchEnded(touch, unused_event);
}

void UserPopUp::onEnter()
{
    BaseLayer::onEnter();
}
void UserPopUp::onExit()
{
    BaseLayer::onExit();
}
void UserPopUp::onExitTransitionDidStart()
{
    CustomMsgProcesser::getInstance()->nextMsgListData();
    BaseLayer::onExitTransitionDidStart();
    this->setClickEnabled(false);
    
}
void UserPopUp::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
     this->setClickEnabled(true);
    this->isClickClose = false;
    this->setGrayBg();
    
}
void UserPopUp::delayClickClose()
{
    DelayTime* delay = DelayTime::create(1.5);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(UserPopUp::setClickClose, this));
    this->runAction(Sequence::create(delay,callBack, NULL));
}
void UserPopUp::setClickClose()
{
    this->isClickClose = true;
}