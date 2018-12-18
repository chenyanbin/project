//
//  RebornPanel.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/7.
//
//

#include "RebornPanel.h"
#include "../../../commonData/dictData/DictBattleRebornCost/DictBattleRebornCostManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../message/Decoding/battle/BattleRebornMsg.h"
#include "../../../net/NetworkDataProcessing.h"
RebornPanel::RebornPanel()
:m_costGold(0)
,TAG_LABEL(1)
,TAG_CONFIRM(2)
,TAG_TITLE(3)
,m_delayCount(11)
,m_rebornCount(0)
{
    
}
RebornPanel::~RebornPanel()
{
}
bool RebornPanel::init(int rebornCount)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_rebornCount = rebornCount;
        setTitle();
        setConfirmBtn();
        setCancelBtn();
        this->isShowGrayBg = true;
//        Node* delayLabel = this->getChildByTag(TAG_LABEL);
//        Node* title  =this->getChildByTag(TAG_TITLE);
//        title->setPositionY(delayLabel->getPositionY() + delayLabel->getContentSize().height);
//        Size size = title->getContentSize();
//        size.height = title->getPositionY() + title->getContentSize().height;
//        this->setContentSize(size);
        bref = true;
    } while (false);
    return bref;
}
void RebornPanel::setConfirmBtn()
{
//    TAG_CONFIRM
    Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_RED, "", CC_CALLBACK_1(RebornPanel::onConfirmClick, this));
    btn->setAnchorPoint(Point::ZERO);
    Sprite* title = Sprite::create(IMG_BUTTON_REBORNLABEL);
    title->setPosition(btn->getContentSize().width/2, btn->getContentSize().height/2);
    btn->addChild(title,10);
    btn->setPosition((this->getContentSize().width - btn->getContentSize().width)/2 - 100, 0);
    this->addChild(btn,1,TAG_CONFIRM);
    
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    
    string str  = PublicShowUI::numberToString(getCostGold(m_rebornCount));
    Label* label = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,25,false,false);
    label->setAnchorPoint(Point::ZERO);
    gold->addChild(label,10);
    label->setPosition(gold->getContentSize().width, (gold->getContentSize().height - label->getContentSize().height)/2);
    
    this->addChild(gold,3);
    gold->setPosition(btn->getPositionX() - gold->getContentSize().width - label->getContentSize().width, btn->getPositionY());
}
void RebornPanel::onConfirmClick(Ref* pSender)
{
    Dialog::showServerLoading(.5);
    BattleRebornMsg* msg = new BattleRebornMsg(m_rebornCount);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
//    broadMsg(CUSTOM_BATTLE_HERO_REBORNCONFIRM);
    this->removeFromParent();
}
int RebornPanel::getCostGold(int count)
{
    
    int gold = 0;
    Vector<DictBattleRebornCost*>* list = DictBattleRebornCostManager::getInstance()->getDataList();
    for(DictBattleRebornCost* data :* list)
    {
        if(data->rebornTimes == count)
        {
            gold = data->gold;
            break;
        }
    }
    
    return gold;
    
}
void RebornPanel::setTitle()
{
    Sprite* title = Sprite::create(IMG_BATTLE_CONTINUE);
    title->setAnchorPoint(Point::ZERO);
    this->addChild(title,0,TAG_TITLE);
    title->setPosition(0,0);
    this->setContentSize(title->getContentSize());
}
void RebornPanel::setCancelBtn()
{
    Node* confirmBtn = this->getChildByTag(TAG_CONFIRM);
    Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(RebornPanel::onCancelClick, this));
    btn->setAnchorPoint(Point::ZERO);
    Sprite* title = Sprite::create(IMG_BUTTON_NOLABEL);
    title->setPosition(btn->getContentSize().width/2, btn->getContentSize().height/2);
    btn->addChild(title,10);
    btn->setPosition((this->getContentSize().width - btn->getContentSize().width)/2, 0);
    this->addChild(btn,2);
    btn->setPosition(confirmBtn->getPositionX() + btn->getContentSize().width + 100, confirmBtn->getPositionY());

}
void RebornPanel::onCancelClick(Ref* pSender)
{
    onCancel();
}
void RebornPanel::onCancel()
{
     broadMsg(CUSTOM_BATTLE_HERO_REBORNCANCEL);
     this->removeFromParent();
}
RebornPanel* RebornPanel::create(int rebornCount)
{
    RebornPanel* panel = new RebornPanel();
    if(panel && panel->init(rebornCount))
    {
        panel->autorelease();
        return panel;
    }
    CC_SAFE_DELETE(panel);
    panel = NULL;
    return NULL;
}
void RebornPanel::show(int costGold)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    RebornPanel* panel = RebornPanel::create(costGold);
    panel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(panel);
    panel->setPosition(VisibleRect::center().x - panel->getContentSize().width/2, VisibleRect::center().y - panel->getContentSize().height/2);
    scene->addChild(panel,SCENE_POPLAYER_ZORDER,SCENE_TAG_REBORN);
}
void RebornPanel::onEnter()
{
    BaseLayer::onEnter();

}
void RebornPanel::onExit()
{
    BaseLayer::onExit();

}
void RebornPanel::onExitTransitionDidStart()
{
     BaseLayer::onExitTransitionDidStart();
     this->stopAllActions();
    this->setClickEnabled(false);
}
void RebornPanel::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
  
    this->setClickEnabled(true);
//    onDelay();
}
void RebornPanel::onDelay()
{
    if(m_delayCount <= 0)
    {
        onCancel();
        return;
    }
    Node* confirmBtn = this->getChildByTag(TAG_CONFIRM);
    Node* label = (Node*)this->getChildByTag(TAG_LABEL);
    if(label)
    {
        label->removeFromParent();
    }
    label = PublicShowUI::getNumbers(m_delayCount,IMG_PUBLIC_NUMBER5);
    label->setAnchorPoint(Point::ZERO);
    this->addChild(label,1,TAG_LABEL);
    label->setPosition(confirmBtn->getPositionX() +(confirmBtn->getContentSize().width - label->getContentSize().width)/2, 150);
    SoundManager::playEffectMusic(EFFECT_NUMBER);
    m_delayCount--;
    DelayTime* delay = DelayTime::create(1);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(RebornPanel::onDelay, this));
    this->stopAllActions();
    this->runAction(Sequence::create(delay,callBack, NULL));
}

bool RebornPanel::onTouchBegan(Touch *touch, Event *unused_event)
{
    return false;
}
void RebornPanel::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void RebornPanel::onTouchEnded(Touch *touch, Event *unused_event)
{
//    onDelay();
}