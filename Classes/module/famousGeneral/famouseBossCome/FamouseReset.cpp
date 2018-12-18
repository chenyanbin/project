//
//  FamouseReset.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/2/1.
//
//

#include "FamouseReset.hpp"
#include "../../../message/Decoding/famouseGeneral/RequestFamouseCard.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../message/Decoding/generals/props/PropsItemUseMsg.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../market/MarketLayer.h"
FamouseReset::FamouseReset()
:ID_CHALLENGECARD_ID(190006)
,m_attackCount(0)
,TAG_ICON(2)
{
    
}
FamouseReset::~FamouseReset()
{
    
}
FamouseReset* FamouseReset::create(int attackCount)
{
    FamouseReset* layer = new FamouseReset();
    if(layer && layer->init(attackCount))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void FamouseReset::show(int attackCount)
{
    FamouseReset* layer = FamouseReset::create(attackCount);
    
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_POPLAYER_ZORDER);
}
bool FamouseReset::init(int attackCount)
{
    this->m_attackCount = attackCount;
    PopUpLayer* layer = PopUpLayer::create();
    layer->setClickEnabled(false);
    layer->isClickClose = false;
    layer->isAutoClose = false;
    this->addChild(layer,0,TAG_BG);
    this->setContentSize(layer->getContentSize());
    this->isClickClose = true;
    this->isShowGrayBg = true;
//    layer->addButton(IMG_BUTTON_CANCEL_LABEL, 2,IMG_PUBLIC_BUTTON_TWO_RED);
    layer->addButton(IMG_BUTTON_CONFIRM_LABEL, 1,IMG_PUBLIC_BUTTON_TWO_ORANGE);
    layer->setCallBack(this, callfuncN_selector(FamouseReset::onBtnClick));
    setContent();
    return true;
}
void FamouseReset::setContent()
{
    string str = "";
    int count = GlobalInfo::getInstance()->famouseChallengeCount;
 
//    名将传次数不满且无征讨令时
//    弹框提示玩家：您当前没有征讨令，是否前往商城购买？
//    点击确定前往商城
  
    if(count > 0 && m_attackCount <= 0)
    {
        str = "是否使用一个征讨令恢复全部挑战次数";
    }
    else if(count <= 0 && m_attackCount <= 0)
    {
        str = "您当前没有征讨令，是否前往商城购买？";
    }
    else
    {
        str = "您的名将传次数已满，无需恢复";
    }
    PopUpLayer* layer = (PopUpLayer*)this->getChildByTag(TAG_BG);
    layer->setContent(str.c_str());
}
void FamouseReset::setCardIcon()
{
    int count = GlobalInfo::getInstance()->famouseChallengeCount;
    float sx = GlobalInfo::getInstance()->screenScaleX;
    float _scaleX = .6 * sx;
    string str = PublicShowUI::getGoods(DictItemTypeEnumItem, ID_CHALLENGECARD_ID);
    UserEquipLayer* icon = UserEquipLayer::create(str.c_str(),PublicShowUI::getQuality(DictItemTypeEnumItem,ID_CHALLENGECARD_ID),false);
    icon->setAnchorPoint(Point::ZERO);
    this->addChild(icon,1,TAG_ICON);
    icon->setPosition(15 * sx,this->getContentSize().height - icon->getContentSize().height * _scaleX - 25 * sx);
    
    str = PublicShowUI::getName(DictItemTypeEnumItem,ID_CHALLENGECARD_ID);
    str += ("X" + PublicShowUI::numberToString(count));
    Label* labelCount = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
    labelCount->setAnchorPoint(Point::ZERO);
    labelCount->setPosition(icon->getContentSize().width + 2 , 2);
    icon->addChild(labelCount,20);
    icon->setScale(_scaleX);
}
void FamouseReset::onBtnClick(Node* pSender)
{
    if(pSender->getTag() != 1)
    {
        this->removeFromParent();
        return;
    }
  
    int count = GlobalInfo::getInstance()->famouseChallengeCount;
  
    if(count > 0 && m_attackCount <= 0)
    {
        PropsItemUseMsg* msg = new PropsItemUseMsg(ID_CHALLENGECARD_ID);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
    else if(count <= 0 && m_attackCount <= 0)
    {
       MarketLayer::show(SCENE_TAG_MAINUI,MarketLayer::TAG_SHANGDIAN);
    }
    this->removeFromParent();
  }
void FamouseReset::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void FamouseReset::onExit()
{
     BaseLayer::onExit();
}
void FamouseReset::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
     this->setClickEnabled(false);
}
void FamouseReset::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    Dialog::showServerLoading();
    RequestFamouseCard* msg = new RequestFamouseCard();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FamouseReset::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendRestoreAttackCountPageResp)
    {
        int count = msg->byteStream->getShort();
        int addOneCountTime = msg->byteStream->getInt();//秒
        GlobalInfo::getInstance()->famouseChallengeCount = count;
        setCardIcon();
        setContent();
    }

}
void FamouseReset::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendRestoreAttackCountPageResp).c_str(), CC_CALLBACK_1(FamouseReset::onMsgProcess, this));
}
void FamouseReset::removeEventListener()
{
     BaseLayer::removeEventListener();
}
bool FamouseReset::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch,unused_event);
    return true;
}
void FamouseReset::onTouchMoved(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchMoved(touch,unused_event);
}
void FamouseReset::onTouchEnded(Touch *touch, Event *unused_event)
{
     BaseLayer::onTouchEnded(touch,unused_event);
}