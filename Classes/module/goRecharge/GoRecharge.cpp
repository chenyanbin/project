//
//  GoRecharge.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/28.
//
//

#include "GoRecharge.hpp"
#include "../../common/TouchSprite/Button.h"
#include "../vip/VipLayer.h"
GoRecharge::GoRecharge()
{
}
GoRecharge::~ GoRecharge()
{
    
}
bool GoRecharge::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,false);
        this->setClickEnabled(true);
        this->isClickClose = true;
        this->isShowGrayBg = true;
        onSetButton();
        bref = true;
    } while (false);
    return bref;
}
GoRecharge* GoRecharge::create()
{
    GoRecharge* layer= new GoRecharge();
    if(layer && layer->init())
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void GoRecharge::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    GoRecharge* layer = GoRecharge::create();
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_LAYER_ZORDER + 1);
}

void GoRecharge::onEnter()
{
    BaseLayer::onEnter();
}
void GoRecharge::onExit()
{
    BaseLayer::onExit();
}
void GoRecharge::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
}
void GoRecharge::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumGrabButton);
}

void GoRecharge::onSetButton()
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    float sx = GlobalInfo::getInstance()->screenScaleX;

    string str = "元宝不足";
    Label* label = PublicShowUI::getLabelNumber(str.c_str(), PublicShowUI::getColor3b(COLOR_BROWN_WHITE), 22, false, false);
    label->setPosition(layer->getContentSize().width/sx/2,layer->getContentSize().height/sx/2+50);
    layer->addChild(label);
    
    Button* btncell =Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(GoRecharge::onClick, this));
    btncell->setAnchorPoint(Point::ZERO);
    btncell->setPosition(layer->getContentSize().width/sx/2-btncell->getContentSize().width/2-80,50);
    layer->addChild(btncell,1,1);
    Sprite* sprcell = Sprite::create(IMG_BUTTON_CANCEL_LABEL);
    sprcell->setAnchorPoint(Point::ZERO);
    sprcell->setPosition(Point::ZERO);
    btncell->addChild(sprcell,5,1);
    
    //充值
    Button* btnrechage =Button::create(IMG_PUBLIC_BUTTON_TWO_RED, IMG_PUBLIC_BUTTON_TWO_RED, CC_CALLBACK_1(GoRecharge::onClick, this));
    btnrechage->setAnchorPoint(Point::ZERO);
    btnrechage->setPosition(btncell->getPositionX() + btncell->getContentSize().width+100,50);
    layer->addChild(btnrechage,1,0);
    Sprite* sprrechage = Sprite::create(IMG_PUBLIC_LABEL_RECHARGE);
    sprrechage->setAnchorPoint(Point::ZERO);
    sprrechage->setPosition(Point::ZERO);
    btnrechage->addChild(sprrechage,5,0);
    
    
}

void GoRecharge::onClick(Ref* pSender)
{
    Node* target= (Node*)pSender;
    if (target->getTag() == 0) {
        VipLayer::show(SCENE_TAG_MAINUI);
    }else{
        this->removeFromParent();
    }
}
