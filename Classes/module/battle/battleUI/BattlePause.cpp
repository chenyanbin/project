//
//  BattlePause.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/29.
//
//

#include "BattlePause.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/noticeManager/NoticeManager.h"
BattlePause::BattlePause()
{
    
}
BattlePause::~BattlePause()
{
    
}
bool BattlePause::init()
{
    if(!BaseLayer::init())
    {
        return false;
    }
    this->isAnimation = false;
    this->isShowGrayBg = true;
    this->isClickClose = true;
    setButton();
    return true;
}
void BattlePause::show()
{
    BattlePause* layer = BattlePause::create();
    layer->setAnchorPoint(Point::ZERO);
    Scene* scene = Director::getInstance()->getRunningScene();
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2 , VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_LAYER_ZORDER);
}
void BattlePause::setButton()
{
    Sprite* backSpr = Sprite::create(IMG_BATTLE_BACK);
    backSpr->setAnchorPoint(Point::ZERO);
    Label* label = PublicShowUI::getLabel("退出战斗",PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition((backSpr->getContentSize().width - label->getContentSize().width)/2, -label->getContentSize().height);
    backSpr->addChild(label);
    MenuItemLabel* backLabel = MenuItemLabel::create(backSpr, CC_CALLBACK_1(BattlePause::onBackClick, this));
    backLabel->setAnchorPoint(Point::ZERO);
   
    
    Sprite* playSpr = Sprite::create(IMG_BATTLE_PLAY);
    playSpr->setAnchorPoint(Point::ZERO);
    label = PublicShowUI::getLabel("继续战斗",PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition((playSpr->getContentSize().width - label->getContentSize().width)/2, -label->getContentSize().height);
    playSpr->addChild(label);
    MenuItemLabel* playLabel = MenuItemLabel::create(playSpr, CC_CALLBACK_1(BattlePause::onPlayClick, this));
    playLabel->setAnchorPoint(Point::ZERO);
    
    playLabel->setPositionX(250);
    
    Menu* menu = Menu::create(backLabel,playLabel, NULL);
    menu->setAnchorPoint(Point::ZERO);
    Size size = playLabel->getContentSize();
    size.width = playLabel->getPositionX() + playLabel->getContentSize().width;
    menu->setContentSize(size);
    PublicShowUI::setTargetScale(menu);
    menu->setPosition(Point::ZERO);
    this->setContentSize(menu->getContentSize());
    
    this->addChild(menu);
    
}
void BattlePause::onPlayClick(Ref* pSender)
{
    this->removeFromParent();

}
void BattlePause::onBackClick(Ref* pSender)
{
    if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle)
    {
        broadMsg(CUSTOM_BATTLE_QUITBATTLE,__Bool::create(false));
         this->removeFromParent();
        return;
    }
    broadMsg(CUSTOM_OVERFIGHT_TALK_END);
    this->removeFromParent();
}
void BattlePause::onEnter()
{
    BaseLayer::onEnter();
}
void BattlePause::onExit()
{
    BaseLayer::onExit();
}
void BattlePause::onExitTransitionDidStart()
{
      Director::getInstance()->resume();
    BaseLayer::onExitTransitionDidStart();
     this->setClickEnabled(false);
}
void BattlePause::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    Director::getInstance()->pause();
    this->setClickEnabled(true);
}